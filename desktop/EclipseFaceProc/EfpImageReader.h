#pragma once

#include <QObject>

#include <QDir>
class QFileSystemModel;

#include <FileInfo.h>
#include <FileInfoList.h>
#include <Types.h>
#include <Url.h>

class EfpImageReader : public QObject
{
    Q_OBJECT
public:
    explicit EfpImageReader(const Url &url, QObject *parent=nullptr);

public slots:
    void initialize();
    void setup();
    void start();
    void pause();
    void resume();

signals:
    void initialized();
    void setupd();
    void started();
    void paused();
    void resumed();

public: // const
    QDir inputDir() const;
    Url inputUrl() const;

public: // non-const
    void inputDir(const QDir &dir);
    void inputUrl(const Url &url);

public: // pointers

private slots:


private:
    Url mInputUrl;
    QDir mInputDir;
    Milliseconds mSampleMsec=100;
    bool mUseModel=false;
    Count mDirDepth = 1;
    QFileSystemModel * mpFSModel=nullptr;
    FileInfoList mFileInfoList;
};

inline QDir EfpImageReader::inputDir() const { return mInputDir; }
inline Url EfpImageReader::inputUrl() const { return mInputUrl; }
