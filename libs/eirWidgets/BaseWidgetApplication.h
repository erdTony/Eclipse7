#pragma once
#include "eirWidgets.h"

#include <QApplication>

class ExeSupport;

class EIRWIDGETS_EXPORT BaseWidgetApplication : public QApplication
{
    Q_OBJECT
public: // ctors
    BaseWidgetApplication(int &argc, char **argv);

public: // pointers
    ExeSupport * exe();


private:
    ExeSupport * mpExeSupport=nullptr;
};

inline ExeSupport *BaseWidgetApplication::exe() { Q_CHECK_PTR(mpExeSupport); return mpExeSupport; }

