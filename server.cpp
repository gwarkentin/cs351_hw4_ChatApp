#include "server.h"

Server::Server(QObject *parent, int port, QHostAddress ipaddr) : QObject(parent)
{
    ip = ipaddr;
    inport = port;
    udpSocket = new QUdpSocket(this);
    resetSocket();
    connect(udpSocket, &QUdpSocket::readyRead,
            this, &Server::readPendingDatagrams);
}

void messageReceived(const QString &msg);

void Server::resetSocket()
{
    bool connected = false;
    if (!udpSocket->NotOpen) {
        udpSocket->close();
    }

    qDebug() << "Reset inport to " << ip.toString() << ":" << inport;
    connected = udpSocket->bind(ip, inport);
    if (!connected)
    {
        emit connectionMsg("Connection to " + ip.toString() + ":" + QString::number(inport) + " failed. Try again or another port.");
    }
    else
    {
        emit connectionMsg("Listening on " + ip.toString() + ":" +  QString::number(inport));
    }
}

void Server::changePortSlot(const QString &text)
{
    inport = text.toInt();
    resetSocket();
}

void Server::changeIpSlot(const QString &text)
{
    ip = QHostAddress(text);
    resetSocket();
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
