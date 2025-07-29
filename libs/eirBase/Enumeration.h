#pragma once
/*! @file Enumeeration.h Declarations for Enumeeration mechanism

Goals:

1. enum [SETYP] Ename { $nullNAME = 0, VAL1, VAL2, ...
2. enum [SETYP] Ename { VAL1 = 1, VAL3 = 3, VAL9 = 9, ...
3. enum [LETYP] EnameFlag { FLAG1 = 1 << VAL1, ...


Usage:

#define LOGLEVEL_NAMEONLY(NAME) \
    NAME(Minimum) \
    NAME(FnArgVal) \ ...

#define LOGLEVEL_NAMEVAL(NVAL) \
    NVAL(Minimum, 1) \
    NVAL(FnEnter, 5) \ ...

#define DEFINE_ENUM_NAMEONLY(LogLevelEnum, LOGLEVEL_NAMEONLY) yields:
    enum LogLevelEnum { Minimum, FnArgVal, }

#define DEFINE_ENUMT_NAMEVAL(LogLevelEnum, BYTE, LOGLEVEL_NAMEVAL) yields:
    enum BYTE LogLevelEnum { Minimum = 1, FnEnter = 5, }

#define DEFINE_FLAG_NAME(LogLevelFlag, quint64, LOGLEVEL_NAMEVAL) yields:
    enum quint64 LogLevelFlag { MinimumFlag = 1 << Minimum, FnEnterFlag = 1 << FnEnter, }



*/
/* g++ -E -dM file.cpp should do the job. -dM, as GNU
 * Preprocessor manual puts it, should generate a list of
 * ‘#define’ directives for all the macros defined
 * during the execution of the preprocessor,
 * including predefined macros.
 */



#define ENUM_DECLARE_BEG(ENAM) \
    enum ENAM { \

#define ENUM_DECLARE_BEGT(ETYP, ENAM) \
    enum ETYP ENAM { \

#define ENUM_DECLARE_END \
    } ; \

#define ENUM_BODY_NAMEONLY(NAME) \
    NAME , \

#define ENUM_BODY_NAMEVAL(NAME, VAL) \
    NAME = VAL , \

#define FLAG_DECLARE_BEGT(ETYP, ENAM) \
    enum ETYP ENAM##Flag { \

#define FLAG_DECLARE_END \
    } ; \

#define FLAG_BODY_NAME(NAME) \
    NAME##Flag = 1 << NAME , \

#define DEFINE_ENUM_NAMEONLY(ENAM, DEF) \
    ENUM_DECLARE_BEG(ENAM) \
    ENUM_BODY_NAMEONLY(DEF) \
    ENUM_DECLARE_END \

#define DEFINE_ENUM_NAMEVAL(ENAM, DEF) \
    ENUM_DECLARE_BEG(ENAM) \
    ENUM_BODY_NAMEVAL(DEF) \
    ENUM_DECLARE_END \

#define DEFINE_ENUMT_NAMEONLY(ETYP, ENAM, DEF) \
    ENUM_DECLARE_BEGT(ETYP, ENAM) \
    ENUM_BODY_NAMEONLY(DEF) \
    ENUM_DECLARE_END \

#define DEFINE_ENUMT_NAMEVAL(ETYP, ENAM, DEF) \
    ENUM_DECLARE_BEGT(ETYP, ENAM) \
    ENUM_BODY_NAMEVAL(DEF) \
    ENUM_DECLARE_END \

#define DEFINE_FLAG_NAME(ETYP, ENAM, DEF) \
    FLAG_DECLARE_BEGT(ETYP, ENAM) \
    FLAG_BODY_NAME(DEF) \
    FLAG_DECLARE_END \


