#pragma once

#include <QObject>

class ObjdetParameters
{
public:
    ObjdetParameters();

    // ------------------ properties ---------------------
private:
    // TODO ForceRaw
    bool m_Enable;
    QString m_DetectorsXml; // Catalog
    QString m_OutputDir;

};

/*
    Q_PROPERTY(QString ClassName READ className)
    Q_PROPERTY(qreal ClassFactor READ classFactor)
    Q_PROPERTY(QString DetectorName READ detectorName)
    Q_PROPERTY(QString DetectorDescription READ detectorDescription)
    Q_PROPERTY(QSize DetectorSize READ detectorSize)
    Q_PROPERTY(int MaxResults READ maxResults WRITE setMaxResults)
    Q_PROPERTY(int MinQuality READ minQuality WRITE setMinQuality)
    Q_PROPERTY(bool ForceFind READ forceFind WRITE setForceFind)
    Q_PROPERTY(qreal Factor READ factor WRITE setFactor)
    Q_PROPERTY(qreal MaxDensity READ maxDensity WRITE setMaxDensity)
    Q_PROPERTY(int MaxDetectors READ maxDetectors WRITE setMaxDetectors)
    Q_PROPERTY(qreal Scale READ scale WRITE setScale)
    Q_PROPERTY(int Flags READ flags WRITE setFlags)
    Q_PROPERTY(int Adjust READ adjust WRITE setAdjust)
    Q_PROPERTY(int MaxAcross READ maxAcross WRITE setMaxAcross)
    Q_PROPERTY(int MinAcross READ minAcross WRITE setMinAcross)
    Q_PROPERTY(int MaxDimension READ maxDimension WRITE setMaxDimension)
    Q_PROPERTY(int MaxPixels READ maxPixels WRITE setMaxPixels)
    Q_PROPERTY(int MinPixels READ minPixels WRITE setMinPixels)
    Q_PROPERTY(int GroupMethod READ groupMethod WRITE setGroupMethod)
    Q_PROPERTY(int GroupThreshold READ groupThreshold WRITE setGroupThreshold)
    Q_PROPERTY(int OverlapThreshold READ overlapThreshold WRITE setOverlapThreshold)
    Q_PROPERTY(int NeighborThreshold READ neighborThreshold WRITE setNeighborThreshold)
    Q_PROPERTY(QString MarkExtraColor READ markExtraColor WRITE setMarkExtraColor)
    Q_PROPERTY(QString MarkScaleColor READ markScaleColor WRITE setMarkScaleColor)
    Q_PROPERTY(QString MarkColors READ markColors WRITE setMarkColors)
    Q_PROPERTY(bool MarkAll READ markAll WRITE setMarkAll)
*/
