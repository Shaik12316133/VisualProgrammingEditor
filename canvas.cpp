#include "Canvas.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>


Canvas::Canvas(QWidget* parent):QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);
    setBackgroundBrush(QColor(20,20,20));
}

Node* Canvas::createNode(QString name)
{
    Node* n = new Node(name);
    scene->addItem(n);
    n->setPos(rand()%400, rand()%300);
    nodes.append(n);
    return n;
}

void Canvas::connectNodes(Node* a, Node* b)
{
    Connection* c = new Connection(a,b);
    scene->addItem(c);
    connections.append(c);
}

void Canvas::saveToFile(QString path)
{
    QJsonArray arr;

    for(Node* n : nodes)
    {
        QJsonObject obj;
        obj["title"]=n->title;
        obj["x"]=n->pos().x();
        obj["y"]=n->pos().y();
        arr.append(obj);
    }

    QJsonDocument doc(arr);
    QFile f(path);
    if(f.open(QIODevice::WriteOnly))
        f.write(doc.toJson());
}

void Canvas::loadFromFile(QString path)
{
    QFile f(path);
    if(!f.open(QIODevice::ReadOnly)) return;

    QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    scene->clear();
    nodes.clear();

    for(auto v : doc.array())
    {
        QJsonObject o = v.toObject();
        Node* n = createNode(o["title"].toString());
        n->setPos(o["x"].toDouble(),o["y"].toDouble());
    }
}
