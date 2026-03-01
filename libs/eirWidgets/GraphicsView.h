#pragma once
#include "eirWidgets.h"

#include <QGraphicsView>

class EIRWIDGETS_EXPORT GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(QWidget * parent=nullptr);
};
