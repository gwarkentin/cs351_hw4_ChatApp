#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QNetworkDatagram>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr, int port = 3515, QHostAddress ipaddr = QHostAddress::LocalHost);
    ~Server();

signals:
    void messageReceived(const QString &msg);

public slots:
    void resetSocket();
    void changePortSlot(const QString &text);
    void changeIpSlot(const QString &text);

private:
    QUdpSocket *udpSocket;
    int inport = 3151;
    QHostAddress ip = QHostAddress::LocalHost;
    void readPendingDatagrams();
};
#endif // SERVER_H

