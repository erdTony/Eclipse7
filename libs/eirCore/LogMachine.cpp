#include "LogMachine.h"

#include <QCoreApplication>
#include <QFinalState>
#include <QState>
#include <QTimer>

#include <CTextList.h>

#include "LogObject.h"
#include "BaseLogOutput.h"
#include "LogUrl.h"

LogMachine::LogMachine(Log *parent)
    : QStateMachine{parent}
    , mpParentLog(parent)
    , mpInitializeState(new QState(this))
    , mpProcessingState(new QState(this))
    , mpFormattingState(new QState(this))
    , mpDistributeState(new QState(this))
    , mpQuittingState(new QFinalState(this))
    , mpPulseTimer(new QTimer(this))
{
    setObjectName("LogMachine:Idle");
    Q_CHECK_PTR(mpInitializeState);
    Q_CHECK_PTR(mpProcessingState);
    Q_CHECK_PTR(mpFormattingState);
    Q_CHECK_PTR(mpDistributeState);
    Q_CHECK_PTR(mpQuittingState);
    mpInitializeState->setObjectName("InitializeState");
    mpInitializeState->setObjectName("ProcessingState");
    mpProcessingState->setObjectName("FormattingState");
    mpFormattingState->setObjectName("DistributeState");
    mpDistributeState->setObjectName("QuittingState");
    mpQuittingState->setObjectName("InitializeState");
    mpInitializeState->setProperty("Name", "Initialize");
    mpProcessingState->setProperty("Name", "Processing");
    mpFormattingState->setProperty("Name", "Formatting");
    mpDistributeState->setProperty("Name", "Distribute");
    mpQuittingState->setProperty("Name", "Quitting");
}

void LogMachine::setup()
{
    setInitialState(mpInitializeState);
    mCurrentState = Initialize;
    Q_ASSERT(connect(pulseTimer(), &QTimer::timeout,
                     this, &LogMachine::pulse));
    Q_ASSERT(connect(LOG(), &Log::enqueuedMessage,
                     this, &LogMachine::enqueueMessage));
    Q_ASSERT(connect(qApp, &QCoreApplication::aboutToQuit,
                     this, &LogMachine::quit));
    QTimer::singleShot(100, this, &LogMachine::run);
}

void LogMachine::run()
{
    pulseTimer()->setInterval(mLongPulse ? 100 : 10);
    pulseTimer()->start();
}

void LogMachine::enqueueMessage()
{
    const LogMessage cMsg = LOG()->dequeueMessage();
    mMessageQueue.enqueue(cMsg);
    emit enqueuedMessage(cMsg);
}

void LogMachine::pulse()
{
    mLongPulse = true;
    pulseTimer()->stop();

    switch (mCurrentState)
    {
    case Initialize:    mLongPulse &= initialize();     break;
    case Process:       mLongPulse &= process();        break;
    case Format:        mLongPulse &= format();         break;
    case Distribute:    mLongPulse &= distribute();     break;
    case Quitting:                    quit();           break;
    default:            /* NADA */                      break;
    };

    run();
}

void LogMachine::quit()
{
    foreach (BaseLogOutput * pOut, LOG()->outputList())
    {
        pOut->flush();
        pOut->close();
        pOut->deleteLater();
        LOG()->remove(pOut);
    }

}

bool LogMachine::initialize()
{
    mCurrentState = Process;
    return mMessageQueue.isEmpty();
}

bool LogMachine::process()
{
    Count k = qMin(10, mMessageQueue.count());
    while (k--)
    {
        LogMessage tLM = mMessageQueue.dequeue();
        LogItem tLI(tLM);
        mItemQueue.enqueue(tLI);
    }
    mCurrentState = Format;
    return mMessageQueue.isEmpty();
}

bool LogMachine::format()
{
    Count k = qMin(10, mItemQueue.count());
    while (k--)
    {
        LogItem tLI = mItemQueue.dequeue();
        foreach (BaseLogOutput * pOut, LOG()->outputList())
        {
            LogFormat tLF = pOut->url().format();
            CTextList tCTxL = tLF.process(tLI);
            FormatKey tFK;
            tFK.first = tLI.logUid();
            tFK.second = pOut;
            mFormattedItemMap.insert(tFK, tCTxL);
        }
    }
    mCurrentState = Distribute;
    return mFormattedItemMap.isEmpty();
}

bool LogMachine::distribute()
{
    Count k = qMin(10, mFormattedItemMap.count());
    while (k--)
    {
        FormatKey tKey = mFormattedItemMap.firstKey();
        CTextList tMsg = mFormattedItemMap.value(tKey);
        BaseLogOutput * pOut = tKey.second;
        Q_CHECK_PTR(pOut);
        mFormattedItemMap.remove(tKey);
        pOut->write(tMsg);
    }
    mCurrentState = Process;
    return mMessageQueue.isEmpty();
}


