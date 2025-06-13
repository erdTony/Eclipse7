#pragma once

#include <QObject>

#include <QQueue>

#include <Url.h>

#include <Types.h>
#include <FileInfo.h>

class BaseImageAcqSource : public QObject
{
    Q_OBJECT
public:
    explicit BaseImageAcqSource(QObject *parent = nullptr);
protected:
    BaseImageAcqSource(const Url &Url, QObject *parent = nullptr);

public slots:
    void dequeueInfo(const Count k=1);

signals:
    void dequeued(const FileInfo &fi);
    void infoEmpty();

public: // const
    Count infoCount() const;

public: // non-const
    void enqueue(const FileInfo &fi);
    bool dequeue(FileInfo * pFI);

public: // pointers


private:
    QQueue<FileInfo> mFileInfoQueue;


};
