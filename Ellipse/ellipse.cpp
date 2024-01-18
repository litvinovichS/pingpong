#include "ellipse.h"
#include "ui_ellipse.h"


Ellipse::Ellipse(QWidget *parent)
    : QGraphicsView(parent)
    , ui(new Ui::Ellipse)
    , scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    ellipse = new QGraphicsEllipseItem();
    ellipse->setFlag(QGraphicsItem::ItemIsFocusable);
    ellipse->setFocus();
    ellipse->setRect(400, 300, 25, 25);
    setScene(scene);
    scene->addItem(ellipse);
    scene->setBackgroundBrush(Qt::gray);
    scene->setSceneRect(0, 0, 800, 600);

    mSocket = new QUdpSocket(this);

}

void Ellipse::pressKeyEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
    {
        ellipse->setPos(x()+10, y());
    }
    else if(event->key() == Qt::Key_Up)
    {
        ellipse->setPos(x(), y()+10);
    }
    else if(event->key() == Qt::Key_Down)
    {
        ellipse->setPos(x(), y()-10);
    }
    else if(event->key() == Qt::Key_Right)
    {
        ellipse->setPos(x()-10, y());
    }

    sendDataToServer();
}

Ellipse::~Ellipse()
{
    delete ui;
}

void Ellipse::sendDataToServer()
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream << ellipse->x() << ellipse->y();

    mSocket->writeDatagram(data, QHostAddress::Broadcast, 1234);
}

