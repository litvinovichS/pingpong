#include "server.h"
#include "ui_server.h"
#include <QUdpSocket>

Server::Server(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);
    mSocket = new QUdpSocket(this);
}

void Server::readPendingDatagrams()
{
    while (mSocket->hasPendingDatagrams()){
        QByteArray datagram;
        /*Если maxSize слишком мал, остальная часть дейтаграммы будет потеряна.
         * Чтобы избежать потери данных, вызовите pendingDatagramSize(),
         * чтобы определить размер ожидающей дейтаграммы, прежде чем пытаться ее прочитать.
         * Если maxSize равен 0, дейтаграмма будет отброшена.*/
        datagram.resize(mSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;


        /*Получает дейтаграмму размером не более байта maxSize и сохраняет ее в data.
        Адрес хоста и порт отправителя сохраняются в *address и *port (если указатели не равны 0).
        Возвращает размер дейтаграммы при успешном выполнении; в противном случае возвращает -1.
        Если maxSize слишком мал, остальная часть дейтаграммы будет потеряна. Чтобы избежать потери данных,
        вызовите pendingDatagramSize(), чтобы определить размер ожидающей дейтаграммы, прежде чем пытаться ее прочитать.
        Если maxSize равен 0, дейтаграмма будет отброшена.
        Смотрите также writeDatagram(), hasPendingDatagrams() и pendingDatagramSize().*/
        mSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        processReceivedData(datagram, sender);
    }
}


// Пример обработки входящих датаграмм в сервере
void Server::processReceivedData(const QByteArray &data, QHostAddress &sender)
{
    //Разбор и обработка данных от клиента (игры)
    //Пример: обновление координат объекта на сцене
    qreal newX, newY;
    QDataStream stream(data);
    stream >> newX >> newY;


    // Отправляем сигнал для обновления сцены в игре
    emit updateGameSceneSignal(newX, newY);

}

Server::~Server()
{
    delete ui;
}


void Server::on_pushButton_clicked()
{
    auto datagram = ui->mes->text().toLatin1();
    mSocket->writeDatagram(datagram, QHostAddress::Broadcast, ui->port->value());
}

