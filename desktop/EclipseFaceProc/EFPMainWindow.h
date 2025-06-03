#pragma once

#include <MainWindowPageStack.h>

class EFPSplash;

class EFPMainWindow : public MainWindowPageStack
{
    Q_OBJECT

public:
    EFPMainWindow(BaseWidgetApplication *bwa);
    ~EFPMainWindow();

public slots:
    void setup();

private:
    EFPSplash * mpSplash;
};


