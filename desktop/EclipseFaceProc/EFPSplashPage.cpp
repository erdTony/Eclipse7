#include "EFPSplashPage.h"

#include <QHBoxLayout>
#include <QImage>
#include <QLayoutItem>
#include <QTimer>
#include <QVBoxLayout>

#include <BaseMainWindowPage.h>
#include <Label.h>

EFPSplashPage::EFPSplashPage(MainWindowPageStack *pMWPS)
    : BaseMainWindowPage{"EFP", pMWPS}
    , mpMainGrid(new QGridLayout())
    , mpEircLabel(new Label("EIRC"))
    , mpIndiLabel(new Label("INDI"))
    , mpEfpLabel(new Label("Efp"))
{
    qDebug() << Q_FUNC_INFO;
    setObjectName("EFPSplashPage");
}

void EFPSplashPage::setup()
{
    Q_CHECK_PTR(mpMainGrid); Q_CHECK_PTR(mpEircLabel);
    Q_CHECK_PTR(mpIndiLabel); Q_CHECK_PTR(mpEfpLabel);
    QWidget::setLayout(mpMainGrid);

    mpMainGrid->addWidget(mpEircLabel, 0, 0, Qt::AlignCenter);
    mpMainGrid->addWidget(mpIndiLabel, 0, 1, Qt::AlignCenter);
    mpMainGrid->addWidget(mpEfpLabel, 1, 0, 1, 2, Qt::AlignCenter);
    QImage tEircImage(":/logos/EclipseIRLogo.png");
    QImage tIndiImage(":/logos/INDI200.png");
    QImage tEfpImage(":/logos/EclipseFaceProcessor.png");
    qDebug() << Q_FUNC_INFO << tEircImage.isNull()
             << tIndiImage.isNull() << tEfpImage.isNull();

    mpEircLabel->pixmap(tEircImage.scaledToWidth(512));
    mpIndiLabel->pixmap(tIndiImage.scaledToWidth(512));
    mpEfpLabel->pixmap(tEfpImage.scaledToWidth(1024));
    const int cRow0Height = qMax(mpEircLabel->height(),
                                 mpIndiLabel->height());
    const int cRow1Height = mpEfpLabel->height();
    mpMainGrid->setColumnMinimumWidth(0, 512);
    mpMainGrid->setColumnMinimumWidth(1, 512);
    mpMainGrid->setRowMinimumHeight(0, cRow0Height);
    mpMainGrid->setRowMinimumHeight(1, cRow1Height);
    minimumSize(Size(1024, cRow0Height + cRow1Height));
    show();
    qDebug() << Q_FUNC_INFO << minimumSize() << "exit";
}
