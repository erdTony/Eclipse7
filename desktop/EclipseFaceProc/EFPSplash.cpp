#include "EFPSplash.h"

#include <QGridLayout>
#include <QImage>
#include <QLabel>
#include <QTimer>

#include <BaseMainWindowPage.h>

EFPSplash::EFPSplash(MainWindowPageStack *pMWPS)
    : BaseMainWindowPage{"EFP", pMWPS}
    , mpLayout(new QGridLayout())
{
    qDebug() << Q_FUNC_INFO;
    setObjectName("EFPSplash");
}

void EFPSplash::setup()
{
    Q_CHECK_PTR(mpLayout);
    layout(mpLayout);
    QImage tEircImage(":/logos/EclipseIRLogo.png");
    QImage tIndiImage(":/logos/INDI200.png");
    QImage tEfpImage(":/logos/EclipseFaceProcessing.png"); // TODO rename processor
    qDebug() << Q_FUNC_INFO << tEircImage.isNull() << tIndiImage.isNull() << tEfpImage.isNull();
    const QPixmap tEircPixmap = QPixmap::fromImage(tEircImage.scaledToWidth(512));
    const QPixmap tIndiPixmap = QPixmap::fromImage(tIndiImage.scaledToWidth(512));
    const QPixmap tEfpPixmap = QPixmap::fromImage(tEfpImage.scaledToWidth(1024));
    qDebug() << Q_FUNC_INFO << tEircPixmap.isNull() << tIndiPixmap.isNull() << tEfpPixmap.isNull();
    QLabel tEircLabel("EIRC");
    QLabel tIndiLabel("INDI");
    QLabel tEfpLabel("EFP");
    tEircLabel.setPixmap(tEircPixmap);
    tIndiLabel.setPixmap(tIndiPixmap);
    tEfpLabel.setPixmap(tEfpPixmap);
    mpLayout->setColumnMinimumWidth(0, 512);
    mpLayout->setColumnMinimumWidth(1, 512);
    mpLayout->setRowMinimumHeight(0,
        qMax(tEircPixmap.height(), tIndiPixmap.height()));
    mpLayout->setRowMinimumHeight(1, tEfpPixmap.height());
    mpLayout->addWidget(&tEircLabel, 0, 0, 1, 1);
    mpLayout->addWidget(&tIndiLabel, 0, 1, 1, 1);
    mpLayout->addWidget(&tEfpLabel, 1, 0, 1, 2);
    tEircLabel.setVisible(true);
    qDebug() << Q_FUNC_INFO << tEircLabel.minimumSizeHint()
             << tIndiLabel.minimumSizeHint()
             << tEfpLabel.minimumSizeHint();
    setVisible(true);
    show();
    qDebug() << Q_FUNC_INFO << "exit";
}
