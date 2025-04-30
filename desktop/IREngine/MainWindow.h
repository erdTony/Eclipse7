#pragma once

#include <QMainWindow>

class QStackedWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public: // ctors
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void init();
    void setup();
    void start();
    void run();
    void pulse();

public: // const

public: // non-const

private:
    QStackedWidget * mpMainStack;
};
