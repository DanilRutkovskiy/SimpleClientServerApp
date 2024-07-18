#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QtNetwork/QUdpSocket>
#include <QObject>
#include <QTimer>
#include "data.h"

class UdpServer : public QObject
{
    Q_OBJECT
public:
    UdpServer(QObject *parent = nullptr);
    QString getClientIP() const;
    quint16 getClientPort() const;
    quint16 getServerPort() const;
    void setClientIP(const QString& ip);
    void setClientPort(quint16 port);
    void setServerPort(quint16 port);

public slots:
    void sendData();
    void processPendingDatagrams();

signals:
    void dataReceived(const Data& data);

private:
    QUdpSocket *m_udpSocket;
    QHostAddress m_clientAddress;
    quint16 m_clientPort;
    Data m_data;
    QTimer *m_sendTimer;
};

#endif // UDPSERVER_H
