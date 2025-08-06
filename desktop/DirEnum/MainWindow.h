#pragma once

#include <QMainWindow>

#include <Url.h>

#include "DirEnumProperties.h"
class EnumWindow;
class FileEnumerator;
class FileEnumParmWidget;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void setup();
    void start();
    void updateProperties();

signals:
    void propertyChanged();

private:
    EnumWindow * mpEnumWindow=nullptr;
    FileEnumParmWidget * mpParmWidget=nullptr;
    DirEnumProperties mProperties;
    Url mUrl;
    FileEnumerator * mpEnumerator=nullptr;
};
