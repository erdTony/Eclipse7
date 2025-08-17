#pragma once
#include "eirWidgets.h"

#include <QObject>

#include <MatrixT.h>
#include <Point.h>
#include <SCRect.h>
#include <Types.h>

#include "GalleryProperties.h"
class GalleryCell;
class GalleryFrame;
class GalleryGrid;

class EIRWIDGETS_EXPORT Gallery : public QObject
{
    Q_OBJECT
public: // types
    enum Mode
    {
        $nullMode = 0,
        RollingRow          = 0x00000001,
        RollingCol          = 0x00000002,
        RollingGridByRow    = 0x00000004,
        RollingGridByCol    = 0x00000008,
        AlignTop            = 0x00000010,
        AlignRight          = 0x00000020,
        AlignBottom         = 0x00000040,
        AlignLeft           = 0x00000080,
        ImageScale          = 0x80000000,
        ImageCrop           = 0x40000000,
        ImageAspect         = 0x20000000,
    };
    Q_ENUM(Mode);
    Q_DECLARE_FLAGS(Modes, Mode);
    Q_FLAG(Modes);


public: // ctors
    explicit Gallery(QWidget *parent = nullptr);


public slots:
    void setup(const GalleryProperties gp);
    void add(const QImage &qi);

signals:

public: // const

public: // non-const
    void modes(const Modes fs);
    void props(const GalleryProperties ps);
    void set(const Point pt, GalleryCell * pCell);

public: // pointers
    GalleryGrid * grid();
    GalleryProperties props() const;
    GalleryProperties & props();
    QWidget * widget();

private:
    Modes mModes=$nullMode;
    GalleryGrid * mpGrid=nullptr;
    QWidget * mpGalleryWidget=nullptr;
    GalleryProperties mProperties;
    Index mCurrentIndex=0;
};


inline void Gallery::modes(const Modes fs) { mModes = fs; }
inline void Gallery::props(const GalleryProperties ps) { mProperties = ps; }
inline GalleryGrid *Gallery::grid() { Q_CHECK_PTR(mpGrid); return mpGrid; }
inline GalleryProperties &Gallery::props() { return mProperties; }
inline GalleryProperties Gallery::props() const { return mProperties; }
inline QWidget *Gallery::widget() { Q_CHECK_PTR(mpGalleryWidget); return mpGalleryWidget; }
