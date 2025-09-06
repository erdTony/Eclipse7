#pragma once
#include "eirExe.h"

#include <QApplication>

class ExeSupport;

class EIREXE_EXPORT BaseWidgetApplication : public QApplication
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

