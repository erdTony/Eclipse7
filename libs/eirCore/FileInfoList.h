#pragma once
#include "eirCore.h"

#include "FileInfo.h"

#include <QFileInfoList>
#include <QStringList>

#include <FSText.h>
#include <FSTextList.h>

class EIRCORE_EXPORT FileInfoList : public FileInfo::List
{
public: // ctors
    FileInfoList();
    FileInfoList(const FileInfo::List fil);
    FileInfoList(const QFileInfoList qfil);
    FileInfoList(const FSTextList fstl);
    FileInfoList(const QStringList qsl);

public: // const

public: // non-const
    void set(const FileInfo::List fil);
    void set(const QFileInfoList qfil);
    void set(const FSTextList fstl);
    void set(const QStringList qsl);


};
