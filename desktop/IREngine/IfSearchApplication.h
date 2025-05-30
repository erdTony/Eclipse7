#pragma once

#include <QApplication>
#include <QCommandLineParser>
#include <QDir>
#include <QFileInfo>

class QWidget;

#include "VersionInfo.h"

class IfSearchEngine;
class IfSearchWindow;

class IfSearchApplication : public QApplication
{
    Q_OBJECT
public: // types
    enum ShowOption
    {
        $null = 0,
        Minimized,
        Normalized,
        Maximized,
        FullScreen,
        NoShow,
        $max,
        Default = Normalized,
    };
    struct Options
    {
        QDir        inputDir = QDir("./input");
        QDir        baseOutputDir = QDir("./output/@");
        unsigned    minQuality = 300;
        unsigned    faceOverCrop = 125;
        unsigned    sampleMsec = 1000;
        unsigned    waitingMsec = 60000;
        ShowOption  show = $null;
        bool        loop = false;
        bool        deleteAfter = false;
        bool        finishedQuit = false;
        QFileInfo   frontalDetectorFI = QFileInfo("./Aim8A001-32-NoSplit.xml");
        QFileInfo   eyesDetectorFI = QFileInfo("./haarcascade_eye.xml");
        unsigned    frontalFactor = 100;
        QDir        markedDir = QDir("./Marked");
        QDir        noFaceDir = QDir("./NoFace");
        QDir        detectedFacesDir = QDir("./DetectedFaces");
        QDir        frontalObjdetDir = QDir("./FrontalObjdet");
        QDir        eyesObjdetDir = QDir("./EyesObjdet");
        QFileInfo   logFI = QFileInfo("./IfSearch.log");
    };

public: // ctors
    IfSearchApplication(int &argc, char **argv,
                        const VersionInfo vi);

public slots:
    void show();
    void start();

public: // const
    VersionInfo version() const;
    QFileInfo exeFileInfo() const;
    Options options() const;

public: // non-const
    void set(IfSearchWindow * win);
    void setupOptions();
    void parseOptions();
    void parseDetectors();
    void traceOptions();


public: // pointers
    Options & options();
    QCommandLineParser & parser();
    IfSearchWindow * win();
    IfSearchEngine * eng();

public: // static
    static Options defaultOptions();

private:
    const VersionInfo cmVersion;
    const QStringList cmCommandLine;
    const QFileInfo cmExeFI;
    IfSearchWindow * mpWindow=nullptr;
    IfSearchEngine * mpEngine=nullptr;
    QCommandLineParser mParser;
    Options mOptions;
};

inline VersionInfo IfSearchApplication::version() const { return cmVersion; }
inline QFileInfo IfSearchApplication::exeFileInfo() const { return cmExeFI; }
inline void IfSearchApplication::set(IfSearchWindow *win) { mpWindow = win; }
inline IfSearchApplication::Options IfSearchApplication::options() const { return mOptions; }
inline IfSearchApplication::Options IfSearchApplication::defaultOptions() { return Options(); }
inline IfSearchApplication::Options & IfSearchApplication::options() { return mOptions; }
inline QCommandLineParser & IfSearchApplication::parser() { return mParser; }
inline IfSearchWindow *IfSearchApplication::win() { Q_ASSERT(mpWindow); return mpWindow; }
inline IfSearchEngine *IfSearchApplication::eng() { Q_ASSERT(mpEngine); return mpEngine; }


