#pragma once

#include <QObject>

#include <QDomElement>
#include <QFileInfo>
#include <QMap>
#include <QString>

#include "Objdet.h"
#include "ObjdetCatalogItem.h"

class ObjdetCatalog : public QObject
{
    Q_OBJECT
public: // types

public: // ctors
    ObjdetCatalog(const QString &catXmlFileName, QObject *parent = nullptr);

public slots:

signals:

public: // const
    QFileInfo fileInfo() const;
    bool fileExists() const;
    ObjdetCatalogItem item(const ObjdetCatalogItem::Key &key) const;
    friend bool operator < (const ObjdetCatalogItem::Key &lhs,
                          const ObjdetCatalogItem::Key &rhs);


public: // non-const
    QString readXmlFile();

public: // static
    static QString names(const Objdet::Class objcls);

private:
    QString processClassDE(const QDomElement &classDE);
    QString extractDetectorItems(const QDomElement &classDE, const QDomElement &detectorDE);
    QStringList toDebugStrings();

private:
    QFileInfo mCatFileInfo;
    QMap<Objdet::Class, QDomElement> mClassElementMap;
    QMap<Objdet::Class, QString> mClassDefaultDetectorMap;
    QMap<ObjdetCatalogItem::Key, ObjdetCatalogItem> mKeyItemMap;
};

inline QFileInfo ObjdetCatalog::fileInfo() const { return mCatFileInfo; }
