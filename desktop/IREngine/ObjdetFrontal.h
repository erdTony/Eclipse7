#pragma once

#include "Objdet.h"

#include "SCRect.h"

class ObjdetFrontal : public Objdet
{
    Q_OBJECT
public:
    explicit ObjdetFrontal(QObject *parent = nullptr);

public: // const
    QImage markedImage(const SCRect eyeLRect=SCRect(),
                       const SCRect eyeRRect=SCRect(),
                       int minQuality=500,
                       int showQuality=0) const;
    QImage detectImage(const unsigned int minQuality) const;

    // ------------------ properties ---------------------
private:
    bool m_Enable;
    int m_MinAcross;
    int m_MaxAcross;
    int m_MinPixels;
    int m_MaxPixels;
    int m_MinQuality;
};
