#pragma once

#include <QMainWindow>

#include <Url.h>

#include "DirEnumProperties.h"
class EnumWindow;
class FileEnumerator;
class PropertyEditor;


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
    PropertyEditor * mpPropertyEditor=nullptr;
    DirEnumProperties mProperties;
    Url mUrl;
    FileEnumerator * mpEnumerator=nullptr;
};
