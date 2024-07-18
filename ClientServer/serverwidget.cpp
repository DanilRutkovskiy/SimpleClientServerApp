#include "serverwidget.h"
#include "ui_serverwidget.h"
#include "connectionsettingswidget.h"

ServerWidget::ServerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerWidget)
    , m_server(new UdpServer(this))
{
    ui->setupUi(this);

    QObject::connect(m_server, &UdpServer::dataReceived, this, &ServerWidget::onServerDataRecieved);
    QObject::connect(ui->settingsBtn, &QPushButton::clicked, this, &ServerWidget::onSettingsBtnClicked);

    this->setWindowTitle("Сервер");
}

ServerWidget::~ServerWidget()
{
    delete ui;
}

void ServerWidget::onServerDataRecieved(const Data &data)
{
    ui->x_value_label_s->setText(QString::number(data.x()));
    ui->y_value_label_s->setText(QString::number(data.y()));
    ui->v_value_label_s->setText(QString::number(data.v()));
    ui->m_value_label_s->setText(QString::number(data.m()));
    ui->s_value_label_s->setText(QString::number(data.s()));
    ui->a_value_label_s->setText(QString::number(data.a(), 'f', 1));
    ui->p_value_label_s->setText(QString::number(data.p()));
    ui->R1_val_label_s->setText(data.bit(0) ? "1" : "0");
    ui->R2_val_label_s->setText(data.bit(1) ? "1" : "0");
    ui->R3_val_label_s->setText(data.bit(2) ? "1" : "0");
    ui->R4_val_label_s->setText(data.bit(3) ? "1" : "0");
    ui->R5_val_label_s->setText(data.bit(4) ? "1" : "0");
    ui->R6_val_label_s->setText(data.bit(5) ? "1" : "0");
    ui->R7_val_label_s->setText(data.bit(6) ? "1" : "0");
    ui->R8_val_label_s->setText(data.bit(7) ? "1" : "0");
    ui->R9_val_label_s->setText(data.bit(8) ? "1" : "0");
    ui->R10_val_label_s->setText(data.bit(9) ? "1" : "0");
    ui->R11_val_label_s->setText(data.bit(10) ? "1" : "0");
    ui->R12_val_label_s->setText(data.bit(11) ? "1" : "0");
    ui->R13_val_label_s->setText(data.bit(12) ? "1" : "0");
    ui->R14_val_label_s->setText(data.bit(13) ? "1" : "0");
    ui->R15_val_label_s->setText(data.bit(14) ? "1" : "0");
    ui->R16_val_label_s->setText(data.bit(15) ? "1" : "0");
}

void ServerWidget::onSettingsBtnClicked()
{
    ConnectionSettingsWidget wgt(ConnectionSettingsWidget::DlgMode::ServerSettings);
    wgt.setClientIP(m_server->getClientIP());
    wgt.setClientPort(m_server->getClientPort());
    wgt.setServerPort(m_server->getServerPort());
    if(QDialog::Accepted == wgt.exec()){
        m_server->setClientIP(wgt.getNewClientIp());
        m_server->setClientPort(wgt.getNewClientPort());
        m_server->setServerPort(wgt.getNewServerPort());
    }
}
