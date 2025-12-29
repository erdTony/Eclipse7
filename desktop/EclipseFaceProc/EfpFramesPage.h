#pragma once

#include <BaseMainWindowPage.h>

#include <QDir>

#include "FileInfo.h"
//#include <GalleryProperties.h>
class Gallery;
class Label;
class Url;

class EfpImageReader;

class EfpFramesPage : public BaseMainWindowPage
{
    Q_OBJECT
public: // ctors
    EfpFramesPage(QWidget *parent=nullptr);


public slots:
    virtual void setup();
    virtual void activate();
    void start(const QDir &dir);
    void hasCaptured(const FileInfo &fi, const QImage qi);

signals:

public: // const
//    GalleryProperties props() const;

public: // non-const
    void setDefaultProperties(const Size baseGallerySize=Size(128));
    void readSettingsProperties();

public: // pointers
//    GalleryProperties & props();
    EfpImageReader * reader();
    Gallery * gallery();


private:
    EfpImageReader * mpImageReader=nullptr;
    Label * mpFrameLabel=nullptr;
    Label * mpDetectLabel=nullptr;
    Gallery * mpGallery=nullptr;
//    GalleryProperties mGalleryProperties;
};

//inline GalleryProperties EfpFramesPage::props() const { return mGalleryProperties; }
//inline GalleryProperties & EfpFramesPage::props() { return mGalleryProperties; }
inline EfpImageReader *EfpFramesPage::reader() { Q_CHECK_PTR(mpImageReader); return mpImageReader; }
inline Gallery *EfpFramesPage::gallery() { Q_CHECK_PTR(mpGallery); return mpGallery; }
