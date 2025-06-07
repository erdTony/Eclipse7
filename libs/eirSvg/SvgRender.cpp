#include "SvgRender.h"

#include <QtSvg/QSvgRenderer>
#include <QFileInfo>
#include <QPainter>

SvgRender::SvgRender(QObject *parent)
    : QObject{parent}
    , mpRenderer(new QSvgRenderer(parent))
{
    setObjectName("SvgRender");
}

SvgRender::SvgRender(const QString svgFileName, QObject *parent)
    : QObject{parent}
    , mpRenderer(new QSvgRenderer(svgFileName, parent))
{
    setObjectName("SvgRender:" + QFileInfo(svgFileName).baseName());
}

QImage SvgRender::image(const QSize sz, const bool greyed)
{
    QImage result(sz, QImage::Format_ARGB32);
    result.fill(Qt::transparent);
    QPainter tPainter(&result);
    mpRenderer->render(&tPainter, QRect(QPoint(0,0), sz));
    tPainter.end();
    if (greyed)
        result.convertTo(QImage::Format_Grayscale8);
    return result;
}

QPixmap SvgRender::pixmap(const QSize sz, const bool greyed)
{
    return QPixmap::fromImage(image(sz, greyed));
}
