#include "FileData.h"


DEFINE_DATAPROPS(FileData, FileDataData);


FileData::FileData(const Url &url, const FSText &fname)
    : data(new FileDataData) { ctor(); set(url, fname); }

FileData::FileData(const DirInfo &dir, const FSText &fname)
    : data(new FileDataData) { ctor(); set(dir, fname); }

void FileData::set(const Url &url, const FSText &fname)
{
    sourceUrl(url);
}

void FileData::set(const DirInfo &dir, const FSText &fname)
{

}

void FileData::ctor(void) {;}
void FileData::dtor(void) {;}
