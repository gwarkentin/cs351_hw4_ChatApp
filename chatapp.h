#ifndef CHATAPP_H
#define CHATAPP_H

#include <QMainWindow>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QNetworkInterface>
#include <QIntValidator>
#include <QRegularExpression>
#include <QRegularExpressionValidator>


QT_BEGIN_NAMESPACE
namespace Ui { class ChatApp; }
QT_END_NAMESPACE

class ChatApp : public QMainWindow
{
    Q_OBJECT

public:
    ChatApp(QWidget *parent = nullptr);
    ~ChatApp();

void appendText(const QString &text);

signals:
    void sendMessage(const QString &text);
    void changeInPort(const QString &text);
    void changeOutPort(const QString &text);
    void changeOutIp(const QString &text);

private slots:
    void textEntered();
    void swapPorts();

private:
    Ui::ChatApp *ui;
    QString getMyIP();
};
#endif // CHATAPP_H
