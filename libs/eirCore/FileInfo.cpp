#include "FileInfo.h"

FileInfo::FileInfo() : Null(true) {;}
FileInfo::FileInfo(const QFileInfo &qfi): QFileInfo(qfi), Null(false) {;}
FileInfo::FileInfo(const FSText &path) : QFileInfo(path), Null(false) {;}
FileInfo::FileInfo(const QDir &dir, const FSText &file) : QFileInfo(dir, file), Null(false) {;}
