#pragma once

#include <QObject>

#include <QDir>
#include <QImage>
class QFileSystemModel;
class QTimer;

#include <FileInfo.h>
#include <FileInfoList.h>
#include <Types.h>
#include <Url.h>

class EfpImageReader : public QObject
{
    Q_OBJECT
public:
    explicit EfpImageReader(QObject *parent=nullptr);

public slots:
    void initialize();
    void setup();
    void start(const QDir &dir);
    void pause();
    void resume();
    void capture();

signals:
    void initialized();
    void setupd();
    void started();
    void paused();
    void resumed();
    void captured(const FileInfo &fi, const QImage qi);
    void finished();

public: // const
    QDir inputDir() const;

public: // non-const
    bool queryInputDir(const QDir &dir);

public: // pointers

private slots:


private:
    QDir mInputDir;
    Milliseconds mSampleMsec=1000;
    QTimer * mpCaptureTimer;
    bool mPaused=false;
    bool mLoop=false;
    bool mUseModel=false;
    Count mDirDepth = 1;
    QFileSystemModel * mpFSModel=nullptr;
    FileInfoList mFileInfoList;
};

inline QDir EfpImageReader::inputDir() const { return mInputDir; }
