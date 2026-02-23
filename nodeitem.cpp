#include "NodeItem.h"
#include "WireItem.h"
#include "PinItem.h"

#include <QGraphicsTextItem>
#include <QGraphicsProxyWidget>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsScene>
#include <QLineEdit>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QPen>
#include <QComboBox>

NodeItem::NodeItem(QString type)
{
    nodeType = type;

    setFlags(ItemIsMovable |
             ItemIsSelectable |
             ItemSendsGeometryChanges);

    setAcceptHoverEvents(true);

    //// ⭐ Neon Glow
    QGraphicsDropShadowEffect* glow = new QGraphicsDropShadowEffect();
    glow->setBlurRadius(30);
    glow->setOffset(0);
    glow->setColor(QColor(0,255,170,120));
    setGraphicsEffect(glow);

    //// ⭐ TITLE TEXT
    titleText = new QGraphicsTextItem(type,this);
    QFont f;
    f.setBold(true);
    f.setPointSize(11);
    titleText->setFont(f);
    titleText->setDefaultTextColor(Qt::white);
    titleText->setPos(12,8);

    //// ⭐ OUTPUT LABEL
    outputLabel = nullptr;

    if(type=="Output")
    {
        outputLabel = new QGraphicsSimpleTextItem("Result: --",this);

        QFont rf;
        rf.setPointSize(10);
        rf.setBold(true);
        outputLabel->setFont(rf);

        outputLabel->setBrush(QColor(0,255,200));
        outputLabel->setPos(12,50);
        outputLabel->setZValue(5);
    }

    //// ⭐ Unreal Compare Operator Dropdown
    if(type=="Compare")
    {
        compareBox = new QComboBox();
        compareBox->addItem("<");
        compareBox->addItem(">");
        compareBox->addItem("==");
        compareBox->addItem("!=");
        compareBox->addItem("<=");
        compareBox->addItem(">=");

        compareBox->setStyleSheet(
            "QComboBox{background:#1b1b1b;color:white;border-radius:6px;padding:3px;}");

        compareProxy = new QGraphicsProxyWidget(this);
        compareProxy->setWidget(compareBox);
        compareProxy->setPos(12,32);

        QObject::connect(compareBox,&QComboBox::currentTextChanged,
                         [=](QString op)
                         {
                             compareOp = op;
                             titleText->setPlainText("Compare ("+op+")");
                         });
    }

    //// INPUT FIELD
    if(type!="If" && type!="Output")
    {
        QLineEdit* edit = new QLineEdit();
        edit->setStyleSheet(
            "QLineEdit{background:#1b1b1b;color:white;border-radius:6px;padding:4px;}");

        QGraphicsProxyWidget* proxy = new QGraphicsProxyWidget(this);
        proxy->setWidget(edit);
        proxy->setPos(12,65);

        QObject::connect(edit,&QLineEdit::textChanged,
                         [=](QString t)
                         {
                             numberValue = t.toDouble();
                         });
    }

    input=new PinItem(this,PinItem::Input);
    input->setParentItem(this);
    input->setPos(-7,95);

    output=new PinItem(this,PinItem::Output);
    output->setParentItem(this);
    output->setPos(253,95);

    yesPin=new PinItem(this,PinItem::Yes);
    yesPin->setParentItem(this);
    yesPin->setPos(253,55);

    noPin=new PinItem(this,PinItem::No);
    noPin->setParentItem(this);
    noPin->setPos(253,135);
}

QRectF NodeItem::boundingRect() const
{
    return QRectF(0,0,260,170);
}

//// ⭐ PAINT
void NodeItem::paint(QPainter* p,
                     const QStyleOptionGraphicsItem*,
                     QWidget*)
{
    p->setRenderHint(QPainter::Antialiasing,true);

    QRectF r = boundingRect();

    QPen pen(QColor(0,255,170),2);
    p->setPen(pen);
    p->setBrush(QColor(18,18,18));

    p->drawRoundedRect(r,14,14);
}

void NodeItem::hoverEnterEvent(QGraphicsSceneHoverEvent*)
{
    update();
}

void NodeItem::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
    update();
}

void NodeItem::setActive(bool a)
{
    if(a) setOpacity(1.0);
    else setOpacity(0.95);

    update();
}

QVariant NodeItem::itemChange(GraphicsItemChange change,const QVariant &value)
{
    if(change==ItemPositionHasChanged)
    {
        for(WireItem* w : connectedWires)
            if(w) w->updatePath();
    }
    return QGraphicsObject::itemChange(change,value);
}

void NodeItem::setOutputText(QString txt)
{
    if(outputLabel)
        outputLabel->setText("Result: " + txt);
}
