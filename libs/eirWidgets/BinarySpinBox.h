#pragma once
#include "eirWidgets.h"

#include <QSpinBox>

#include <QString>

#include <Binary.h>

class EIRWIDGETS_EXPORT BinarySpinBox : public QSpinBox
{
    Q_OBJECT
public: // ctors
    explicit BinarySpinBox(QWidget *parent=nullptr);
    explicit BinarySpinBox(const QString &text,
                           QWidget *parent=nullptr);

public slots:

signals:

public: // const
    Binary binary() const;

public: // non-const
    Binary & binary();
    void setRange(const Binary minBinary, const Binary maxBinary);
    void setValue(const Binary binaryValue);


public: // pointers

protected: // virtual overrides
    virtual QString textFromValue(int binaryValue) const override;

private:
    Binary mBinary;
    QString mText;
};
