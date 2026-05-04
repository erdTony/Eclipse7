#pragma once

#include <QByteArray>
#include <QDateTime>


#include <ctime>

class StructTM
{
public: // ctors
    StructTM(const bool now=true);
    StructTM(const QDateTime dttm);


public: // const
    std::time_t timeT() const;

public: // non-const
    void clear();
    void set(const QDateTime dttm);

private:
    struct tm mSTM;
    QByteArray mBytes;
};
