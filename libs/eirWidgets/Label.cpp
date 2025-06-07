#include "Label.h"

Label::Label(QWidget *parent) : QLabel{parent} {;}
Label::Label(const QString &text, QWidget *parent) : QLabel(text, parent) {;}
Label::Label(const QPixmap &pxm, const QString &text, QWidget *parent) : QLabel(text, parent) { setPixmap(pxm); }
Label::Label(const QImage &img, const QString &text, QWidget *parent)  : QLabel(text, parent) { setPixmap(QPixmap::fromImage(img)); }

void Label::text(const QString &s)
{
    QLabel::setText(s);
}

void Label::pixmap(const QPixmap &pxm)
{
    QLabel::setPixmap(pxm);
}

void Label::pixmap(const QImage &img)
{
    pixmap(QPixmap::fromImage(img));
}


