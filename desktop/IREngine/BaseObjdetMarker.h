#pragma once

#include <QObject>

class BaseObjdetMarker
    : public QObject
{
    Q_OBJECT
public:
    explicit BaseObjdetMarker(QObject *parent = nullptr);

public slots:
    virtual void reset() {;}

signals:

    // ------------------ properties ---------------------
private:
    QString m_OutputDir;
    QString m_CharcolDir;
    QString m_SkinDir;
    bool m_MarkAll;
    QString m_MarkColors;
    QString m_MarkScaleColor;
    QString m_MarkExtraColor;
};
