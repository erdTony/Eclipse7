#pragma once

#include <QApplication>

class BaseWidgetApplication : public QApplication
{
    Q_OBJECT
public:
    BaseWidgetApplication(int &argc, char **argv);
};
