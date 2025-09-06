#include "Label.h"

#include <QPainter>

#include <SCRect.h>

Label::Label(QWidget *parent) : QLabel{parent} {;}
Label::Label(const QString &text, QWidget *parent) : QLabel(text, parent) {;}
Label::Label(const BYTE digits, QWidget *parent) : QLabel(QString(digits, '0'), parent) { set(""); }
Label::Label(const QPixmap &pxm, QWidget *parent, const QString &text) : QLabel(text, parent) { setPixmap(pxm); }
Label::Label(const QImage &img, QWidget *parent, const QString &text)  : QLabel(text, parent) { setPixmap(QPixmap::fromImage(img)); }
Label::Label(const Size sz, const QColor &clr, QWidget *parent) : QLabel(parent) { set(sz, clr); }
Label::Label(const Size sz, const QImage &img, QWidget *parent, const QString &text)
    : QLabel(text, parent) { set(sz, img); }

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

void Label::set(const Size sz, const QColor &clr)
{
    QPixmap tPixmap(sz);
    tPixmap.fill(clr);
    set(tPixmap);
}

void Label::set(const Size sz, const QImage &img)
{
    const Size cOrigSize = img.size();
    const Size cScaledSize(sz, cOrigSize.aspect());
    const SCRect cCenteredRect(cScaledSize);
    QPixmap tPixmap(sz);
    QPainter tPainter;
    tPainter.begin(&tPixmap);
    tPainter.fillRect(SCRect(sz).toQRect(), Qt::transparent);
    tPainter.drawImage(cCenteredRect.toQRect(), img);
    tPainter.end();
    set(tPixmap);
}



