#pragma once

#include <QObject>

#include <QByteArray>
#include <QDir>
#include <QImage>
#include <QMap>
#include <QModelIndex>
#include <QQueue>

#include <FileData.h>
#include <FileInfo.h>
#include <Types.h>
#include <Url.h>

class QFileSystemModel;

#include "FileEnumeratorParms.h"

class FileEnumerator : public QObject
{
    Q_OBJECT
public: // types
    enum Mode : WORD
    {
        $null                   = 0,
        Enumerate               = 0x0001,
        CollectNames            = 0x0002,
        ReadData                = 0x0004,
        LoadImages              = 0x0008,
        CacheImages             = 0x0010,
        EnumeratingPaused       = 0x0100,
        CollectingPaused        = 0x0200,
        ReadingPaused           = 0x0400,
        LoadingPaused           = 0x0800,
        CachingPaused           = 0x1000,
    };
    Q_DECLARE_FLAGS(Modes, Mode);


public:
    explicit FileEnumerator(const FileEnumeratorParms &fed,
                            QObject *parent = nullptr);

public slots:
    void start(const Url &url);
    void pulse();

signals:
    void error(const QString msg);
    void enumerated(const FileInfo &fi);
    void loaded(const FileInfo &fi, const QImage &qi);

public:
    FileEnumeratorParms parms() const;
    FileEnumeratorParms & parms();

private slots:
    void pulseEnumerate();

private:
    FileEnumeratorParms mParms;
    QDir mBaseDir;
    QFileSystemModel * mpModel=nullptr;
    QModelIndex mFetchIndex;
    Count mRowCount;
    Count mCurrentRow;
    QQueue<FileInfo> mInputQueue;
    QQueue<FileInfo> mProcessQueue;
    QQueue<FileData> mInfoBytesQueue;
    QMap<FileInfo, QByteArray> mInfoDataMap;
    QMap<FileInfo, QImage> mInfoImageMap;
};

inline FileEnumeratorParms FileEnumerator::parms() const { return mParms; }
inline FileEnumeratorParms &FileEnumerator::parms() { return mParms; }
