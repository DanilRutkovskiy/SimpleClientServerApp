#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include "data.h"
#include "udpclient.h"

namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();

private slots:
    void onClientDataRecieved(const Data& data);
    void onWriteBtnClicked();
    void onSettingsBtnClicked();
    void onConnectionStateChanged(bool);

private:
    UdpClient *m_client;

private:
    Ui::ClientWidget *ui;
};

#endif // CLIENTWIDGET_H
