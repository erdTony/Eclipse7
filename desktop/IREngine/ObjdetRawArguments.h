#pragma once

#include <QSharedDataPointer>
class ObjdetRawArgumentsData;

#include <QSize>
#include <QStringList>

#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>


class ObjdetRawArguments
{
public: // types
    enum Flag // TODO Eliminate Flag/s
    {
        $null = 0,
        Canny = cv::CASCADE_DO_CANNY_PRUNING,
        Scale = cv::CASCADE_SCALE_IMAGE,
        Biggest = cv::CASCADE_FIND_BIGGEST_OBJECT,
        Rough = cv::CASCADE_DO_ROUGH_SEARCH,
        ForceRaw = 0x8000,
    };
    Q_DECLARE_FLAGS(Flags, Flag)

public: // const
    qreal factor() const;
    int neighbors() const;
    int flags() const;
    QSize minSize() const;
    QSize maxSize() const;
    QSize inputSize() const;
    cv::Size cvMinSize() const;
    cv::Size cvMaxSize() const;
    QStringList toStrings() const;

public: // non-const
    void ctor();
    void setFactor(const unsigned u);
    void factor(const qreal f);
    void neighbors(const int n);
    void flags(const int f);
    void minSize(const unsigned dim);
    void maxSize(const unsigned dim);
    void minSize(const QSize sz);
    void maxSize(const QSize sz);
    void inputSize(const QSize sz);
    void set(const Flag f);

    // -------------------- QSharedDataPointer ------------------------
public:
    ObjdetRawArguments();
    ObjdetRawArguments(const ObjdetRawArguments &);
    ObjdetRawArguments(ObjdetRawArguments &&);
    ~ObjdetRawArguments();
    ObjdetRawArguments &operator=(const ObjdetRawArguments &);
    ObjdetRawArguments &operator=(ObjdetRawArguments &&);

private:
    QSharedDataPointer<ObjdetRawArgumentsData> data;
};
