#pragma once
#include "eirCore.h"

#include <QObject>
#include <QStateMachine>

#include <QPair>
#include <QQueue>
class QFinalState;
class QState;
class QTimer;

#include <CTextList.h>
#include <Uid.h>

#include "LogItem.h"
#include "LogFormat.h"
#include "LogMessage.h"
class Log;
class BaseLogOutput;

class EIRCORE_EXPORT LogMachine : public QStateMachine
{
    Q_OBJECT
public: // types
    enum State
    {
        $nullState,
        Initialize,
        Process,
        Format,
        Distribute,
        Quitting,
        $maxState
    };
    typedef QPair<Uid, BaseLogOutput *> FormatKey;

public:
    explicit LogMachine(Log *parent = nullptr);

public slots:
    void setup();
    void run();
    void enqueueMessage();
    void pulse();
    void quit();

signals:
    void changedState(const State * newState);
    void processingDone();
    void formatingDone();
    void distributingDone();
    void messageReady();
    void enqueuedMessage(const LogMessage &message);
    void dequeuedMessage(const LogMessage &message);

public: // const


public: // non-const
    bool initialize();
    bool process();
    bool format();
    bool distribute();

public: // pointers
    QTimer * pulseTimer();

private:
    Log * mpParentLog=nullptr;
    QState * mpInitializeState=nullptr;
    QState * mpProcessingState=nullptr;
    QState * mpFormattingState=nullptr;
    QState * mpDistributeState=nullptr;
    QFinalState * mpQuittingState=nullptr;
    QTimer * mpPulseTimer=nullptr;
    State mCurrentState=$nullState;
    LogFormat::Format mFormatMask;
    QQueue<LogMessage> mMessageQueue;
    QQueue<LogItem> mItemQueue;
    QMap<FormatKey, CTextList> mFormattedItemMap;
    bool mLongPulse=true;
};

inline QTimer *LogMachine::pulseTimer() { Q_CHECK_PTR(mpPulseTimer); return mpPulseTimer; }


