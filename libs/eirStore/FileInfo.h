#pragma once
#include "eirStore.h"

#include <Null.h>

#include <QFileInfo>

class EIRSTORE_EXPORT FileInfo : public Null
{
public: // ctors
    FileInfo();

public: // const

public: // non-const

public: // pointers

private:
    QFileInfo mQFI;
};
