#include "CTextList.h"

#include <QByteArray>
#include <QString>

#include "AText.h"

CTextList::CTextList() {;}

CTextList::CTextList(const QByteArrayList &bal) { set(bal); }
CTextList::CTextList(const QStringList &qsl) { set(qsl); }
CTextList::CTextList(const QString &s) { set(s); }
CTextList::CTextList(const QList<CText> &other) : CText::List(other) {;}

CText CTextList::join(char ch) const
{
    if (0 == ch) ch = CText::hinge();
    CTextList tList = *this;
    CText result = isEmpty() ? CText() : tList.takeFirst();
    while ( ! tList.isEmpty())
    {
        result.removeLast(); // take off NUL from previous string
        result += ch;
        result += tList.takeFirst();
    }
    return result;
}


QStringList CTextList::toStringList() const
{
    QStringList result;
    foreach (const CText cct, it())
        result << cct.toString();
    return result;
}

void CTextList::set(const QByteArrayList &bal)
{
    clear();
    foreach (const QByteArray ba, bal)
        append(CText(ba));
}

void CTextList::set(const QStringList &qsl)
{
    clear();
    foreach (const QString qs, qsl)
        append(CText(qs));
}

void CTextList::set(const QString &s)
{
    clear();
    append(s);
}

void CTextList::set(const ATextList &atxl)
{
    clear();
    foreach (const QString qs, atxl)
        append(AText(qs));
}
