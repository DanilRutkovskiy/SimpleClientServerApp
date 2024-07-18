#include "udpserver.h"
#include <QMessageBox>

UdpServer::UdpServer(QObject* parent) : QObject{parent}, m_udpSocket(new QUdpSocket(this)){
    m_udpSocket->bind(QHostAddress::Any, 54001);
    m_clientAddress = QHostAddress("127.0.0.1");
    m_clientPort = 54002;

    m_sendTimer = new QTimer(this);
    connect(m_udpSocket, &QUdpSocket::readyRead, this, &UdpServer::processPendingDatagrams);
    connect(m_sendTimer, &QTimer::timeout, this, &UdpServer::sendData);
    m_sendTimer->start(1000);
}

QString UdpServer::getClientIP() const
{
    return m_clientAddress.toString();
}

quint16 UdpServer::getClientPort() const
{
    return m_clientPort;
}

quint16 UdpServer::getServerPort() const
{
    return m_udpSocket->localPort();
}

void UdpServer::setClientIP(const QString &ip)
{
    m_clientAddress.setAddress(ip);
}

void UdpServer::setClientPort(quint16 port)
{
    m_clientPort = port;
}

void UdpServer::setServerPort(quint16 port)
{
    quint16 prev = m_udpSocket->localPort();
    m_udpSocket->close();
    if(!m_udpSocket->bind(QHostAddress::Any, port)){
        m_udpSocket->close();
        m_udpSocket->bind(QHostAddress::Any, prev);
        QMessageBox msg;
        msg.setText("Не удалось изменить порт сервера!");
        msg.exec();
    }
}

void UdpServer::sendData()
{
    QByteArray data;

    QDataStream stream (&data, QIODevice::WriteOnly);

    stream << m_data;

    m_udpSocket->writeDatagram(data, m_clientAddress, m_clientPort);
}

void UdpServer::processPendingDatagrams()
{
    while(m_udpSocket->hasPendingDatagrams()){
        QByteArray datagram;
        datagram.resize(m_udpSocket->pendingDatagramSize());
        m_udpSocket->readDatagram(datagram.data(), datagram.size());

        QDataStream stream(&datagram, QIODevice::ReadOnly);

        while (!stream.atEnd()){
            stream >> m_data;
        }

        emit dataReceived(m_data);
    }
}
