#pragma once
#include "eirGraphics.h"

#include <QObject>

#include "GalleryProperties.h"
class GalleryFrame;
class GalleryScene;
class GalleryView;

class EIRGRAPHICS_EXPORT Gallery : public QObject
{
    Q_OBJECT
public: // types
    enum Option
    {
        $null = 0,
        RollingGrid = 0x00000001,
    };
    Q_ENUM(Option);
    Q_DECLARE_FLAGS(Options, Option);
    Q_FLAG(Options);

public: // ctors
    explicit Gallery(QWidget *parent = nullptr);


public slots:
    void setup();

signals:

public: // const

public: // non-const

public: // pointers
    GalleryFrame * frame();
    GalleryProperties props() const;
    GalleryProperties & props();
    GalleryScene * scene();
    GalleryView * view();
    QWidget * widget();

private:
    GalleryFrame * mpFrame=nullptr;
    GalleryProperties mProperties;
    GalleryScene * mpScene=nullptr;
    GalleryView * mpView=nullptr;

};

inline GalleryFrame *Gallery::frame() { Q_CHECK_PTR(mpFrame); return mpFrame; }
inline GalleryProperties &Gallery::props() { return mProperties; }
inline GalleryProperties Gallery::props() const { return mProperties; }
inline GalleryScene *Gallery::scene() { Q_CHECK_PTR(mpScene); return mpScene; }
inline GalleryView *Gallery::view() { Q_CHECK_PTR(mpView); return mpView; }
inline QWidget *Gallery::widget() { return (QWidget *)frame(); }
