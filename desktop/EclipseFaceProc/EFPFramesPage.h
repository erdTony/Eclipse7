#pragma once

#include <BaseMainWindowPage.h>

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

public: // non-const

public: // pointers
    Gallery * gallery();


private:
    Gallery * mpGallery=nullptr;
};

inline Gallery *EFPFramesPage::gallery() { Q_CHECK_PTR(mpGallery); return mpGallery; }
