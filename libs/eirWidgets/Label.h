#pragma once

#include <QLabel>

#include <QFrame>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QWidget>


class Label : public QLabel
{
    Q_OBJECT
public: // typedef
    typedef QWidget * WidgetPtr;

public: // ctors
    explicit Label(QWidget *parent = nullptr);
    explicit Label(const QString &text, QWidget *parent = nullptr);
    explicit Label(const QPixmap &pxm, const QString &text=QString(), QWidget *parent = nullptr);
    explicit Label(const QImage &img, const QString &text=QString(), QWidget *parent = nullptr);

public slots:
    void text(const QString &s);
    void pixmap(const QPixmap &pxm);
    void pixmap(const QImage &img);

signals:

public: // const

public: // non-const


public: // pointers
    QFrame * frame() const;
    WidgetPtr widget() const;
    operator WidgetPtr () const;

};

inline QFrame *Label::frame() const { return (QFrame *)(this); }
inline Label::WidgetPtr Label::widget() const { return (QWidget *)(this); }
inline Label::operator WidgetPtr() const { return widget(); }

