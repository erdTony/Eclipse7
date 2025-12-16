#pragma once
#include "eirCore.h"

#include <QApplication>

class QWidget;

class EIRCORE_EXPORT BaseWidgetApplication : public QApplication
{
    Q_OBJECT
public: // ctors
    BaseWidgetApplication(int &argc, char **argv);

public: // pointers


private:
};


