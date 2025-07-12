#pragma once
#include "eirWidgets.h"

#include <QObject>

#include <MatrixT.h>
#include <SCRect.h>

#include "GalleryProperties.h"
class GalleryFrame;

class EIRWIDGETS_EXPORT Gallery : public QObject
{
    Q_OBJECT
public: // types
    enum Mode
    {
        $null = 0,
        RollingRow          = 0x00000001,
        RollingCol          = 0x00000002,
        RollingGridByRow    = 0x00000004,
        RollingGridByCol    = 0x00000008,
        AlignTop            = 0x00000010,
        AlignRight          = 0x00000020,
        AlignBottom         = 0x00000040,
        AlignLeft           = 0x00000080,
    };
    Q_ENUM(Mode);
    Q_DECLARE_FLAGS(Modes, Mode);
    Q_FLAG(Modes);


public: // ctors
    explicit Gallery(QWidget *parent = nullptr);
    explicit Gallery(const Modes modes,
                     QWidget *parent = nullptr);


public slots:
    void setup();

signals:

public: // const

public: // non-const

public: // pointers
    GalleryFrame * frame();
    GalleryProperties props() const;
    GalleryProperties & props();
    QWidget * widget();

private:
    GalleryFrame * mpFrame=nullptr;
    GalleryProperties mProperties;
};

inline GalleryFrame *Gallery::frame() { Q_CHECK_PTR(mpFrame); return mpFrame; }
inline GalleryProperties &Gallery::props() { return mProperties; }
inline GalleryProperties Gallery::props() const { return mProperties; }
inline QWidget *Gallery::widget() { return (QWidget *)frame(); }
