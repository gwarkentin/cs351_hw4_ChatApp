#include "client.h"

Client::Client(QObject *parent, int port, QHostAddress ipaddr) : QObject(parent)
{
    ip = ipaddr;
    outport = port;
    udpSocket = new QUdpSocket(this);
}

void Client::changePort(int port)
{
    outport = port;
}

void Client::changePortSlot(const QString &text)
{
    changePort(text.toInt());
}

void Client::changeIpSlot(const QString &text)
{
    ip = QHostAddress(text);
}

void Client::sendMessage(const QString &text)
{
    const QByteArray ba = text.toUtf8();
    const QNetworkDatagram qn = QNetworkDatagram(ba, ip, outport);

    qDebug() << "Snd" << ip.toString() << ":" << outport << "- " << text;
    udpSocket->writeDatagram(qn);
}

