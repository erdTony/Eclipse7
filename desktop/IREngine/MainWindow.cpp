#include "MainWindow.h"

#include <QtDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setObjectName("IREngine:MainWindow");
    QTimer::singleShot(500, this, &MainWindow::init);
}

MainWindow::~MainWindow() {;}

void MainWindow::init()
{
    qInfo() << Q_FUNC_INFO;

    QTimer::singleShot(100, this, &MainWindow::setup);
}

void MainWindow::setup()
{

}

void MainWindow::start()
{

}

void MainWindow::run()
{

}

void MainWindow::pulse()
{

}
