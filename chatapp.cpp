#include "chatapp.h"
#include "ui_chatapp.h"

ChatApp::ChatApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChatApp)
{
    ui->setupUi(this);

    // display this comps local ip
    QString myIP = getMyIP();
    ui->myIpLabel->setText(myIP);

    // make sure good data for port and ips
    QValidator *portvalidator = new QIntValidator(0,65353, this);
    ui->inportLineEdit->setValidator(portvalidator);
    ui->outportLineEdit->setValidator(portvalidator);

    //found this regex on the internet a it's good enough for me
    QRegularExpression rx("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    QValidator *ipvalidator = new QRegularExpressionValidator(rx, this);
    ui->yourIpLineEdit->setValidator(ipvalidator);


    // send messages with click or enter
    connect(ui->pushButton, SIGNAL (clicked()), this, SLOT (textEntered()));
    connect(ui->lineEdit, SIGNAL (returnPressed()), this, SLOT (textEntered()));

    connect(ui->swapButton, SIGNAL (clicked()), this, SLOT (swapPorts()));

    // signals to let client and server processes know to change settings
    connect(ui->yourIpLineEdit, &QLineEdit::textChanged, this, &ChatApp::changeOutIp);
    connect(ui->inportLineEdit, &QLineEdit::textChanged, this, &ChatApp::changeInPort);
    connect(ui->outportLineEdit, &QLineEdit::textChanged, this, &ChatApp::changeOutPort);

}

QString ChatApp ::getMyIP()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    QString ipaddress = "127.0.0.1";

    //return first non-loopback ip
    for(int nIter=0; nIter<list.count(); nIter++)
    {
        if(!list[nIter].isLoopback())
        {
            if (list[nIter].protocol() == QAbstractSocket::IPv4Protocol )
            {
                ipaddress = list[nIter].toString();
                break;
            }
        }
    }
    return ipaddress;
}

ChatApp::~ChatApp()
{
    delete ui;
}

// to easily test side by side
void ChatApp::swapPorts()
{

    QString inport = ui->inportLineEdit->text();
    QString outport = ui->outportLineEdit->text();
    ui->inportLineEdit->setText(outport);
    ui->outportLineEdit->setText(inport);
}

// add messages from self or others to display
void ChatApp::appendText(const QString &text)
{
    ui->textBrowser->append(text);
}

// new message submissions
void ChatApp::textEntered()
{
    const QString text = ui->lineEdit->text();
    ChatApp::appendText("Me: " + text);
    emit sendMessage(text);
    ui->lineEdit->clear();
}
