#pragma once
#include <QGraphicsView>

class MiniMap:public QGraphicsView
{
public:
    MiniMap(QGraphicsScene* s,QWidget* parent=nullptr);
};
