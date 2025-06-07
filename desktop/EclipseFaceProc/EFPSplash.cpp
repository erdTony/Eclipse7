#include "EFPSplash.h"

#include <QHBoxLayout>
#include <QImage>
#include <QLayoutItem>
#include <QTimer>
#include <QVBoxLayout>

#include <BaseMainWindowPage.h>
#include <Label.h>

EFPSplash::EFPSplash(MainWindowPageStack *pMWPS)
    : BaseMainWindowPage{"EFP", pMWPS}
    , mpMainGrid(new QGridLayout())
    , mpEircLabel(new Label("EIRC"))
    , mpIndiLabel(new Label("INDI"))
    , mpEfpLabel(new Label("Efp"))
{
    qDebug() << Q_FUNC_INFO;
    setObjectName("EFPSplash");
}

void EFPSplash::setup()
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
    qDebug() << Q_FUNC_INFO << tEircImage.isNull() << tIndiImage.isNull() << tEfpImage.isNull();

    mpEircLabel->pixmap(tEircImage.scaledToWidth(512));
    mpIndiLabel->pixmap(tIndiImage.scaledToWidth(512));
    mpEfpLabel->pixmap(tEfpImage.scaledToWidth(1024));
    mpMainGrid->setColumnMinimumWidth(0, 512);
    mpMainGrid->setColumnMinimumWidth(1, 512);
    mpMainGrid->setRowMinimumHeight(0, qMax(mpEircLabel->height(),
                                            mpIndiLabel->height()));
    mpMainGrid->setRowMinimumHeight(0, mpEfpLabel->height());
    show();
    qDebug() << Q_FUNC_INFO << "exit";
}
