#pragma once
#include "eirStore.h"


#include <QObject>
#include "BaseImageAcqSource.h"

class EIRSTORE_EXPORT FilesAcqSource : public BaseImageAcqSource
{
    Q_OBJECT
public: // ctors
    explicit FilesAcqSource(QObject *parent = nullptr);

public slots:

signals:

public: // const

public: // non-const

public: // pointers


private:

};
