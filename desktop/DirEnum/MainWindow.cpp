#include "MainWindow.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QGridLayout>
#include <QTimer>
#include <QWidget>

#include <Log.h>
#include <Url.h>

#include "EnumWindow.h"
#include "FileEnumerator.h"
#include "FileEnumParmWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , mpEnumWindow(new EnumWindow(this))
    , mpParmWidget(new FileEnumParmWidget(this))
{
    QTimer::singleShot(100, this, &MainWindow::setup);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setup()
{
    Log::instance()->hookQtMsg();
    Log::instance()->add(new LogOutText(true));
    LOGHOOK();
    LOGOUTSTD();
    UINFOMSG("Starting " + QCoreApplication::applicationName()
            + QDateTime::currentDateTime().toString(" yyMMMdd hh:mm"));

    QGridLayout * pMainGrid = new QGridLayout;
    QWidget * pMainWidget = new QWidget(this);
    pMainWidget->setLayout(pMainGrid);
    setCentralWidget(pMainWidget);

    mpEnumWindow->setup();
    mpParmWidget->setup();
    pMainGrid->addWidget(mpParmWidget, 0, 0);
    pMainGrid->addWidget(mpEnumWindow, 0, 1);

}

void MainWindow::start()
{
    QDir tBaseDir = QDir::current();
    tBaseDir.cd("../EFPin");
    Url tUrl;
    tUrl.set(tBaseDir);
    qInfo() << Q_FUNC_INFO << tBaseDir << tUrl.string();
    mUrl = tUrl;
    mpEnumerator->start(mUrl);
}

void MainWindow::updateProperties()
{

}
