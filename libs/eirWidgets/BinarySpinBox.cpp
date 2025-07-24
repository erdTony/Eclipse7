#include "BinarySpinBox.h"

BinarySpinBox::BinarySpinBox(QWidget *parent)
    : QSpinBox{parent}
{
    setObjectName("BinarySpinBox");
}

BinarySpinBox::BinarySpinBox(const QString &text, QWidget *parent)
    : QSpinBox{parent}
    , mText(text)
{
    setObjectName("BinarySpinBox:" + mText);
}

void BinarySpinBox::setRange(const Binary minBinary,
                            const Binary maxBinary)
{
    QSpinBox::setRange(minBinary.power(), maxBinary.power());
}

void BinarySpinBox::setValue(const Binary binaryValue)
{
    QSpinBox::setValue(binaryValue.power());
}

QString BinarySpinBox::textFromValue(int value) const
{
    Binary tBinary;
    tBinary.power(BYTE(value));
    return QString::number(QWORD(tBinary.value()));
}
