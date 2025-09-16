#include "EfpApplication.h"

#include <QTimer>

#include <AppHelper.h>

#include "EfpImageReader.h"
#include "EfpMainWindow.h"

EfpApplication * EfpApplication::mpInstance = nullptr;


EfpApplication::EfpApplication(int &argc, char **argv)
    : BaseWidgetApplication{argc, argv}
    , mpAppHelper(new AppHelper(this))
{
    qInfo() << Q_FUNC_INFO;
    Q_ASSERT(mpInstance == nullptr);
    mpInstance = this;
    setObjectName("EFPApplication:" + applicationName());
    QTimer::singleShot(1000, this, &EfpApplication::initialize);
}

void EfpApplication::initialize()
{
    qInfo() << Q_FUNC_INFO;
    mpMainWindow = new EfpMainWindow;
    mpImageReader = new EfpImageReader(this);
    Q_CHECK_PTR(mpMainWindow);
    Q_CHECK_PTR(mpImageReader);

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
    qInfo() << Q_FUNC_INFO;

    emit setupd();
}

void EfpApplication::start()
{
    qDebug() << Q_FUNC_INFO;

    emit started();
}

void EfpApplication::resume()
{
    qDebug() << Q_FUNC_INFO;
}
