 #pragma once

#include <QObject>

class QSettings;

#include <Value.h>
class Key;
class KeyValueMap;

class Settings : public QObject
{
    Q_OBJECT
public:

public: // ctors
    explicit Settings(QObject *parent = nullptr);

public slots:
    void setup();
    void execute();

signals:

public: // const
    bool contains(const Key &key);
    Value operator [] (const Key &key);
    Value value(const Key &key, const Value fallback=Value());
    KeyValueMap extract();
    KeyValueMap extract(const Key &group);

public: // non-const


public: // pointers


private:
    QSettings * mpSettings=nullptr;

};
