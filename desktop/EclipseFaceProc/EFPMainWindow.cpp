#include "EFPMainWindow.h"

#include <QApplication>
#include <QTimer>

#include "EFPSplash.h"


EFPMainWindow::EFPMainWindow(BaseWidgetApplication *bwa)
    : MainWindowPageStack(bwa)
{
    qDebug() << Q_FUNC_INFO;
    setObjectName("EFPMainWindow:" + QApplication::applicationName());
    QTimer::singleShot(250, this, &EFPMainWindow::setup);
}

EFPMainWindow::~EFPMainWindow() {}

void EFPMainWindow::setup()
{
    qDebug() << Q_FUNC_INFO;
    MainWindowPageStack::setup();
    mpSplash = new EFPSplash(this);
    Q_CHECK_PTR(mpSplash);
    add(mpSplash);
    mpSplash->setup();
    show();
    qDebug() << Q_FUNC_INFO << "exit";
}
