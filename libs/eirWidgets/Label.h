#pragma once
#include "eirWidgets.h"


#include <QLabel>

#include <QFrame>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QWidget>

#include <Size.h>
#include <Types.h>

class EIRWIDGETS_EXPORT Label : public QLabel
{
    Q_OBJECT
public: // typedef
    typedef QWidget * WidgetPtr;

public: // ctors
    explicit Label(QWidget *parent = nullptr);
    explicit Label(const QString &text, QWidget *parent = nullptr);
    explicit Label(const BYTE digits, QWidget *parent = nullptr);
    explicit Label(const QPixmap &pxm, QWidget *parent = nullptr, const QString &text=QString());
    explicit Label(const QImage &img, QWidget *parent = nullptr, const QString &text=QString());
    explicit Label(const Size sz, const QColor &clr, QWidget *parent = nullptr);
    explicit Label(const Size sz, const QImage &img, QWidget *parent = nullptr, const QString &text=QString());

public slots:
    void set(const QString &s);
    void set(const QPixmap &pxm);
    void set(const QImage &img);
    void set(const Size sz, const QColor &clr);
    void set(const Size sz, const QImage &img);

signals:

public: // const

public: // non-const


public: // pointers
    QFrame * frame() const;
    WidgetPtr widget() const;
    operator WidgetPtr () const;

private: // non-const
    void set(const Size labelSize, const Size origSize);

private:
};

inline QFrame *Label::frame() const { return (QFrame *)(this); }
inline Label::WidgetPtr Label::widget() const { return (QWidget *)(this); }
inline Label::operator WidgetPtr() const { return widget(); }

