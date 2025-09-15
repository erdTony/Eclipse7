#pragma once

#include <BaseMainWindowPage.h>

#include <GalleryProperties.h>
class Gallery;
class Label;
class Url;

class EfpFramesPage : public BaseMainWindowPage
{
    Q_OBJECT
public: // ctors
    EfpFramesPage(QWidget *parent=nullptr);


public slots:
    virtual void setup();
    virtual void activate();
    void start(const Url &url);

signals:

public: // const
    GalleryProperties props() const;

public: // non-const
    void setDefaultProperties(const Size baseGallerySize=Size(128));
    void readSettingsProperties();

public: // pointers
    GalleryProperties & props();
    Gallery * gallery();


private:
    Label * mpFrameLabel=nullptr;
    Label * mpDetectLabel=nullptr;
    Gallery * mpGallery=nullptr;
    GalleryProperties mGalleryProperties;
};

inline GalleryProperties EfpFramesPage::props() const { return mGalleryProperties; }
inline GalleryProperties & EfpFramesPage::props() { return mGalleryProperties; }
inline Gallery *EfpFramesPage::gallery() { Q_CHECK_PTR(mpGallery); return mpGallery; }
