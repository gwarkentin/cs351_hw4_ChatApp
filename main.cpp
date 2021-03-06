#include "chatapp.h"
#include "client.h"
#include "server.h"

#include <QApplication>

/*
Gabriel Warkentin
11/21/2021

CS351 Assignment 4
Chat Application
    A gui chat application using UDP
	Required to interface with an app on local machine:
		sending messages to port 3515
		receiving messages on port 3514
	Messages are UDP packets containing c_str
	
	Prints messages both sent and received
	
	I added more functionaility:
		Can change ports
		Easy to use side by side with port swap button
		Can change outbount IP
        Can change which IP to listen on
*/


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatApp w;

    Client udpClient(&w);
    Server udpServer(&w);

    //connect display to server and client
    w.connect(&udpServer, &Server::messageReceived, &w, &ChatApp::appendText);
    w.connect(&w, &ChatApp::sendMessage, &udpClient, &Client::sendMessage);
    w.connect(&w, &ChatApp::changeInPort, &udpServer, &Server::changePortSlot);
    w.connect(&w, &ChatApp::changeOutPort, &udpClient, &Client::changePortSlot);
    w.connect(&w, &ChatApp::changeOutIp, &udpClient, &Client::changeIpSlot);
    w.connect(&w, &ChatApp::changeInIp, &udpServer, &Server::changeIpSlot);

    //display error messages in chat box for failed connections
    w.connect(&udpServer, &Server::connectionMsg, &w, &ChatApp::appendText);
    w.connect(&udpClient, &Client::sentStatus, &w, &ChatApp::appendText);

    w.initLineEdits();

    w.show();
    return a.exec();
}

