#pragma once
#include "eirLogger.h"

#include <QObject>
#include <QStateMachine>

#include <QQueue>
class QFinalState;
class QState;
class QTimer;

#include "LogItem.h"
#include "LogMessage.h"

class EIRLOGGER_EXPORT LogMachine : public QStateMachine
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

public:
    explicit LogMachine(QObject *parent = nullptr);

public slots:
    void setup();
    void run();
    void enqueueMessage();
    void pulse();
    void initialize();
    void process();
    void format();
    void distribute();
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


public: // pointers
    QTimer * pulseTimer();

private:
    QState * mpInitializeState=nullptr;
    QState * mpProcessingState=nullptr;
    QState * mpFormattingState=nullptr;
    QState * mpDistributeState=nullptr;
    QFinalState * mpQuittingState=nullptr;
    QTimer * mpPulseTimer=nullptr;
    State mCurrentState=$nullState;
    QQueue<LogMessage> mMessageQueue;
    QQueue<LogItem> mItemQueue;
    QQueue<LogItem> mFormatedItemQueue;
    bool mLongPulse=true;
};

inline QTimer *LogMachine::pulseTimer() { Q_CHECK_PTR(mpPulseTimer); return mpPulseTimer; }


