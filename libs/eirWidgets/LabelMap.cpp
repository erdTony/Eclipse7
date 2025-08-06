#include "LabelMap.h"

#include "Label.h"

LabelMap::LabelMap(QWidget *labelsParent) : mpLabelsParent(labelsParent) {;}

Label *LabelMap::label(const Key &key) const
{
    return mKeyLabelMap.value(key);
}

Label *LabelMap::add(const Key &key)
{
    Label * result = new Label(mpLabelsParent);
    mKeyLabelMap.insert(key, result);
    return result;
}

Label *LabelMap::add(const Key &key, const QString &text)
{
    Label * result = new Label(text, mpLabelsParent);
    mKeyLabelMap.insert(key, result);
    return result;
}

Label *LabelMap::add(const Key &key, const BYTE digits)
{
    Label * result = new Label(digits, mpLabelsParent);
    mKeyLabelMap.insert(key, result);
    return result;
}

Label *LabelMap::add(const Key &key, const QPixmap &pxm)
{
    Label * result = new Label(pxm, mpLabelsParent);
    mKeyLabelMap.insert(key, result);
    return result;
}

Label *LabelMap::add(const Key &key, const QImage &img)
{
    Label * result = new Label(img, mpLabelsParent);
    mKeyLabelMap.insert(key, result);
    return result;
}

