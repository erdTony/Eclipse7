#pragma once

#include <QObject>

#include <QColor>
#include <QImage>
class QTimer;

#include <Rgba32Table.h>
#include <Types.h>

class SandboxApplication;
//#include "SandboxApplication.h"

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


signals:
    void initialized(void);
    void configured(void);
    void setuped(void);
    void started(void);
    void frameSwapped(const Count swapPass,
                      const Count numSwaps,
                      const QImage &qi);
    void frameSwapFinished(void);
    void frameFlipped(const QImage &qi);


public: // const
    QImage subjectImage() const;
    QImage processImage() const;

public: // non-const
    void subjectImage(const QImage &qi);
    void processImage(const QImage &qi);

public: // pointers
    SandboxApplication * app();
    QObject * object();

private slots:
    void startFrame();
    void swapFrame();
    void finishFrame();
    void flipFrame();

private:
    Count processSwaps();
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
    QTimer * mpSwapTimer=nullptr;
    QImage mSubjectImage;
    QImage mProcessImage;
    Count mSwapCount;
    Rgba32Table::RgbList mColorTable;
};

inline QImage SandboxEngine::subjectImage() const { return mSubjectImage; }
inline QImage SandboxEngine::processImage() const { return mProcessImage; }
inline void SandboxEngine::processImage(const QImage &qi) { mProcessImage = qi; }
inline SandboxApplication *SandboxEngine::app() { Q_ASSERT(mpApplication); return mpApplication; }
inline QObject *SandboxEngine::object() { return parent(); }
