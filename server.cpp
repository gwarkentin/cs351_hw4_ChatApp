#include "server.h"

Server::Server(QObject *parent, int port) : QObject(parent)
{
    udpSocket = new QUdpSocket(this);
    resetSocket(port);
    connect(udpSocket, &QUdpSocket::readyRead,
            this, &Server::readPendingDatagrams);
}

void messageReceived(const QString &msg);

void Server::resetSocket(int port)
{
    if (!udpSocket->NotOpen) {
        udpSocket->close();
    }
    inport = port;

    qDebug() << "Reset inport to : " << inport;
    udpSocket->bind(QHostAddress::LocalHost, port);
}

void Server::changePortSlot(const QString &text)
{
    resetSocket(text.toInt());
}

void Server::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        QByteArray ba = datagram.data();
        QString msg = QString::fromUtf8(ba);
        QString sender = datagram.senderAddress().toString();
        qDebug() << "Rcv " << inport << ": " << msg;
        emit messageReceived(sender + " - " + msg);
    }
}

Server::~Server()
{
    udpSocket->close();
}
