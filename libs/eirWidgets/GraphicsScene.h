#pragma once
#include "eirWidgets.h"

#include <QGraphicsScene>

class EIRWIDGETS_EXPORT GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphicsScene(QObject * parent=nullptr);
};
