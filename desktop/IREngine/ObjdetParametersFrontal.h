#pragma once

#include <QObject>

class ObjdetParametersFrontal : public QObject
{
    Q_OBJECT
public:
    explicit ObjdetParametersFrontal(QObject *parent = nullptr);

signals:

    // ------------------ properties ---------------------
private:
//  int m_GroupMethod // deprecated
    int m_MaxDetectors;
    int m_MaxResults;
    bool m_ForceFind;
    int m_MaxDensity;
    int m_MaxDimension;
    int m_MinPixels;
    int m_MaxPixels;
    int m_MinAcross;
    int m_MaxAcross;
    int m_MinQuality;
    int m_InputOverCrop;
    QString m_FaceDetector; // Catalog Name for Frontal
    QString m_DetectorFile;
    bool m_MarkAll;
    QString m_MarkColors;
    QString m_MarkScaleColor;
    QString m_MarkExtraColor;
    QString m_CharcolDir;
    QString m_OutputDir;
};
