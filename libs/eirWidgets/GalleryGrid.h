#pragma once

#include <QObject>

#include <QGridLayout>

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

public: // non-const
    void setup(const Size sz, GalleryCell * pCell);

public: // pointers
    Gallery * gallery() const;
    Gallery * gallery();


private:
    Gallery * mpGallery=nullptr;
    QGridLayout mGrid;
};


inline Gallery *GalleryGrid::gallery() { Q_CHECK_PTR(mpGallery); return mpGallery; }
inline QGridLayout *GalleryGrid::layout() { return &mGrid; }
inline Gallery *GalleryGrid::gallery() const { Q_CHECK_PTR(mpGallery); return mpGallery; }
