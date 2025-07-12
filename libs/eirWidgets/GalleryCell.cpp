#include "GalleryCell.h"

#include "Gallery.h"

GalleryCell::GalleryCell(Gallery *parent) : QLabel{parent->widget()}, mpGallery(parent) {;}

GalleryProperties GalleryCell::props() const { return gallery()->props(); }

GalleryProperties &GalleryCell::props() { return gallery()->props(); }
