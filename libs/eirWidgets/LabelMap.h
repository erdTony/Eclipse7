#pragma once
#include "eirWidgets.h"

#include <QMap>
class QWidget;

#include <Key.h>
#include <KeyMap.h>
#include <Types.h>
class Label;


class EIRWIDGETS_EXPORT LabelMap
{
public: // ctors
    LabelMap(QWidget *labelsParent=nullptr);

public: // const
    Label * label(const Key &key) const;

public: // non-const
    Label * add(const Key &key);
    Label * add(const Key &key, const QString &text);
    Label * add(const Key &key, const BYTE digits);
    Label * add(const Key &key, const QPixmap &pxm);
    Label * add(const Key &key, const QImage &img);


public: // pointers


private:
    QWidget * mpLabelsParent=nullptr;
    KeyMapT<Key, Label *> mKeyLabelMap;
};
