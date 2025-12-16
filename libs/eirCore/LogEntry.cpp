#include "LogEntry.h"


#include <QBuffer>
#include <QDateTime>
#include <QDataStream>

#include <Bytes.h>

#include "Log.h"

const FourCC LogEntry::scmLESignature("LgEn");

LogEntry::LogEntry() : mLevel(LogLevel::$nullLevel) {;}
LogEntry::LogEntry(const QByteArray &ba) { mport(ba); }
LogEntry::LogEntry(const LogLevel::Value level, const AText &message)
    : mLevel(level), mFormat(message) {;}

LogEntry::LogEntry(const LogLevel::Value level,
                   const AText &format,
                   const QVariant &arg1,
                   const QVariant &arg2,
                   const QVariant &arg3,
                   const QVariant &arg4)
    : mLevel(level)
    , mFormat(format)
    , mArguments(QVariantList() << format << arg1 << arg2 << arg3 << arg4)
{
    ;
}

LogEntry::LogEntry(const LogLevel::Value level,
                   const AText &format,
                   const QVariantList &args)
    : mLevel(level)
    , mFormat(format)
    , mArguments(args)
{
    mArguments.prepend(format);
}

LogEntry::LogEntry(const LogLevel::Value level,
                   const LogCondition cond,
                   const CText &expName,
                   const QVariant &expValue,
                   const CText &actName,
                   const QVariant &actValue)
    : mLevel(level)
    , mCondition(cond)
    , mArguments(QVariantList() << expName << expValue << actName << actValue)
{
    mArguments.prepend(cond.text());
}

LogEntry::LogEntry(void *psender, const CText &sender, const CText &signal,
                   void *preceiver, const CText &receiver, const CText &slot,
                   const bool conn)
{

}

bool LogEntry::isNull() const
{
    return ! mLevel.isValidLevel();
}

QVariant LogEntry::argument(const Index ix) const
{
    return (ix >= 0 && ix < arguments().count())
               ? arguments().value(ix) : QVariant();
}

QByteArray LogEntry::xport() const
{
    QByteArray result;
    QBuffer tBuffer(&result);
    tBuffer.open(QIODevice::WriteOnly);
    BYTE tByte = level().value();
    DWORD tDword = scmLESignature.dword();
    int tCond = condition().toInt();
    Count tCount;
    const AText cFormat = format();
    tBuffer.write((const char *)&tDword, sizeof(tDword));
    tBuffer.write((const char *)&tByte, sizeof(tByte));
    tBuffer.write((const char *)&tCond, sizeof(tCond));
    tCount = arguments().count();
    tBuffer.write((const char *)&tCount, sizeof(tCount)); // NumArgs
    tCount = format().length() + 1;
    tBuffer.write((const char *)&tCount, sizeof(tCount)); // Format Length
    tBuffer.write((const char *)cFormat.data(), tCount); // Format itself

    foreach (const QVariant cVar, arguments())
    {
        Bytes tVarBytes(cVar);
        int tTypeId = cVar.typeId();
        qsizetype tBytesLength = tVarBytes.length();
        tBuffer.write((const char *)&tBytesLength, sizeof(qsizetype));
        tBuffer.write((const char *)&tTypeId, sizeof(int));
        tBuffer.write((const char *)tVarBytes.data(), tBytesLength);
    }
    tBuffer.close();
    return result.toBase64();
}

QtMsgType LogEntry::qMsgType() const
{
    return LogLevel::qMsgType(mLevel.msgType());
}

void LogEntry::clear()
{
    mLevel.set(LogLevel::$nullLevel);
    mEntryMsec = 0;
    mFormat.clear();
    mCondition = LogCondition::$null;
    mArguments.clear();
}

void LogEntry::mport(const QByteArray &ba)
{
    QByteArray tBA(QByteArray::fromBase64(ba));
    QBuffer tBuffer(&tBA);
    tBuffer.open(QIODevice::ReadOnly);
    clear();
    \
    Bytes tBytes = tBuffer.read(sizeof(DWORD));
    DWORD tSignature = tBytes.dword();
    if (tSignature != scmLESignature.dword())
    {
        mFormat = tBytes;
        mLevel.set(LogLevel::TInfo);
    }
    else
    {
        tBytes = tBuffer.read(sizeof(BYTE));
        mLevel.set(tBytes.byte());
        tBytes = tBuffer.read(sizeof(UINT));
        mCondition.set(tBytes.uint());
        tBytes = tBuffer.read(sizeof(Count));
        Count tArgCount = tBytes.count();
        tBytes = tBuffer.read(sizeof(Count));
        Count tFormatLen = tBytes.count();
        mFormat = tBuffer.read(tFormatLen);

        if (tArgCount)
            mArguments.fill(QVariant(), tArgCount);
        for (Index ix = 0; ix < Index(tArgCount); ++ix)
        {
            tBytes = tBuffer.read(sizeof(UINT));
            UINT tTypeId = tBytes.uint();
            QMetaType tMType = QMetaType(tTypeId);
            tBytes = tBuffer.read(sizeof(qsizetype));
            qsizetype tBytesLength = tBytes.qSizeType();
            QByteArray tVarBytes = tBuffer.read(tBytesLength);
            QVariant tArgVar(tMType, tVarBytes.data());
            mArguments[ix] = tArgVar;
        }
    }
    tBuffer.close();
}

