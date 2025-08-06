#pragma once

#include <QLineEdit>
#include <QWidget>

class LineEdit : public QLineEdit
{
    Q_OBJECT
public:
    LineEdit(QWidget *parent);
    LineEdit(const QString &text, QWidget *parent);
};
