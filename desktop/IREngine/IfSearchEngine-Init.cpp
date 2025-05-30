#include "IfSearchEngine.h"

#include <QApplication>
#include <QDateTime>
#include <QLibraryInfo>
#include <QProcessEnvironment>
#include <QString>
#include <QTimer>

#include <ObjdetCatalog.h>
#include <ObjdetEyes.h>
#include <IfSearchApplication.h>
#include <IfSearchWindow.h>

#include <DDTcore.h>
#include <Detector.hhh>
#include <EigenFace.h>
#include <EigenFaceData.h>
#include <EigenFaceGenerator.h>
#include <EigenFaceSearcher.h>
#include <EigenFaceSearchTier.h>
#include <EigenFaceSimilarity.h>
#include <FaceBase.h>
#include <FileWriteProfile.h>
#include <FileWriter.h>
#include <ImageCache.h>
#include <ImageSource.h>
#include <INDIffd.h>
#include <InputHotdir.h>
#include <Objdet.h>
#include <ObjdetFrontal.h>
#include <ObjdetRawArguments.h>
#include <Return.h>
#include <Settings.h>
#include <VersionInfo.h>
#include <Resolver.h>
#include <ClothesMatchProperties.h>
#include <HeightGrid.h>
#include <SkinMatcher.h>
#include <SkinMatchProperties.h>


void IfSearchEngine::init(void)
{
    qDebug() << Q_FUNC_INFO;
#ifdef BUILD_OBJDET_EVAL
    mBaseTimestamp = QDateTime::currentDateTime();


#endif
#ifndef TODO0002
    Return rtn;
    QStringList qsl;
    appSettings->setPollCountKey("Options/PollCount");
    if (appSettings->value("Output/LogStdout", true).toBool())
        Info::add(new InfoOutputFile(stdout));

    QString sDetail = optLogDetail->toString();
    Info::Severity logDetail = Info::Severity::Info;
    if (0 == sDetail.compare("Null", Qt::CaseInsensitive))
        logDetail = Info::Severity::Null;
    else if (0 == sDetail.compare("Leave", Qt::CaseInsensitive))
        logDetail = Info::Severity::Leave;
    else if (0 == sDetail.compare("Enter", Qt::CaseInsensitive))
        logDetail = Info::Severity::Enter;
    else if (0 == sDetail.compare("Detail", Qt::CaseInsensitive))
        logDetail = Info::Severity::Detail;
    else if (0 == sDetail.compare("Debug", Qt::CaseInsensitive))
        logDetail = Info::Severity::Debug;
    else if (0 == sDetail.compare("Info", Qt::CaseInsensitive))
        logDetail = Info::Severity::Info;
    else if (0 == sDetail.compare("Progress", Qt::CaseInsensitive))
        logDetail = Info::Severity::Progress;
    else if (0 == sDetail.compare("Warning", Qt::CaseInsensitive))
        logDetail = Info::Severity::Warning;
    else if (0 == sDetail.compare("Error", Qt::CaseInsensitive))
        logDetail = Info::Severity::Error;
    else if (0 == sDetail.compare("Fatal", Qt::CaseInsensitive))
        logDetail = Info::Severity::Fatal;
    QString logFileName = optLogFile->toString();
    if (0 != logFileName.compare("none", Qt::CaseInsensitive))
    {
        QDir logDir(writer->baseDir());
        if (logFileName.isEmpty())
            logFileName = "./log/IfSearch-@.log";
        QFileInfo fi(logFileName);
        if (fi.isDir())
            logFileName += "/IfSearch-@.log";
        logFileName = logDir.absoluteFilePath(logFileName);
        Info::add(new InfoOutputFile(logFileName),
                       logDetail.isValid() ? logDetail : Info::Severity::Info);
    }

    Info::add(infoSetting, Info::Severity::Warning,
                                Info::Severity::Fatal);
    Info::start(QThread::NormalPriority);
    PROGRESS("%3 %1 built %2", version.toString(),
             version.dateTimeString(), version.getAppName());
    INFO(version.getCopyright());
    INFO(appSettings->programName());
    DETAIL("Running ProcessId=%1", applicationPid());
#else
    qInfo() << cmVersion.toString() << cmVersion.dateTimeString() << cmVersion.getAppName();
    qInfo() << cmVersion.getAppName() << cmVersion.getCopyright();
    qInfo() << "Running ProcessId:" << QApplication::applicationPid();
#endif

#ifndef TODO0002
    qreal rolloverHours = appSettings->value("Output/RolloverHours").toReal();
    int rolloverKeep = appSettings->value("Output/RolloverKeep").toInt();
    if ( ! qIsNull(rolloverHours))
    {
        Info::setRolloverKeep(rolloverKeep);
        MillisecondDelta msd;
        msd.setHours(rolloverHours);
        rolloverTimer = new QTimer(this);
        rolloverTimer->setInterval(msd.msec());
        if (connect(rolloverTimer, SIGNAL(timeout()), this, SLOT(logRollover())))
        {
            INFO("Log Rollover started for %1 hours keeping %2",
                 rolloverHours, rolloverKeep);
            rolloverTimer->start();
        }
        else
        {
            ERRMSG("Error CONNECTing logRollover() slot");
        }
    }
    detectorsXml     = appSettings->value("Detect/DetectorsXml", "../detectors/Detectors.xml").toString();
    mpObjdetCatalog = new ObjdetCatalog(detectorsXml, this); Q_ASSERT(mpObjdetCatalog);
#endif
    qInfo() << "Running Qt Version" << qVersion();
    qInfo() << "Running OpenCV Version" << Objdet::cvVersion().toString();

#ifndef TODO0002
    eigenFaceDataDir = appSettings->value("Generate/DataDir", "../data/Face1").toString();
    faceBaseBaseDir  = appSettings->value("FaceBase/BaseDir", "../FaceBase").toString();
    faceBaseMaxLoad  = appSettings->value("FaceBase/MaxLoad", 50).toInt();
    faceBaseReload_msd.setToMinutes(appSettings->value("FaceBase/ReloadMins", 0.0).toFloat());
#endif

#ifndef TODO0002
    EigenFaceSearchTier::setColor(EigenFaceSearchTier::Best,
                                 appSettings->value("Output/MarkBestColor",
                                                    EigenFaceSearchTier::color(EigenFaceSearchTier::Best)).value<QColor>());
    EigenFaceSearchTier::setColor(EigenFaceSearchTier::Strong,
                                 appSettings->value("Output/MarkStrongColor",
                                                    EigenFaceSearchTier::color(EigenFaceSearchTier::Strong)).value<QColor>());
    EigenFaceSearchTier::setColor(EigenFaceSearchTier::Possible,
                                 appSettings->value("Output/MarkPossibleColor",
                                                    EigenFaceSearchTier::color(EigenFaceSearchTier::Possible)).value<QColor>());
    EigenFaceSearchTier::setColor(EigenFaceSearchTier::Weak,
                                 appSettings->value("Output/MarkWeakColor",
                                                    EigenFaceSearchTier::color(EigenFaceSearchTier::Weak)).value<QColor>());

    optSearchCommand->setValue(QString());
    optEnrollCommand->setValue(QString());
    optRetrieveCommand->setValue(QString());
#endif

    QTimer::singleShot(0, this, SLOT(start()));
} // init()

void IfSearchEngine::start(void)
{
    qDebug() << Q_FUNC_INFO;
#ifdef BUILD_OBJDET_EVAL
    const QString cDetectorsXmlName("./detectors/Detectors.XML");
    const QString cDetectorClassName("FaceFrontal");
    const QString cDetectorName(""); // blank=default
#if 0
    ObjdetCatalog * pCatalog = new ObjdetCatalog(cDetectorsXmlName, this);
    Q_ASSERT(pCatalog);
    if ( ! pCatalog->fileExists())
        qFatal() << pCatalog->fileInfo().absoluteFilePath() << "catalog file does not exist";

    const ObjdetCatalogItem::Key cKey(cDetectorClassName, cDetectorName);
    const ObjdetCatalogItem cItem = pCatalog->item(cKey);
    if ( ! cItem.xmlFileExists())
        qFatal() << cItem.xmlFileInfo().absoluteFilePath() << "catalog item does not exist";
#endif
    if (mpFrontal)
    {
        mpFrontal->unloadDetector();
        mpFrontal->deleteLater();
    }
    mpFrontal = new ObjdetFrontal(this);
    mpFrontal->loadDetectorXml("./detectors/Aim8A001-32-NoSplit.xml");
    if ( ! mpFrontal->isDetectorLoaded())
        qFatal() << "Failed to load:" << mpFrontal->detectorFileInfo();
    if (mpEyes)
    {
        mpEyes->unloadDetector();
        mpEyes->deleteLater();
    }
    mpEyes = new ObjdetEyes(this);
    mpEyes->loadDetectorXml("./detectors/haarcascade_eye.xml");
    if ( ! mpEyes->isDetectorLoaded())
        qFatal() << "Failed to load:" << mpEyes->detectorFileInfo();

    //pCatalog->deleteLater(); pCatalog = nullptr;
#endif
#ifndef TODO0002
    Return rtn;
    QStringList qsl;

    /*--- Setup Clothes Matcher ---*/
    appSettings->objectProperties(clothesMatchProperties, tr("Clothes", "config"), clothesMatchProperties->dynamicPropertyNames(), Settings::Volatile);

    /*--- Initialize Height Grid ---*/
    heightGrid = new HeightGrid(this);
    Q_ASSERT(heightGrid);
    connect(heightGrid, SIGNAL(error(QString)), this, SLOT(error(QString)));
    appSettings->objectProperties(heightGrid, tr("Height", "config"), heightGrid->dynamicPropertyNames(), Settings::Volatile);

    /*--- Setup Skin Matchers ---*/
    appSettings->beginGroup("FaceColor");
    qsl = appSettings->childGroups();
    appSettings->endGroup();
    foreach (QString name, qsl)
    {
        SkinMatchProperties * smp = new SkinMatchProperties(name, this);
        appSettings->objectProperties(smp, "FaceColor/" + name, DDTcore::propertyNames(smp), Settings::Volatile);
        FileWriteProfile * fwpOutput = writer->newProfile(name+"-Output", FileWriter::FaceImage, "FaceColor/"+name+"/OutputDir");
        FileWriteProfile * fwpMarked = writer->newProfile(name+"-Marked", 0, "FaceColor/"+name+"/MarkedDir");
        // TODO: InputImageDir properties
        skinMatcher->add(name, smp);
        fwpsFaceColor.insert(name+"-Output", fwpOutput);
        fwpsFaceColor.insert(name+"-Marked", fwpMarked);
    }
    // TODO: Global SkinMatcher properties: RegionScale, Regions

    /*--- Color Correction ---*/
//    Q_ASSERT(ccProps);
//    Q_ASSERT(colorCorrection);
//    appSettings->objectProperties(&ccProps, tr("ColorCorrection", "config"), ccProps.dynamicPropertyNames());

    /*--- Setup Transform ---*/
    appSettings->objectProperties(&xformProps, tr("PreProcess", "config"), xformProps.dynamicPropertyNames(), Settings::Volatile);

    /*--- Setup Resolver ---*/
    resolver = new Resolver(this);  Q_ASSERT(resolver);
    qsl.clear(); qsl << "Quality" << "Consistency" << "FaceColor"
                     << "UpperClothes" << "LowerClothes" << "Height";
    foreach (IdString name, qsl)
    {
        Setting * opt = new Setting(appSettings, "Resolve/" + name, 0, Settings::Volatile);
        int weight = opt->toInt();
        resolver->add(name, weight);
    }

    /*--- Setup Performance Writers ---*/
    QString fpFileName = appSettings->value("Output/FramePerformanceFile", QString()).toString();
    if ( ! fpFileName.isEmpty())
    {
        fpFileName = writer->baseDir().absoluteFilePath(fpFileName);
        fpWriter = new CsvWriter(fpFileName);
        Q_ASSERT(fpWriter);
        if (fpWriter->isOpen())
        {
            frameStatistics = new FrameStatistics;
            Q_ASSERT(frameStatistics);
            framePerformance = new FramePerformance;
            Q_ASSERT(framePerformance);
            fpWriter->add(framePerformance);
            fpWriter->add(frameStatistics);
            fpWriter->header();
            PROGRESS("FramePerformanceFile %1 started", fpFileName);
        }
        else
        {
            ERRMSG("Unable to write FramePerformanceFile %1: %2", fpFileName, fpWriter->errorString());
            delete fpWriter;
            fpWriter = 0;
        }

    }


    appSettings->objectProperty(appSettings,
                                tr("Options", "config"),
                                tr("UpdateMsec", "config"),
                                Settings::Volatile);
    connect(appSettings, SIGNAL(valueChanged(QString)),
            this, SLOT(changed(QString)));
    connect(appSettings, SIGNAL(propertyChanged(QString)),
            this, SLOT(changed(QString)));
    connect(appSettings, SIGNAL(valueChanged(QString)),
            writer, SLOT(settingChanged(QString)));

    connect(writer, SIGNAL(directorySet(QString,QString)),
            this, SLOT(directorySet(QString,QString)));
    connect(writer, SIGNAL(fileWritten(QString)),
            this, SLOT(fileWritten(QString)));
    connect(writer, SIGNAL(error(QString)),
            this, SLOT(error(QString)));

    resultsDelimiter = appSettings->value("Options/Delimiter", "^").toString();
    if ( ! check(368))
        return;

    rtn = initEigenFace();
    RETURN(rtn);
    if (rtn.isError() || rtn.isFalse())
    {
        QTimer::singleShot(0, this, SLOT(done()));
        return;
    }

    PROGRESS("Initializing INDI FaceBase");
    faceBase = new FaceBase(this, eigenMatcher);	Q_ASSERT(faceBase);
    INFO("from %1", faceBaseBaseDir);
    rtn = faceBase->initialize(faceBaseBaseDir, faceBaseMaxLoad);
    RETURN(rtn);
    if (rtn.isError() || rtn.isFalse())
    {
        QTimer::singleShot(0, this, SLOT(done()));
        return;
    }

    if ( ! faceBaseReload_msd.isNull())
    {
        reloadTimer = new QTimer(this);
        reloadTimer->setInterval(faceBaseReload_msd.msec());
        connect(reloadTimer, SIGNAL(timeout()), this, SLOT(reload()));
        reloadTimer->start();
    }
#endif
    QTimer::singleShot(0, this, SLOT(run()));
} // start()

void IfSearchEngine::run(void)
{
    qDebug() << Q_FUNC_INFO;
#ifdef BUILD_OBJDET_EVAL

    getInputFiles();

    mOutputBaseDir.cd(app()->exeFileInfo().dir().absolutePath());
    QString tOutputBaseDirName = options().baseOutputDir.path();
    tOutputBaseDirName.replace('@', QDateTime::currentDateTime()
                                        .toString("DyyyyMMdd-Thhmm"));
    mOutputBaseDir.mkpath(tOutputBaseDirName);
    if ( ! mOutputBaseDir.cd(tOutputBaseDirName))
        qCritical() << "Can't set base output directory";
    mMarkedDir = mNoFaceDir = mFrontalObjDetDir
            = mDetectedFacesDir = mOutputBaseDir;
    qDebug() << mOutputBaseDir << mMarkedDir << mDetectedFacesDir;
    if ( ! mMarkedDir.mkpath(options().markedDir.path()))
        qCritical() << "Can't make marked output directory";
    if ( ! mNoFaceDir.mkpath(options().noFaceDir.path()))
        qCritical() << "Can't make no faces detected output directory";
    if ( ! mDetectedFacesDir.mkpath(options().detectedFacesDir.path()))
        qCritical() << "Can't make detected faces output directory";
    if ( ! mFrontalObjDetDir.mkpath(options().frontalObjdetDir.path()))
        qCritical() << "Can't make objdet output directory";
    qDebug() << mOutputBaseDir << mMarkedDir << mDetectedFacesDir;
    if ( ! mMarkedDir.cd(options().markedDir.path()))
        qCritical() << "Can't set marked output directory";
    if ( ! mNoFaceDir.cd(options().noFaceDir.path()))
        qCritical() << "Can't set no faces detected output directory";
    if ( ! mDetectedFacesDir.cd(options().detectedFacesDir.path()))
        qCritical() << "Can't set detected faces output directory";
    if ( ! mFrontalObjDetDir.cd(options().frontalObjdetDir.path()))
        qCritical() << "Can't set objdet output directory";
    qDebug() << mOutputBaseDir << mMarkedDir << mDetectedFacesDir;
    app()->win()->clearPixmaps();
#endif
#ifndef TODO0002
    FUNCTION();
#ifdef ENABLE_AVGFACE
    if (optAvgFaceEnable->toBool())
        avgFaceInit();
#endif

    appSettings->setValue(optShutdown->keyName(), false);
    appSettings->startTimers();
    appSettings->dump(Info::Severity::Info);

    writer->start();
    writer->pumpAll();
    writer->dump();

    if (fwpRecon->isActive())
    {
        QImage avg = eigenData->meanFaceImage();
        fwpRecon->write(avg, "AvgFace");
    }

    changed(optHeightEnable->keyName());
    changed(optInput->keyName());
    changed(optPause->keyName());
#endif
    QTimer::singleShot(0, this, SLOT(pulse()));
} // run()

#if 0
#define DLL
#include "C:/CrypKey SDK/Build 7723/Include/crypkey.h"

#define MASTER_KEY \
    "6a6167abf35cb0253b91761971cfcecfe79b6935d6e77905f5b29a45badd3a4f"  \
    "21315cee18798f96ef1861455c0f18643746f1183580caa6a3f5ef6d8e3dd7e15" \
    "da0f3ab21414b8fbe549d385552f816406b15040070d636ab2153d715e71c6c2e" \
    "eda08f58503f64ce9183759075949ff249013d045b55907aa6924c5d707546"

#define USER_KEY "D050 815C D1A2 A79D B1"

#define CHECKPERIOD 15


bool IfSearch::initLicense(void) const
{
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    DETAIL("System Environment:");
    foreach(QString var, env.toStringList())
        DETAIL(var);
#if 0
    PROGRESS("Initializing SDK1 License");

    int code = -85;
    unsigned long level = 0;

    // --- Try to initialize Crypkey
    QString phase("Init");
    QString path(appSettings->programName());
#if 1 // Crypkey trial period
    QFileInfo fi(path);
    fi.setFile("EXAMPLE.EXE");
    path = fi.absoluteFilePath();
#endif
    char bstr[MAX_PATH];
    qstrcpy(bstr, qPrintable(QDir::toNativeSeparators(path)));
    code = InitCrypkey(bstr,
                       MASTER_KEY,
                       USER_KEY,
                       FALSE, /* No Floppy License */
                       3 * CHECKPERIOD);

    // --- Try Crypkey Authorization
    if (INIT_OK == code)
    {
        code = GetAuthorization(&level, 0);

    }


    // --- We're done one way or the other
    if (code)
    {
        ERRMSG("Licensing Failed; code=%1 during %2", code, phase);
        INFO("Please contact EclipseIR to resolve at");
        INFO("mailto:matchpoint_prerelease@eclipseir.com");
        return false;
    }
    else
    {
        PROGRESS("Licencing Complete");
        return true;
    }
#else
    return true;
#endif
}

Return IfSearch::initEigenFace(void)
{
    QStringList qsl;
    Return rtn;

    QDir xmlDir(qApp->applicationDirPath());
    QFile file(xmlDir.absoluteFilePath(detectorsXml));
    INFO("Reading detectors from " + file.fileName());
    rtn = HaarDetector::initialize(&file);
    RETURN(rtn);
    if (rtn.isError())
        return rtn;

    PROGRESS("Initializing INDIface Face Detector");
    unsigned faceInterface = appSettings->value("Detect/Interface", 0).toUInt();
    ffd = new FrontalFaceDetector(faceInterface, this); Q_ASSERT(ffd);
    ffd->setObjectName("ffd");
    QString faceDetector = appSettings->value("Detect/FaceDetector",
                                              ffd->detectorsDefault())
                                                    .toString();
    VersionInfo cvVersion = ffd->cvVersion();
    PROGRESS("%1 %2 %3 built %4", cvVersion.getOrgName(),
             cvVersion.getAppName(), cvVersion.toString(),
             cvVersion.dateTimeString());
    INFO(cvVersion.getCopyright());

    if (faceDetector.isEmpty())
    {
        WARNING("No face detector specified in Detect/FaceDetector");
    }
    else
    {
        ffd->selectDetector(faceDetector);
        if (ffd->hasDetector())
        {
            PROGRESS("Face Detector loaded: %1 %2x%3", ffd->detectorName(),
                     ffd->detectorSize().width(), ffd->detectorSize().height());
            INFO("Description: %1", ffd->detectorDescription());
        }
        else
        {
            ERRMSG("Unable to load face detector: %1", ffd->detectorName());
            QTimer::singleShot(0, this, SLOT(done()));
            return Return::False;
        }
    }
    qsl.clear(); qsl << "MaxAcross" << "MinAcross" << "MinPixels" << "MaxDetectors"
                     << "MaxPixels" << "MaxResults" << "MinQuality" << "MaxDensity"
                     << "MarkColors" << "MarkScaleColor" << "MarkExtraColor" << "MarkAll"
                     << "Factor" << "GroupMethod" << "ForceFind" << "Scale" << "Flags"
                     << "MaxDimension";
    appSettings->objectProperties(ffd, tr("Detect", "config"),
                                  qsl, Settings::Volatile);
    ffd->setDefaultGroupMethod(HaarDetector::GroupByNeighbors);
    connect(ffd, SIGNAL(error(QString)), this, SLOT(error(QString)));
    ffdBusy = false;
    TRACE("FFD is free");

    PROGRESS("Initializing INDIface Data and Parameters");
    eigenData = new EigenFaceData("FaceFrontal");
    QDir dataDir(qApp->applicationDirPath());
    dataDir.cd(eigenFaceDataDir);
    INFO("Creating INDIface data from " + dataDir.absolutePath());
    Info::flush();

    rtn = eigenData->create(dataDir);
    RETURN(rtn);
    if (rtn.isError())
        return rtn;

    eigenParms = EigenFace::parameters(QDir(/*eigenFaceParmDir*/));
    if ( ! eigenParms)
    {
        rtn = EigenFace::lastReturn();
        RETURN(rtn);
        return rtn;
    }

    PROGRESS("Initializing INDIface Template Generators");
    eigenFace = new EigenFaceGenerator(this, eigenData, eigenParms);	Q_ASSERT(eigenFace);
    eigenFace->setObjectName("eigenFace");
    eigenFace->setFactor(optGenerateFactor->toFloat());
    qsl.clear(); qsl << "MinConsistency" << "RoiScale" << "EyeScale";
    appSettings->objectProperties(eigenFace, tr("Generate", "config"), qsl, Settings::Volatile);
    qsl.clear(); qsl << "LeftDetector" << "RightDetector";
    appSettings->objectProperties(eigenFace, tr("Generate", "config"), qsl);
    connect(eigenFace, SIGNAL(error(QString)), this, SLOT(error(QString)));

    PROGRESS("Initializing INDIface Matcher");
    eigenMatcher = new EigenFaceSearcher();
    Q_ASSERT(eigenMatcher);
    appSettings->objectProperties(&matchSettings, tr("Match", "config"), matchSettings.dynamicPropertyNames(), Settings::Volatile);
    appSettings->objectProperties(&searchSettings, tr("Search", "config"), searchSettings.dynamicPropertyNames(), Settings::Volatile);
    searchSimilarity = new EigenFaceSimilarity(&searchSettings);

    return Return();
} // initEigenFace()
#endif
