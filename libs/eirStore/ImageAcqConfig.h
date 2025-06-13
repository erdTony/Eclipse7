#pragma once

#include <QObject>

#include <QUrl>

#include <Key.h>
#include <KeyMap.h>
#include <Types.h>

class ImageAcqConfig : public QObject
{
    Q_GADGET
public: // types
    enum SortBy
    {
        $null = 0,
        Raw,
        BaseName,
        NameSuffix,
        SuffixName,
        TimeStampCreated,
        TimeStampModified,
        TimeStampAccessed,
        TimeStamp = TimeStampModified, // Windows
        $max
    };

public: // ctors
    explicit ImageAcqConfig();

public: // const

public: // non-const
    void clear();
    void reset();
    void set();
    void set(const KeyMap &config);

private:
    SortBy      mSortBy = $null;

// ======= Properties ========
private:
    Key         pName;
    QUrl        pUrl;
    quint64     pSampleMsec;
    bool        pLoop;
    bool        pDeleteAfter;
    unsigned    pLoMark;
    unsigned    mHiMark;
};
