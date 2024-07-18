#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <QByteArray>
#include <QDataStream>
#include <QTimer>
#include "data.h"

class UdpClient : public QObject
{
    Q_OBJECT
public:
    UdpClient(QObject *parent = nullptr);

public:
    Data getCurrentDataCopy() const;
    QString getServerIP() const;
    quint16 getServerPort() const;
    quint16 getClientPort() const;
    void setServerIP(const QString& ip);
    void setServerPort(quint16 port);
    void setClientPort(quint16 port);
    void setDataToWrite(Data data);

public slots:
    void processPendingDatagrams();

private slots:
    void onConnectionTimer();

signals:
    void dataReceived(const Data& data);
    void connectionStateChanged(bool);

private:
    QUdpSocket *m_udpSocket;
    QHostAddress m_serverAddress;
    quint16 m_serverPort;
    Data m_lastData;
    QTimer *m_connectionTimer;
    quint16 m_recievedDatagrams;
    bool m_connectionState;
};

#endif // UDPCLIENT_H
