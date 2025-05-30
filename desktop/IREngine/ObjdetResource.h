#pragma once

#include <QObject>

#include <QFileInfo>
#include <QString>

class ObjdetResource : public QObject
{
    Q_OBJECT
public: // types
    enum Class
    {
        $null = 0,
        Cascade,
        HOG,
        $max
    };

public: // ctors
    explicit ObjdetResource(QObject *parent = nullptr);
    ObjdetResource(const Class cls, QObject *parent = nullptr);

signals:
    void loaded(const bool isError, const QString errorString);

public slots:
//    void load(const QString xmlFileName);

public: // const
    Class klass() const;
    QFileInfo fileInfo() const;

public: // non-const

public: // pointers
    void * resource();

private:
    const Class cmClass=$null;
    QFileInfo mFileInfo;
};
