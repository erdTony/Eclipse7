#pragma once
#include "eirGraphics.h"

#include <QGraphicsScene>

class EIRGRAPHICS_EXPORT GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphicsScene(QObject * parent=nullptr);
};
