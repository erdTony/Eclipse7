#pragma once

#include <QObject>

#include <QImage>
#include <QPixmap>
#include <QString>

class QSvgRenderer;

class SvgRender : public QObject
{
    Q_OBJECT
public:
    explicit SvgRender(QObject *parent = nullptr);
    SvgRender(const QString svgFileName, QObject *parent = nullptr);

public slots:

signals:

public: // const
    QImage image(const QSize sz, const bool greyed=false);
    QPixmap pixmap(const QSize sz, const bool greyed=false);

public: // non-const


public: // pointers
    QSvgRenderer * renderer();

private:
    QSvgRenderer * mpRenderer;
};

inline QSvgRenderer *SvgRender::renderer() { Q_CHECK_PTR(mpRenderer);  return mpRenderer; }
