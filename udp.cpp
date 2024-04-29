#include "udp.h"
#include <QNetworkDatagram>
#include <QDebug>


Udp::Udp(QObject *parent)
    : QObject{parent},
    m_connected(false)
{
    socket = new QUdpSocket(this);
    connect(socket,&QUdpSocket::readyRead,this,&Udp::receive);
}

QString Udp::status() const
{
    return m_status;
}

void Udp::setStatus(const QString &newStatus)
{
    if (m_status == newStatus)
        return;
    m_status = newStatus;
    emit statusChanged();
}

void Udp::bind(int port)
{
    qDebug() << "bind " << port;
    if ((port) < 9000){
        setStatus("invalid port " + QString::number(port));
        setConnected(false);
        return;
    }
    if (socket->bind(QHostAddress::Any, port)){
        setConnected(true);
        setStatus("connected to " + QString::number(port));

    } else {
        setConnected(false);
        setStatus("failed to connect error " + socket->errorString());
    }
}

void Udp::unbind()
{
    socket->close();
    setStatus("");
    setConnected(false);
}

void Udp::send(QString _ip, int _port, QString _msg)
{
    if (!m_connected) return;
    int bytesSent = socket->writeDatagram(_msg.toUtf8(),QHostAddress(_ip),_port);
    //int bytesSent = socket->writeDatagram(_msg.toUtf8() + "\r\n",QHostAddress::Broadcast,_port);
    qDebug() << "sending... " << _ip << ":" << _port << " msg: " << _msg;
    qDebug() << "nByte sent = " << bytesSent;
    if (bytesSent < 0){
        qDebug() << socket->errorString();
    };
}

void Udp::receive()
{
    qDebug() << "receive";
    while (socket->hasPendingDatagrams()){
        QNetworkDatagram d = socket->receiveDatagram();

        QString _msg(d.data());
        qDebug() << "sender: " << d.senderAddress().toString() << " msg: " << _msg;

        emit msg(_msg.trimmed());
    }
}

bool Udp::connected() const
{
    return m_connected;
}

void Udp::setConnected(bool newConnected)
{
    if (m_connected == newConnected)
        return;
    m_connected = newConnected;
    emit connectedChanged();
}
