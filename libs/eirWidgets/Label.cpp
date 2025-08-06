#include "Label.h"

Label::Label(QWidget *parent) : QLabel{parent} {;}
Label::Label(const QString &text, QWidget *parent) : QLabel(text, parent) {;}
Label::Label(const BYTE digits, QWidget *parent) : QLabel(QString(digits, '0'), parent) { set(""); }
Label::Label(const QPixmap &pxm, QWidget *parent, const QString &text) : QLabel(text, parent) { setPixmap(pxm); }
Label::Label(const QImage &img, QWidget *parent, const QString &text)  : QLabel(text, parent) { setPixmap(QPixmap::fromImage(img)); }

void Label::set(const QString &s)
{
    QLabel::setText(s);
}

void Label::set(const QPixmap &pxm)
{
    QLabel::setPixmap(pxm);
}

void Label::set(const QImage &img)
{
    set(QPixmap::fromImage(img));
}


