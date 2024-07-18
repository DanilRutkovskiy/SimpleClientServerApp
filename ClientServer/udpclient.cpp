#include "udpclient.h"
#include <QMessageBox>

UdpClient::UdpClient(QObject *parent) :
    QObject(parent)
    , m_udpSocket(new QUdpSocket(this))
    , m_recievedDatagrams{0}
    , m_connectionState{false}
{
    m_serverAddress = QHostAddress("127.0.0.1");
    m_serverPort = 54001;
    m_udpSocket->bind(QHostAddress::Any, 54002);
    connect(m_udpSocket, &QUdpSocket::readyRead, this, &UdpClient::processPendingDatagrams);
    m_connectionTimer = new QTimer(this);
    connect(m_connectionTimer, &QTimer::timeout, this, &UdpClient::onConnectionTimer);
    m_connectionTimer->start(5000);
}

Data UdpClient::getCurrentDataCopy() const
{
    return m_lastData;
}

QString UdpClient::getServerIP() const
{
    return m_serverAddress.toString();
}

quint16 UdpClient::getServerPort() const
{
    return m_serverPort;
}

quint16 UdpClient::getClientPort() const
{
    return m_udpSocket->localPort();
}

void UdpClient::setServerIP(const QString &ip)
{
    m_serverAddress.setAddress(ip);
}

void UdpClient::setServerPort(quint16 port)
{
    m_serverPort = port;
}

void UdpClient::setClientPort(quint16 port)
{
    quint16 prev = m_udpSocket->localPort();
    m_udpSocket->close();
    if(!m_udpSocket->bind(QHostAddress::Any, port)){
        m_udpSocket->close();
        m_udpSocket->bind(QHostAddress::Any, prev);
        QMessageBox msg;
        msg.setText("Не удалось изменить порт клиента!");
        msg.exec();
    }
}

void UdpClient::setDataToWrite(Data sdata)
{
    QByteArray data;

    QDataStream stream (&data, QIODevice::WriteOnly);

    stream << sdata;

    m_udpSocket->writeDatagram(data, m_serverAddress, m_serverPort);
}

void UdpClient::processPendingDatagrams()
{
    while(m_udpSocket->hasPendingDatagrams()){
        QByteArray datagram;
        datagram.resize(m_udpSocket->pendingDatagramSize());
        m_udpSocket->readDatagram(datagram.data(), datagram.size());

        QDataStream stream(&datagram, QIODevice::ReadOnly);

        while (!stream.atEnd()){
            stream >> m_lastData;
        }

        emit dataReceived(m_lastData);

        ++m_recievedDatagrams;
    }
}

void UdpClient::onConnectionTimer()
{
    if(m_recievedDatagrams > 0){
        if(!m_connectionState){
            m_connectionState = true;
            emit connectionStateChanged(m_connectionState);
        }
    }
    else{
        if(m_connectionState){
            m_connectionState = false;
            emit connectionStateChanged(m_connectionState);
        }
    }

    m_recievedDatagrams = 0;
}
