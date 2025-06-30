#pragma once

#include <QObject>

#include <QColor>
class QTimer;

#include <BrightnessContrast.h>
#include <ByteHistogram.h>
#include <ColorImage.h>
#include <Grey16Image.h>
#include <IndexedImage.h>
#include <Rgba32Table.h>
#include <Types.h>

#include "SandboxApplication.h"
class SandboxScene;

class SandboxEngine : public QObject
{
    Q_OBJECT
public: // ctors
    explicit SandboxEngine(SandboxApplication *parent = nullptr);


public slots:
    void initialize(void);
    void configure(void) {;}
    void setup(void);
    void start(void);
    void process();

    void setSubjectImage(const ColorImage &ci);

signals:
    void initialized(void);
    void configured(void);
    void setuped(void);
    void started(void);
    void passComplete(const Count swaps);

public: // pointers
    SandboxApplication * app();
    SandboxScene * scene();
    QObject * object();


public: // const

public: // non-const

private slots:
    Count processOnce();

private:
    BrightnessContrast processHistogram(const Grey16Image aGrey16Image);
    void setupColorTable();
    void setupColorTableLinear(const BYTE aFrom,
                               const BYTE aTo,
                               const BYTE aOpacity,
                               const QColor aLoColor,
                               const QColor aHiColor);
    void setupColorTableBilinear(const BYTE aFrom,
                                const BYTE aTo,
                                const BYTE aOpacity,
                                const QColor aLoColor,
                                const QColor aMidColor,
                                const QColor aHiColor);

private:
    SandboxApplication * mpApplication=nullptr;
    QTimer * mpProcessTimer=nullptr;
    ColorImage mSubjectImage;
    Grey16Image mGrey16Image;
    IndexedImage mPreviousIndexedImage;
    IndexedImage mCurrentIndexedImage;
    Rgba32Table::RgbList mColorTable;
    ByteHistogram mGrey8Histogram;
};

inline SandboxApplication *SandboxEngine::app() { Q_ASSERT(mpApplication); return mpApplication; }
inline SandboxScene *SandboxEngine::scene() { return app()->scene(); }
inline QObject *SandboxEngine::object() { return parent(); }
