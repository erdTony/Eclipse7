#pragma once

#include <MainWindowPageStack.h>

class EFPMainWindow : public MainWindowPageStack
{
    Q_OBJECT

public:
    EFPMainWindow(BaseWidgetApplication *bwa);
    ~EFPMainWindow();
};


