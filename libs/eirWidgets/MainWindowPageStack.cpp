#include "MainWindowPageStack.h"

#include <QStackedWidget>

#include "BaseWidgetApplication.h"

MainWindowPageStack::MainWindowPageStack(BaseWidgetApplication *bwa)
    : QMainWindow{}
    , mpApp(bwa)
    , mpStack(new QStackedWidget())
{
    setObjectName("MainWindowPageStack:" + app()->applicationName());
    stack()->setObjectName("QStackedWidget:" + app()->applicationName());
}
