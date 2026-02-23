#include "MiniMap.h"

MiniMap::MiniMap(QGraphicsScene* s,QWidget* parent)
    :QGraphicsView(s,parent)
{
    setFixedSize(160,110);
    setStyleSheet("background:#000;border:1px solid #00ffaa;");
    scale(0.1,0.1);
}
