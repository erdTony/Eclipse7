//!file {Eclipse7}/libs/eirBase/Types.h Common typedef's
#pragma once

#include <QtGlobal>
#include <QList>
#include <QString>

typedef quint8                  BYTE;
typedef quint16                 WORD;
typedef float                   WORDF;
typedef quint32                 DWORD;
typedef double                  DWORDF;
typedef quint64                 QWORD;
#ifndef Q_CC_MSVC
typedef quint128                OWORD; // octo
//typedef unsigned _BitInt(256)   SEWORD; // sedecim
#endif

typedef qint16          SWORD;
typedef qint32          SDWORD;
typedef qint64          SQWORD;
#ifndef Q_CC_MSVC
typedef qint128         SOWORD;
//typedef _BitInt(256)    SSEWORD; // sedecim signed
#endif

typedef quintptr        NWORD;
typedef qptrdiff        SNWORD;
typedef signed          INT;
typedef unsigned        UINT;
typedef double          FLOAT;

typedef QWORD           Milliseconds;
typedef qsizetype       Index;
typedef size_t          Count;
typedef size_t          Seed;
typedef Count           Seq;
typedef QWORD           IdNo;

typedef QList<Index>     IndexList;
typedef QList<signed>    SIntList;
typedef QList<unsigned>  UIntList;
typedef QList<QWORD>     QWordList;
typedef QList<double>    FloatList;

