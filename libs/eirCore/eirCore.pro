QT += core
QT += gui
QT += sql
QT += statemachine
QT += xml
QT += widgets
TEMPLATE = lib
DEFINES += EIRCORE_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../libs.pri)

SOURCES += \
    AnyColor.cpp \
    AnyColorTable.cpp \
    Binary.cpp \
    BrightnessContrast.cpp \
    Color.cpp \
    ColorTable.cpp \
    FileInfo.cpp \
    FileInfoList.cpp \
    FunctionInfo.cpp \
    FunctionInfoArgument.cpp \
    FunctionInfoEnum.cpp \
    Iota.cpp \
    LogContext.cpp \
    Pixel32.cpp \
    Point.cpp \
    Rational.cpp \
    RationalColorList.cpp \
    RationalList.cpp \
    RgbColor.cpp \
    Rgba32Table.cpp \
    SCRect.cpp \
    Size.cpp \
    Url.cpp \
    UrlType.cpp \
    VersionInfo.cpp \
    eirCore.cpp \
    Enumeration.cpp \
    Id.cpp \
    IdMap.cpp \
    Key.cpp \
    KeySeg.cpp \
    KeySegList.cpp \
    KeyValueMap.cpp \
    Null.cpp \
    ObjectHelper.cpp \
    UidKeyMap.cpp \
    Value.cpp \
    BaseLogOutput.cpp \
    LogCondition.cpp \
    LogEntry.cpp \
    LogFile.cpp \
    LogFilter.cpp \
    LogFormat.cpp \
    LogFuncInfo.cpp \
    LogItem.cpp \
    LogLevel.cpp \
    LogMachine.cpp \
    LogMessage.cpp \
    LogObject.cpp \
    LogUrl.cpp \
    AText.cpp \
    ATextList.cpp \
    BaseWidgetApplication.cpp \
    Bytes.cpp \
    CText.cpp \
    CTextList.cpp \
    EightCC.cpp \
    FSText.cpp \
    FSTextList.cpp \
    FourCC.cpp \
    MillisecondTime.cpp \
    NanosecondTime.cpp \
    NibbleArray.cpp \
    TriBool.cpp \
    UText.cpp \
    Uid.cpp \
    UidList.cpp \
    XText.cpp

HEADERS += \
    AnyColor.h \
    AnyColorTable.h \
    Binary.h \
    BrightnessContrast.h \
    Color.h \
    ColorTable.h \
    FileInfo.h \
    FileInfoList.h \
    FunctionInfo.h \
    FunctionInfoArgument.h \
    FunctionInfoEnum.h \
    Iota.h \
    LogContext.h \
    MatrixT.h \
    Pixel32.h \
    Point.h \
    Rational.h \
    RationalColorList.h \
    RationalList.h \
    RgbColor.h \
    Rgba32Table.h \
    SCRect.h \
    Size.h \
    Url.h \
    UrlType.h \
    VersionInfo.h \
    eirCore_global.h \
    eirCore.h \
    DualMap.h \
    Enumeration.h \
    EnumerationArray.h \
    EnumerationMask.h \
    Id.h \
    IdMap.h \
    Key.h \
    KeyMap.h \
    KeySeg.h \
    KeySegList.h \
    KeyValueMap.h \
    Named.h \
    Null.h \
    ObjectHelper.h \
    Queue.h \
    UidKeyMap.h \
    Value.h \
    BaseLogOutput.h \
    Log.h \
    LogCondition.h \
    LogEntry.h \
    LogFile.h \
    LogFilter.h \
    LogFormat.h \
    LogFuncInfo.h \
    LogItem.h \
    LogLevel.h \
    LogMachine.h \
    LogMacros.h \
    LogMessage.h \
    LogObject.h \
    LogUrl.h \
    AText.h \
    ATextList.h \
    BaseWidgetApplication.h \
    Bytes.h \
    CText.h \
    CTextList.h \
    DataProperty.h \
    EightCC.h \
    FSText.h \
    FSTextList.h \
    FourCC.h \
    MillisecondTime.h \
    NanosecondTime.h \
    NibbleArray.h \
    TriBool.h \
    Types.h \
    UText.h \
    Uid.h \
    UidList.h \
    XText.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
