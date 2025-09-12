#pragma once
#include "eirBase.h"

#include <QApplication>

class QWidget;

class EIRBASE_EXPORT BaseWidgetApplication : public QApplication
{
    Q_OBJECT
public: // ctors
    BaseWidgetApplication(int &argc, char **argv);

public: // pointers


private:
};


