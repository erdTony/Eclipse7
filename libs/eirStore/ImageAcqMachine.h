#pragma once

#include <QObject>
#include <QStateMachine>

class ImageAcqMachine : public QStateMachine
{
    Q_OBJECT
public:
    ImageAcqMachine(QObject *parent = nullptr);
};
