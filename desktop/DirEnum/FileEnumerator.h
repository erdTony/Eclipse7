#pragma once

#include <QObject>

#include <QByteArray>
#include <QDir>
#include <QImage>
#include <QMap>
#include <QModelIndex>
#include <QQueue>

#include <FileInfo.h>
#include <Types.h>
#include <Url.h>

class QFileSystemModel;

class FileEnumerator : public QObject
{
    Q_OBJECT
public:
    typedef QPair<FileInfo, QByteArray> InfoBytes;
public:
    explicit FileEnumerator(QObject *parent = nullptr);

public slots:
    void start(const Url &url);
    void pulse();

signals:
    void error(const QString msg);
    void enumerated(const FileInfo &fi);
    void loaded(const FileInfo &fi, const QImage &qi);

private:
    QDir mBaseDir;
    QFileSystemModel * mpModel=nullptr;
    QModelIndex mFetchIndex;
    Count mRowCount;
    Count mCurrentRow;
    QQueue<FileInfo> mInputQueue;
    QQueue<FileInfo> mProcessQueue;
    QQueue<InfoBytes> mInfoBytesQueue;
    QMap<FileInfo, QByteArray> mInfoDataMap;
    QMap<FileInfo, QImage> mInfoImageMap;
};
