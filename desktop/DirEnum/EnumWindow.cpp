#include "EnumWindow.h"

#include <QGridLayout>
#include <QTextEdit>

EnumWindow::EnumWindow(QWidget *parent)
    : QWidget{parent}
    , mpEdit(new QTextEdit(this))
{

}

void EnumWindow::setup()
{
    QGridLayout * pLayout = new QGridLayout;
    pLayout->addWidget(mpEdit);
    QWidget::setLayout(pLayout);
}

void EnumWindow::writeLine(const QString &s)
{
    mpEdit->append(s + "\n");
}
