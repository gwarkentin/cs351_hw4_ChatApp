#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QNetworkDatagram>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr, int port = 3515);
    ~Server();

public slots:
    void resetSocket(int port);
    void changePortSlot(const QString &text);

void readPendingDatagrams();

signals:
    void messageReceived(const QString &msg);

private:
    QUdpSocket *udpSocket;
    int inport = 3151;

};

#endif // SERVER_H

