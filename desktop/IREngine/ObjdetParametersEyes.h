#pragma once

#include <QObject>

class ObjdetParametersEyes : public QObject
{
    Q_OBJECT
public:
    explicit ObjdetParametersEyes(QObject *parent = nullptr);

signals:

    // ------------------ properties ---------------------
private:
    int m_EyeScale;
    int m_RoiScale;
    int m_MinConsistency;
    QString m_LeftDetector;
    QString m_LeftDetectorFile;
    QString m_RightDetector;
    QString m_RightDetectorFile;
};
