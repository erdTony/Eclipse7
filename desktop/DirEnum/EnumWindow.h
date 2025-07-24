#pragma once

#include <QWidget>

class QTextEdit;

class EnumWindow : public QWidget
{
    Q_OBJECT
public:
    explicit EnumWindow(QWidget *parent = nullptr);

public slots:
    void setup();
    void writeLine(const QString &s);

signals:

private:
    QTextEdit *mpEdit=nullptr;
};
