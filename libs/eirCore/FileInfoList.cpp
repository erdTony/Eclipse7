#include "FileInfoList.h"

FileInfoList::FileInfoList() {;}
FileInfoList::FileInfoList(const FileInfo::List fil) { set(fil); }
FileInfoList::FileInfoList(const QFileInfoList qfil) { set(qfil); }
FileInfoList::FileInfoList(const FSTextList fstl) { set(fstl); }
FileInfoList::FileInfoList(const QStringList qsl) { set(qsl); }

void FileInfoList::set(const FileInfo::List fil)
{
    foreach (const FileInfo cFI, fil)
        append(fil);
}

void FileInfoList::set(const QFileInfoList qfil)
{
    foreach (const QFileInfo cQFI, qfil)
        append(FileInfo(cQFI));
}

void FileInfoList::set(const FSTextList fstl)
{
    foreach (const FSText cFSTx, fstl)
        append(FileInfo(cFSTx));
}

void FileInfoList::set(const QStringList qsl)
{
    foreach (const QString cQS, qsl)
    {
        const FSText cFSTx(cQS);
        append(FileInfo(cFSTx));
    }
}
