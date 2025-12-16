#pragma once
#include "eirLogger.h"


#include <QDir>
#include <QFileInfo>
#include <QString>
class QFile;

#include <FSText.h>
#include <FSTextList.h>
#include <TriBool.h>
class CTextList;

class EIRLOGGER_EXPORT LogFile
{
public:
    LogFile();
    LogFile(FILE * pFile);
    LogFile(const QString &pathname);
    LogFile(const QDir &dir, const QString &filename);

public: // const
    bool isSet() const;
    bool isDir() const;
    FSText filePath() const;
    QDir dir() const;
    FSText baseFileName() const;
    FSText fileName() const;
    FSText absoluteFilePath() const;
    FSText lastPathSegment() const;
    FSText pathSegment(const int ix) const;
    FSTextList pathList() const;


public: // non-const
    void clear();
    void replace(const char ch, const FSText &tx);
    void setBaseFileName(const FSText &tx);
    void setSuffix(const FSText &tx);
    void set(FILE * pFile);
    void set(const QString &pathname);
    void set(const QDir &dir, const QString &filename);
    void start();
    void write(const CTextList &ctxl);
    void flush();
    void close();

private:
    TriBool mSet;
    FILE * mpStdioFile=nullptr;
    QFileInfo mFileInfo;
    QFile * mpFile=nullptr;
    QDir mDir;
    FSTextList mPathSegments;
};

inline bool LogFile::isSet() const { return mSet.isTrue(); }
inline bool LogFile::isDir() const { return mFileInfo.isDir(); }
inline FSTextList LogFile::pathList() const { return mPathSegments; }


