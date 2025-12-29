#include "EfpApplication.h"

#include <QActionGroup>
#include <QTimer>

#include <AppHelper.h>
#include <BlobStore.h>
#include <Log.h>

#include "EfpFramesPage.h"
#include "EfpImageReader.h"
#include "EfpMainWindow.h"

EfpApplication * EfpApplication::mpInstance = nullptr;


EfpApplication::EfpApplication(int &argc, char **argv)
    : BaseWidgetApplication{argc, argv}
//    , mpAppHelper(new AppHelper(this))
{
    FNENTER();
    Q_ASSERT(mpInstance == nullptr);
    mpInstance = this;
    setObjectName("EFPApplication:" + applicationName());
    QTimer::singleShot(1000, this, &EfpApplication::initialize);
}

void EfpApplication::initialize()
{
    FNSLOT();
    mpMainWindow = new EfpMainWindow;
    Q_CHECK_PTR(mpMainWindow);
    mpActions = new ActionManager(mpMainWindow);
    Q_CHECK_PTR(mpActions);
//    mpBlobStore = new BlobStore(this);
  //  Q_CHECK_PTR(mpBlobStore);

//    mInputUrl = Url("dir://../EFPin/base");
//    mBlobUrl = Url("files://../temp/BlobBase");

    QStringList tArgs = arguments();
    (void)tArgs.takeFirst(); // exe path
    if (tArgs.isEmpty())
        inputDir(QDir("../EFPin"));
    else
        inputDir(tArgs.takeFirst());

    mpActions->setup(ActionManager::AddMainToolbar);
    QActionGroup * pGroup = new QActionGroup(this);
    mpPauseAction = mpActions->add("Pause");
    mpResumeAction = mpActions->add("Resume");
    mpPauseAction->setCheckable(true);
    mpResumeAction->setCheckable(true);
    mpPauseAction->setChecked(true);
    mpResumeAction->setChecked(false);
    pGroup->setExclusionPolicy(QActionGroup::ExclusionPolicy::Exclusive);
    pGroup->addAction(mpPauseAction);
    pGroup->addAction(mpResumeAction);
    connect(mpPauseAction, &QAction::toggled, this, &EfpApplication::onPauseResume);
//    connect(mpResumeAction, &QAction::toggled, this, &EfpApplication::onPauseResume);

//    Q_ASSERT(mpBlobStore->set(mBlobUrl));
  //  Q_ASSERT(mpBlobStore->connect());
    //Q_ASSERT(mpBlobStore->create(true));

    Q_ASSERT(connect(this, &EfpApplication::initialized,
                     main(), &EfpMainWindow::initialize));
    Q_ASSERT(connect(main(), &EfpMainWindow::initialized,
                     this, &EfpApplication::setup));
    Q_ASSERT(connect(this, &EfpApplication::setupd,
                     main(), &EfpMainWindow::setup));
    Q_ASSERT(connect(main(), &EfpMainWindow::setupd,
                     this, &EfpApplication::start));

    emit initialized();
}

void EfpApplication::setup()
{
    FNSLOT();
    connect(this, &EfpApplication::paused, main()->frames()->reader(), &EfpImageReader::pause);
    connect(this, &EfpApplication::resumed, main()->frames()->reader(), &EfpImageReader::resume);
    connect(AMW->frames()->reader(), &EfpImageReader::captured,
            AMW->frames(), &EfpFramesPage::hasCaptured);
    emit setupd();
}

void EfpApplication::start()
{
    FNSLOT();
    main()->start();
    // setRootPath(QDir)
    emit started();
}

void EfpApplication::onPauseResume(const bool checked)
{
    FNSLOT();
    Q_CHECK_PTR(mpPauseAction);
    Q_CHECK_PTR(mpResumeAction);
    if (mpPauseAction->isChecked())
    {
        qDebug() << Q_FUNC_INFO << "emit paused" << checked;
        emit paused();
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "emit resumed" << checked;
        emit resumed();
    }
}


