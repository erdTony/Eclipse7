#pragma once
#include "eirGraphics.h"

#include <QGraphicsView>

class EIRGRAPHICS_EXPORT GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(QWidget * parent=nullptr);
};
