#include "BaseMainWindowPage.h"

#include <QSizePolicy>
#include <QGridLayout>

BaseMainWindowPage::BaseMainWindowPage(const QString &n,
                                       QWidget *parent)
    : QWidget(parent)
    , mpPageGrid(new QGridLayout())
{
    qDebug() << Q_FUNC_INFO;
    setObjectName("SplashPage:" + n);
    name(n);
    setLayout(pageGrid());
}

void BaseMainWindowPage::name(const QString n)
{
    qDebug() << Q_FUNC_INFO << n;
    mName = n;
    emit nameChanged(mName);
}

void BaseMainWindowPage::setSizes(const QSizePolicy::Policy szp,
                                 const QSize sz1, const QSize sz2)
{
    qDebug() << Q_FUNC_INFO << szp << sz1 << sz2;
    if ((int)szp & QSizePolicy::GrowFlag)
    {
        setMinimumSize(sz1);
        Q_UNUSED(sz2);
    }
    // TODO BaseMainWindowPage::setSize() other policies
}


