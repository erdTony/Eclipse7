#pragma once
#include "eirImage.h"

#include <QFileSystemModel>

#include <QDir>
#include <QFileInfo>
#include <QModelIndex>
#include <QQueue>
class QTimer;

#include "ColorImage.h"

class EIRIMAGE_EXPORT ImageFileSource : public QFileSystemModel
{
    Q_OBJECT
public: // types
    enum Flag
    {
        $null = 0,
        Fetching        = 0x0001,
    };
    Q_DECLARE_FLAGS(Flags, Flag)
    Q_FLAG(Flags)

public: // ctors
    explicit ImageFileSource(QObject *parent = nullptr);

public slots:
    void clear();
    void start(const QDir &rootDir);

private slots:
    void fetch();
    void pulse();
    void pulseFetch();

signals:
    void starting(const QDir &dir);
    void fetched(const int fetchQueueCount);

public: // const

public: // non-const

public: // pointers


private:
    QTimer * mpPulseTimer=nullptr;
    Flags mFlags = $null;
    QDir mRootDir;
    QModelIndex mFetchIndex;
    QQueue<QFileInfo> mFetchQueue;
    QQueue<ColorImage> mImageQueue;
};
