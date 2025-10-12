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

public: // ctors
    explicit ImageFileSource(QObject *parent = nullptr);

public slots:
    void clear();
    void start(const QDir &rootDir);
    void fetch();
    void pulse();


signals:
    void starting(const QDir &dir);
    void fetched(const int n);

public: // const

public: // non-const

public: // pointers


private:
    QTimer * mpPulseTimer=nullptr;
    QDir mRootDir;
    QModelIndex mCurrentIndex;
    QQueue<QFileInfo> mFIQueue;
    QQueue<ColorImage> mImageQueue;
};
