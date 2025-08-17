#pragma once

#include <QObject>

#include <QGridLayout>

#include <MatrixT.h>
#include <Types.h>
class Point;
class Size;

class Gallery;
class GalleryCell;

class GalleryGrid : public QObject
{
    Q_OBJECT
public: // ctors
    explicit GalleryGrid(Gallery *parent);

public slots:

signals:
    void rowAdded(const int r);

public: // const
    QGridLayout * layout();
    Count count() const;
    Size size() const;

public: // non-const
    void setup(const Size sz);

public: // pointers
    GalleryCell * cell(const Index ix);
    Gallery * gallery() const;
    Gallery * gallery();


private:
    MatrixT<GalleryCell *> mCellMatrix;
    Gallery * mpGallery=nullptr;
    QGridLayout mGrid;
};


inline Gallery *GalleryGrid::gallery() { Q_CHECK_PTR(mpGallery); return mpGallery; }
inline QGridLayout *GalleryGrid::layout() { return &mGrid; }
inline Count GalleryGrid::count() const { return mCellMatrix.count(); }
inline Size GalleryGrid::size() const { return mCellMatrix.size(); }
inline Gallery *GalleryGrid::gallery() const { Q_CHECK_PTR(mpGallery); return mpGallery; }
