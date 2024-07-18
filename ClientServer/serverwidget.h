#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include "data.h"
#include "udpserver.h"

namespace Ui {
class ServerWidget;
}

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWidget(QWidget *parent = nullptr);
    ~ServerWidget();

private slots:
    void onServerDataRecieved(const Data& data);
    void onSettingsBtnClicked();

private:
    UdpServer *m_server;

private:
    Ui::ServerWidget *ui;
};

#endif // SERVERWIDGET_H
