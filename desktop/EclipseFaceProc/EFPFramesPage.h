#pragma once

#include <BaseMainWindowPage.h>

#include <GalleryProperties.h>
class Gallery;

class EFPFramesPage : public BaseMainWindowPage
{
    Q_OBJECT
public: // ctors
    EFPFramesPage(MainWindowPageStack *pMWPS);


public slots:
    void setup();

signals:

public: // const
    GalleryProperties props() const;

public: // non-const
    GalleryProperties & props();
    void setDefaultProperties(const Size baseGallerySize=Size(128));
    void readSettingsProperties();

public: // pointers
    Gallery * gallery();


private:
    Gallery * mpGallery=nullptr;
    GalleryProperties mGalleryProperties;
};

inline GalleryProperties EFPFramesPage::props() const { return mGalleryProperties; }
inline GalleryProperties & EFPFramesPage::props() { return mGalleryProperties; }
inline Gallery *EFPFramesPage::gallery() { Q_CHECK_PTR(mpGallery); return mpGallery; }
