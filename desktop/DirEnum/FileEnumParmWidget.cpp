#include "FileEnumParmWidget.h"

#include <QButtonGroup>
#include <QGridLayout>
#include <QRadioButton>

#include <Label.h>

FileEnumParmWidget::FileEnumParmWidget(QWidget *parent)
    : QWidget{parent}
    , mLabels(this)
{
    setObjectName("FileEnumParmWidget");
}

void FileEnumParmWidget::setup()
{
    qInfo() << Q_FUNC_INFO;
    enum RowIndex
    {
        SourceRadio,
        SourceValue,
        PulseLabel,
        PulseValues,
        QueueLabel,
        CollectValues,
        ReadValues,
        LoadValues,
        CacheValues,
    };
    enum ColIndex
    {
        Labels,
        DirShort,
        ShortLower,
        UrlUpper,
        LongChunk,
        FullWidth,
        QueueLabelWidth = ShortLower,
    };
    mpMainGrid = new QGridLayout(); Q_CHECK_PTR(mpMainGrid);
    mpDirRadio = new QRadioButton("Dir:", this); Q_CHECK_PTR(mpDirRadio);
    mpUrlRadio = new QRadioButton("URL:", this); Q_CHECK_PTR(mpUrlRadio);
    QButtonGroup * pRadioGroup = new QButtonGroup(this);
    pRadioGroup->addButton(mpDirRadio);
    pRadioGroup->addButton(mpUrlRadio);
    mpMainGrid->addWidget(new QLabel("Source", this), SourceRadio, Labels, Qt::AlignRight);
    mpMainGrid->addWidget(mpDirRadio, SourceRadio, DirShort, 1, 2, Qt::AlignLeft);
    mpMainGrid->addWidget(mpUrlRadio, SourceRadio, UrlUpper, 1, 2, Qt::AlignLeft);
    mpMainGrid->addWidget(labelMap().add("Source", 64), SourceValue, 0, 1, FullWidth, Qt::AlignHCenter);
    mpMainGrid->addWidget(new QLabel("Pulse Microseconds", this), PulseLabel, Labels, 1, FullWidth, Qt::AlignLeft);
    mpMainGrid->addWidget(new QLabel("Short:", this), PulseValues, 1, 1, 1, Qt::AlignRight);
    mpMainGrid->addWidget(new QLabel("Long:", this),  PulseValues, 3, 1, 1, Qt::AlignRight);
//    mpMainGrid->addWidget(labelMap().edit("Pulse/Short", 4), PulseValues, 2, 1, 1, Qt::AlignLeft);
  //  mpMainGrid->addWidget(labelMap().edit("Pulse/Long",  4), PulseValues, 4, 1, 1, Qt::AlignLeft);

    setLayout(mpMainGrid);
}
