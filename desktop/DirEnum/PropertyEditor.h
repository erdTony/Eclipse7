#pragma once

#include <QWidget>

class PropertyEditor : public QWidget
{
    Q_OBJECT
public:
    explicit PropertyEditor(QWidget *parent = nullptr);

public slots:
    void setup();

signals:
};
