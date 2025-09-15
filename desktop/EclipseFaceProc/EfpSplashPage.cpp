#include "EfpSplashPage.h"

#include <QHBoxLayout>
#include <QImage>
#include <QLayoutItem>
#include <QTimer>
#include <QVBoxLayout>

#include <BaseMainWindowPage.h>
#include <Label.h>

EfpSplashPage::EfpSplashPage(QWidget *parent)
    : BaseMainWindowPage{"EFP", parent}
    , mpEircLabel(new Label("EIRC"))
    , mpIndiLabel(new Label("INDI"))
    , mpEfpLabel(new Label("Efp"))
{
    qDebug() << Q_FUNC_INFO;
    setObjectName("EFPSplashPage");
}

void EfpSplashPage::setup()
{
    Q_CHECK_PTR(mpEircLabel);
    Q_CHECK_PTR(mpIndiLabel); Q_CHECK_PTR(mpEfpLabel);
    QWidget::setLayout(pageGrid());

    pageGrid()->addWidget(mpEircLabel, 0, 0, Qt::AlignTop | Qt::AlignRight);
    pageGrid()->addWidget(mpIndiLabel, 0, 1, Qt::AlignTop | Qt::AlignLeft);
    pageGrid()->addWidget(mpEfpLabel, 1, 0, 1, 2, Qt::AlignTop | Qt::AlignHCenter);
    QImage tEircImage(":/logos/EclipseIRLogo.png");
    QImage tIndiImage(":/logos/INDI200.png");
    QImage tEfpImage(":/logos/EclipseFaceProcessor.png");
    qDebug() << Q_FUNC_INFO << tEircImage.isNull()
             << tIndiImage.isNull() << tEfpImage.isNull();

    mpEircLabel->set(tEircImage.scaledToWidth(512));
    mpIndiLabel->set(tIndiImage.scaledToWidth(512));
    mpEfpLabel->set(tEfpImage.scaledToWidth(512));
    const int cRow0Height = qMax(mpEircLabel->height(),
                                 mpIndiLabel->height());
    const int cRow1Height = mpEfpLabel->height();
    pageGrid()->setColumnMinimumWidth(0, 512);
    pageGrid()->setColumnMinimumWidth(1, 512);
    pageGrid()->setRowMinimumHeight(0, cRow0Height);
    pageGrid()->setRowMinimumHeight(1, cRow1Height);
    setSizes(QSizePolicy::Minimum,
             Size(1024, cRow0Height + cRow1Height));
    show();
    qDebug() << Q_FUNC_INFO << minimumSize() << "exit";
}

void EfpSplashPage::activate()
{

}
