#include "connectionsettingswidget.h"
#include "ui_connectionsettingswidget.h"

#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include "myvalidators.h"

ConnectionSettingsWidget::ConnectionSettingsWidget(DlgMode mode, QWidget *parent)
    :
    m_mode{mode},
    QDialog(parent),
    ui(new Ui::ConnectionSettingsWidget)
{
    ui->setupUi(this);

    QRegularExpression ipAddress(R"((^((25[0-5]|2[0-4][0-9]|[01]?[0-9]?[0-9])\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9]?[0-9])$))");

    QRegularExpressionValidator *ipValidator = new QRegularExpressionValidator(ipAddress, this);
    ui->c_ip_edit->setValidator(ipValidator);
     ui->s_ip_edit->setValidator(ipValidator);
    ui->c_port_edit->setValidator(new MyIntValidator(49152, 65535, this));
    ui->s_port_edit->setValidator(new MyIntValidator(49152, 65535, this));

    if(m_mode == DlgMode::ClientSettings){
        ui->c_ip_edit->hide();
        this->setWindowTitle("Настройки клиента");
    }
    else if(m_mode == DlgMode::ServerSettings){
        ui->s_ip_edit->hide();
        this->setWindowTitle("Настройки сервера");
    }

    QObject::connect(ui->accept_Btn, &QPushButton::clicked, this, &ConnectionSettingsWidget::onAcceptBtnClicked);
    QObject::connect(ui->exit_Btn, &QPushButton::clicked, this, &ConnectionSettingsWidget::onExitBtnClicked);
}

ConnectionSettingsWidget::~ConnectionSettingsWidget()
{
    delete ui;
}

QString ConnectionSettingsWidget::getNewClientIp() const
{
    return ui->c_ip_edit->text();
}

quint16 ConnectionSettingsWidget::getNewClientPort() const
{
    return ui->c_port_edit->text().toInt();
}

QString ConnectionSettingsWidget::getNewServerIp() const
{
    return ui->s_ip_edit->text();
}

quint16 ConnectionSettingsWidget::getNewServerPort() const
{
    return ui->s_port_edit->text().toInt();
}

void ConnectionSettingsWidget::setServerIP(const QString &addr)
{
    ui->s_ip_edit->setText(addr);
}

void ConnectionSettingsWidget::setServerPort(quint16 port)
{
    ui->s_port_edit->setText(QString::number(port));
}

void ConnectionSettingsWidget::setClientIP(const QString &addr)
{
    ui->c_ip_edit->setText(addr);
}

void ConnectionSettingsWidget::setClientPort(quint16 port)
{
    ui->c_port_edit->setText(QString::number(port));
}

void ConnectionSettingsWidget::onAcceptBtnClicked()
{
    QDialog::accept();
}

void ConnectionSettingsWidget::onExitBtnClicked()
{
    QDialog::reject();
}
