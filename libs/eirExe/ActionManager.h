#pragma once
#include "eirExe.h"

#include <QObject>

#include <QMap>
class QAction;

#include <Key.h>


class EIREXE_EXPORT ActionManager : public QObject
{
    Q_OBJECT
public: // types
    typedef QAction * Action;

public: // ctors
    explicit ActionManager(QObject *parent = nullptr);

public slots:
    void add(const Key &key, const Action action);
    void setup();
    void execute();

signals:
    void added(const Key &key, const Action action);

public: // const
    bool contains(const Key &key) const;

public: // non-const
    Action add(const Key &key, const QString &name=QString());

public: // pointers
    Action action(const Key &key);

private:
    QMap<Key, QAction *> mKeyActionMap;
};
