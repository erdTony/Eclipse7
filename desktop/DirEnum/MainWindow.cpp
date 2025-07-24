#include "MainWindow.h"

#include <QDir>
#include <QGridLayout>
#include <QTimer>
#include <QWidget>

#include <Url.h>

#include "EnumWindow.h"
#include "FileEnumerator.h"
#include "PropertyEditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , mpEnumWindow(new EnumWindow(this))
    , mpPropertyEditor(new PropertyEditor(this))
{
    QTimer::singleShot(100, this, &MainWindow::setup);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setup()
{
    QGridLayout * pMainGrid = new QGridLayout;
    QWidget * pMainWidget = new QWidget(this);
    pMainWidget->setLayout(pMainGrid);
    setCentralWidget(pMainWidget);

    mpEnumWindow->setup();
    mpPropertyEditor->setup();
    pMainGrid->addWidget(mpEnumWindow, 0, 0);
    pMainGrid->addWidget(mpPropertyEditor, 0, 1);

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
