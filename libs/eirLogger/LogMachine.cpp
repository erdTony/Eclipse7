#include "LogMachine.h"

#include <QCoreApplication>
#include <QFinalState>
#include <QState>
#include <QTimer>

#include "LogObject.h"

LogMachine::LogMachine(QObject *parent)
    : QStateMachine{parent}
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
    mpInitializeState->addTransition(mpProcessingState);
    mpProcessingState->addTransition(mpProcessingState,
                                     SIGNAL(processingDone),
                                     mpFormattingState);
    mpFormattingState->addTransition(mpFormattingState,
                                     SIGNAL(formatingDone),
                                     mpDistributeState);
    mpDistributeState->addTransition(mpDistributeState,
                                     SIGNAL(distributingDone),
                                     mpProcessingState);
    Q_ASSERT(connect(pulseTimer(), &QTimer::timeout,
                     this, &LogMachine::pulse));
    Q_ASSERT(connect(LOG(), &Log::enqueuedMessage,
                     this, &LogMachine::enqueueMessage));
    Q_ASSERT(connect(qApp, &QCoreApplication::aboutToQuit,
                     this, &LogMachine::quit));
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

    run();
}

void LogMachine::initialize()
{

}

void LogMachine::process()
{

}

void LogMachine::format()
{

}

void LogMachine::distribute()
{

}

void LogMachine::quit()
{

}


