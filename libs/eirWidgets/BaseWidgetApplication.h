#pragma once
#include "eirwidgets.h"

#include <QApplication>

class EIRWIDGETS_EXPORT BaseWidgetApplication : public QApplication
{
    Q_OBJECT
public:
    BaseWidgetApplication(int &argc, char **argv);
};
