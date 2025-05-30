#include "IfSearchApplication.h"

#include <QCommandLineOption>
#include <QStringList>
#include <QWidget>

#include "IfSearchEngine.h"
#include "IfSearchWindow.h"
#include "IfSearchWindow.h"
#include "IfSearchWindow.h"

IfSearchApplication::IfSearchApplication(int &argc, char **argv,
                                         const VersionInfo vi)
    : QApplication(argc, argv)
    , cmVersion(vi)
    , cmCommandLine(arguments())
    , cmExeFI(cmCommandLine.first())
{
    setObjectName("IfSearchApplication");
    setOrganizationName(version().getOrgName());
    setApplicationName(version().getAppName());
    setApplicationVersion(version().toString());
}

void IfSearchApplication::show()
{
    ShowOption tSO = options().show;
    if ($null == tSO) tSO = Default;
    qInfo() << Q_FUNC_INFO << options().show << tSO;
    switch (tSO)
    {
    case Minimized:    win()->showMinimized();      break;
    case Normalized:   win()->show();               break;
    case Maximized:    win()->showMaximized();      break;
    case FullScreen:   win()->showFullScreen();     break;
    case NoShow:                                    break;
    default: Q_ASSERT("options().show");            break;
    }
}

void IfSearchApplication::start()
{
    setupOptions();
    parseOptions();
    show();
    parseDetectors();
    traceOptions();
    mpEngine = new IfSearchEngine(this);
}

void IfSearchApplication::setupOptions()
{
    qInfo() << Q_FUNC_INFO;
    parser().setApplicationDescription("IfSearch Engine");
    parser().addHelpOption();
    parser().addVersionOption();
    parser().addPositionalArgument("InputDirectory",
                                   "Directory containing input images [default=./Input]");
    parser().addPositionalArgument("BaseOutputDirectory",
                                   "Destination Base Directory for Output Image Directories (@=timestamp) [default=./Output/@]");
    parser().addOption({"showmin", "Minimize Window."});
    parser().addOption({"shownorm", "Show Normal Window. [default]"});
    parser().addOption({"showmax", "Show Maximized Window."});
    parser().addOption({"showfull", "Show Full Screen."});
    parser().addOption({"shownone", "Do Not Show Windwo."});
    parser().addOption({{"q", "minQuality"},
                        "Set Minimum Detected Face Quality. [default 500]",
                        "100~900",
                        QString::number(defaultOptions().minQuality)});
    parser().addOption({{"z", "sampleMsec"},
                        "Process Input Directory Timer [default 1000]",
                        "0~60000",
                        QString::number(defaultOptions().sampleMsec)});
    parser().addOption({{"w", "waitingMsec"},
                        "Waiting for Input Directory Timer [default 60000]",
                        "0~600000",
                        QString::number(defaultOptions().waitingMsec)});
    parser().addOption({{"l", "loop"},
                        "Reprocess Input Directory"});
    parser().addOption({{"a", "deleteAfter"},
                        "Delete Images from Input Directory as Processed"});
    parser().addOption({{"e", "finishedQuit"},
                        "Quit after Processing Input Directory"});
    parser().addOption({{"f", "frontalDetector"},
                        "Select Frontal Detector by Name or File. [default Aim8A]"
                        "name/file",
                        defaultOptions().frontalDetectorFI.fileName()});
    parser().addOption({{"y", "eyesDetector"},
                        "Select Frontal Detector by Name or File. [default hc_eye]"
                        "name/file",
                        defaultOptions().eyesDetectorFI.fileName()});
    parser().addOption({{"x", "frontalFactor"},
                       "Set Frontal Detector Density Factor. [default 100]",
                       "10~5000",
                       QString::number(defaultOptions().frontalFactor)});
    parser().addOption({{"m", "markedDir"},
                       "Specify Marked Directory Name.",
                       "directory name",
                       defaultOptions().markedDir.path()});
    parser().addOption({{"n", "noFaceDir"},
                       "Specify No Faces Detected Directory Name.",
                       "directory name",
                       defaultOptions().noFaceDir.path()});
    parser().addOption({{"d", "detectedFacesDir"},
                       "Specify Detected Faces Directory Name.",
                       "directory name",
                       defaultOptions().detectedFacesDir.path()});
    parser().addOption({{"o", "frontalObjdetDir"},
                       "Specify Diagnostic Frontal Face Object Detection Directory Name.",
                       "directory name",
                       defaultOptions().frontalObjdetDir.path()});
    parser().addOption({{"r", "eyesObjdetDir"},
                        "Specify Diagnostic Eyes Object Detection Directory Name.",
                        "directory name",
                        defaultOptions().eyesObjdetDir.path()});
    parser().addOption({{"g", "logFile"},
                       "Specify Destination File Name for Logging. [default ./IfSearch.log]",
                       "file name",
                       defaultOptions().logFI.filePath()});
}

void IfSearchApplication::parseOptions()
{
    qInfo() << Q_FUNC_INFO;
    if ( ! parser().parse(cmCommandLine))
        qWarning() << "Parsing error";

    const QStringList cPositionalArgs = parser().positionalArguments();
    if (cPositionalArgs.count() > 0)
        options().inputDir = QDir(cPositionalArgs.at(0));
    if (cPositionalArgs.count() > 1)
        options().baseOutputDir = QDir(cPositionalArgs.at(1));

    const int cMinQuality = parser().value("minQuality").toInt();
    if (cMinQuality >= 100 && cMinQuality < 1000)
        options().minQuality = cMinQuality;
    const int cSampleMsec = parser().value("sampleMsec").toInt();
    if (cSampleMsec >= 0 && cSampleMsec < 60000)
        options().sampleMsec = cSampleMsec;
    const int cWaitingMsec = parser().value("waitingMsec").toInt();
    if (cWaitingMsec >= 0 && cWaitingMsec < 600000)
        options().waitingMsec = cWaitingMsec;
    ShowOption tShow = $null;
    if (parser().isSet("showmin")) tShow = Minimized;
    else if (parser().isSet("shownorm")) tShow = Normalized;
    else if (parser().isSet("showmax")) tShow = Maximized;
    else if (parser().isSet("showfull")) tShow = FullScreen;
    else if (parser().isSet("shownone")) tShow = NoShow;
    options().show = tShow;
    options().loop = parser().isSet("loop");
    options().deleteAfter = parser().isSet("deleteAfter");
    options().finishedQuit = parser().isSet("finishedQuit");
    const int cFrontalFactor = parser().value("frontalFactor").toInt();
    if (cFrontalFactor >= 10 && cFrontalFactor < 5000)
        options().frontalFactor = cFrontalFactor;
    options().markedDir = QDir("./Marked");
    options().noFaceDir = QDir("./NoFace");
    options().detectedFacesDir = QDir("./DetectedFaces");
    options().frontalObjdetDir = QDir("./FrontalObjdet");
    options().eyesObjdetDir = QDir("./EyesObjdet");
    options().logFI = QFileInfo(parser().value("logFile"));
}

void IfSearchApplication::parseDetectors()
{
    QString tFDName = parser().value("frontalDetector");
    QString tEDName = parser().value("eyesDetector");
    if (tFDName.isEmpty()) tFDName = defaultOptions().frontalDetectorFI.fileName();
    if (tEDName.isEmpty()) tEDName = defaultOptions().eyesDetectorFI.fileName();
    qInfo() << Q_FUNC_INFO << tFDName << tEDName;

    if (tFDName.endsWith(".xml", Qt::CaseInsensitive))
    {
        QDir tDetectorDir = cmExeFI.dir();
        if ( ! tDetectorDir.cd("detectors"))
            qWarning() << "Unable to cd detectors: "
                       << tDetectorDir.absolutePath();
        options().frontalDetectorFI = QFileInfo(tDetectorDir, tFDName);
    }
    else
    {
        qCritical() << "Detector Names not yet supported";
    }

    if (tEDName.endsWith(".xml", Qt::CaseInsensitive))
    {
        QDir tDetectorDir = cmExeFI.dir();
        if ( ! tDetectorDir.cd("detectors"))
            qWarning() << "Unable to cd detectors: "
                       << tDetectorDir.absolutePath();
        options().eyesDetectorFI = QFileInfo(tDetectorDir, tEDName);
    }
    else
    {
        qCritical() << "Detector Names not yet supported";
    }

}

void IfSearchApplication::traceOptions()
{
    const QStringList cPosArgs = parser().positionalArguments();
    const QStringList cOptNames = parser().optionNames();
    const QStringList cBadOpts = parser().unknownOptionNames();
    qDebug() << "Executable:" << cmExeFI.absoluteFilePath();
    qDebug() << "Positional Arguments:";
    foreach (const QString cPA, cPosArgs)
        qDebug() << "   " << cPA;
    qDebug() << "Specified Options:";
    foreach (const QString cON, cOptNames)
        qDebug() << "   " << cON << "=" << parser().value(cON);
    qDebug() << "Unrecognized Options:";
    foreach (const QString cBO, cBadOpts)
        qDebug() << "   " << cBO << "=" << parser().value(cBO);
    qDebug() << "Frontal Detector:"
             << options().frontalDetectorFI.absoluteFilePath()
             << options().frontalDetectorFI.exists();
    qDebug() << "Eyes Detector:"
             << options().eyesDetectorFI.absoluteFilePath()
             << options().eyesDetectorFI.exists();
}

