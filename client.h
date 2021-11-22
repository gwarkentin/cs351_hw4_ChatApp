#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QNetworkDatagram>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr,int port = 3514, QHostAddress ipaddr = QHostAddress::LocalHost);

void initSocket(int port);
void changePort(int port);

public slots:
    void sendMessage(const QString &text);
    void changePortSlot(const QString &text);
    void changeIpSlot(const QString &text);

private:
    QUdpSocket *udpSocket;
    QHostAddress ip;
    int outport;

};

#endif // CLIENT_H
