#pragma once
#include "eirImage.h"

#include <QWidget>

#include <MatrixT.h>

class GalleryItem;
class GalleryScene;
class GalleryView;


class EIRIMAGE_EXPORT Gallery : public QWidget
{
    Q_OBJECT
public: // types
    enum Flag
    {
        $null = 0,
        ModeHorizontal      = 0x80000000,
        ModeVertical        = 0x40000000,
        ModeGrid            = 0x20000000,
        SelectNone          = $null,
        SelectSingle        = 0x08000000,
        SelectMultiple      = 0x04000000,
    };
    Q_DECLARE_FLAGS(Flags, Flag)
    Q_FLAG(Flags)

public: // ctors
    explicit Gallery(QWidget *parent = nullptr);

public slots:

signals:

public: // const

public: // non-const

public: // pointers

private:
    GalleryScene * mpScene=nullptr;
    GalleryView * mpView=nullptr;
//    Matrix<GalleryItem *> mViewMatrix;


    // =============== Properties ==============

private:
    int _flags;
    QColor _viewBackground;
    QColor _sceneBackground;
    QColor _itemBackground;
    QColor _selectColor;
    QColor _markColor;
    int _selectWidth;
    int _markWidth;
    bool _followEnabled;
    QSize _thumbSize;
    QSize _spacingSize;
    QSize _viewSize;
    QSize _itemLayout;

};

Q_DECLARE_OPERATORS_FOR_FLAGS(Gallery::Flags)
