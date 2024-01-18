#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class QUdpSocket;

class Server : public QWidget
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();

signals:
    void updateGameSceneSignal(qreal newX, qreal newY);

private slots:
    void readPendingDatagrams();
    void processReceivedData(const QByteArray &data, QHostAddress &sender);
    void on_pushButton_clicked();

private:
    Ui::Server *ui;
    QUdpSocket *mSocket;
};
#endif // SERVER_H
