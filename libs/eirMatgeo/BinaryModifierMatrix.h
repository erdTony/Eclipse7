#pragma once

#include <QString>
#include "MatrixT.h"

#include <Types.h>

#include "Binary.h"

template MatrixT<QString> class BinaryModifierMatrix
{
public:
    typedef QPair<SEWORD, QString> ValueMod;
public:
    BinaryModifierMatrix(Size(3, 10),
                         List<QString>() << "kibi" << "K" << "Ki"
                                         << "mebi" << "M" << "Mi"
                                         << "gibi" << "G" << "Gi"
                                         << "tebi" << "T" << "Ti"
                                         << "pebi" << "P" << "Pi"
                                         << "exbi" << "E" << "Ei"
                                         << "zebi" << "Z" << "Zi"
                                         << "yobi" << "Y" << "Yi"
                                         << "robi" << "R" << "Ri"
                                         << "quebi"<< "Q" << "Qi";)
public:
    ValueMod ValueMod(Binary bin) const
    {
            ValueMod result;

    }

}

