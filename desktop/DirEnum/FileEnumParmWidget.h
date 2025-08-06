#pragma once

#include <QWidget>

class QGridLayout;
class QRadioButton;

#include <LabelMap.h>

#include "FileEnumeratorParms.h"

class FileEnumParmWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FileEnumParmWidget(QWidget *parent = nullptr);

public slots:
    void setup();

signals:

public: // const
    FileEnumeratorParms get() const;


public: // non-const
    void set(const FileEnumeratorParms &fpe);


public: // pointers
    LabelMap & labelMap();


private:
    LabelMap mLabels;
    QGridLayout * mpMainGrid=nullptr;
    QRadioButton * mpDirRadio=nullptr;
    QRadioButton * mpUrlRadio=nullptr;
    Label * mpSourceLabel=nullptr;
    Label * mpShortMsecLabel=nullptr;
    Label * mpLongMsecLabel=nullptr;
    Label * mpCollectUpperLabel=nullptr;
    Label * mpCollectLowerLabel=nullptr;
    Label * mpCollectChunkLabel=nullptr;
    Label * mpReadUpperLabel=nullptr;
    Label * mpReadLowerLabel=nullptr;
    Label * mpReadChunkLabel=nullptr;
    Label * mpLoadUpperLabel=nullptr;
    Label * mpLoadLowerLabel=nullptr;
    Label * mpLoadChunkLabel=nullptr;
    Label * mpCacheUpperLabel=nullptr;
    Label * mpCacheLowerLabel=nullptr;
    Label * mpCacheChunkLabel=nullptr;
};

inline LabelMap &FileEnumParmWidget::labelMap() { return mLabels; }
