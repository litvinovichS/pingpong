#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <QWidget>
#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Ellipse; }
QT_END_NAMESPACE

class Ellipse : public QGraphicsView
{
    Q_OBJECT

protected:
    void pressKeyEvent(QKeyEvent *event);

public:
    Ellipse(QWidget *parent = nullptr);
    ~Ellipse();

public slots:
    void sendDataToServer();

private:
    Ui::Ellipse *ui;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QUdpSocket *mSocket;
};
#endif // ELLIPSE_H
