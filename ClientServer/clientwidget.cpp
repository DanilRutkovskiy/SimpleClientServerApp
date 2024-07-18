#include "clientwidget.h"

#include "ui_clientwidget.h"
#include "connectionsettingswidget.h"
#include "myvalidators.h"

ClientWidget::ClientWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientWidget)
    , m_client(new UdpClient(this))
{
    ui->setupUi(this);
    QObject::connect(m_client, &UdpClient::dataReceived, this, &ClientWidget::onClientDataRecieved);
    QObject::connect(m_client, &UdpClient::connectionStateChanged, this, &ClientWidget::onConnectionStateChanged);
    QObject::connect(ui->writeBtn, &QPushButton::clicked, this, &ClientWidget::onWriteBtnClicked);
    QObject::connect(ui->settingsBtn, &QPushButton::clicked, this, &ClientWidget::onSettingsBtnClicked);

    ui->x_value_edit->setValidator(new MyIntValidator(0, 63, this));
    ui->y_value_edit->setValidator(new MyIntValidator(-31, 31, this));
    ui->v_value_edit->setValidator(new MyIntValidator(0, 255, this));
    ui->m_value_edit->setValidator(new MyIntValidator(0, 3, this));
    ui->s_value_edit->setValidator(new MyIntValidator(0, 3, this));
    QRegularExpression regExp(R"(^-?([0-9]|1[0-2])(\.[0-7])?$|^-12\.7$|^0$|^12\.7$)");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(regExp, this);
    ui->a_value_edit->setValidator(validator);
    ui->p_value_edit->setValidator(new MyIntValidator(0, 130, this));

    this->setWindowTitle("Клиент");
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::onClientDataRecieved(const Data &data)
{
    ui->x_value_label->setText(QString::number(data.x()));
    ui->y_value_label->setText(QString::number(data.y()));
    ui->v_value_label->setText(QString::number(data.v()));
    ui->m_value_label->setText(QString::number(data.m()));
    ui->s_value_label->setText(QString::number(data.s()));
    ui->a_value_label->setText(QString::number(data.a(), 'f', 1));
    ui->p_value_label->setText(QString::number(data.p()));
    ui->R1_val_label->setText(data.bit(0) ? "1" : "0");
    ui->R2_val_label->setText(data.bit(1) ? "1" : "0");
    ui->R3_val_label->setText(data.bit(2) ? "1" : "0");
    ui->R4_val_label->setText(data.bit(3) ? "1" : "0");
    ui->R5_val_label->setText(data.bit(4) ? "1" : "0");
    ui->R6_val_label->setText(data.bit(5) ? "1" : "0");
    ui->R7_val_label->setText(data.bit(6) ? "1" : "0");
    ui->R8_val_label->setText(data.bit(7) ? "1" : "0");
    ui->R9_val_label->setText(data.bit(8) ? "1" : "0");
    ui->R10_val_label->setText(data.bit(9) ? "1" : "0");
    ui->R11_val_label->setText(data.bit(10) ? "1" : "0");
    ui->R12_val_label->setText(data.bit(11) ? "1" : "0");
    ui->R13_val_label->setText(data.bit(12) ? "1" : "0");
    ui->R14_val_label->setText(data.bit(13) ? "1" : "0");
    ui->R15_val_label->setText(data.bit(14) ? "1" : "0");
    ui->R16_val_label->setText(data.bit(15) ? "1" : "0");
}

void ClientWidget::onWriteBtnClicked()
{
    Data cpy = m_client->getCurrentDataCopy();
    if(ui->x_value_edit->text().size() != 0){ cpy.setX(ui->x_value_edit->text().toInt());}
    if(ui->y_value_edit->text().size() != 0){ cpy.setY(ui->y_value_edit->text().toInt());}
    if(ui->v_value_edit->text().size() != 0){ cpy.setV(ui->v_value_edit->text().toInt());}
    if(ui->m_value_edit->text().size() != 0){ cpy.setM(ui->m_value_edit->text().toInt());}
    if(ui->s_value_edit->text().size() != 0){ cpy.setS(ui->s_value_edit->text().toInt());}
    if(ui->a_value_edit->text().size() != 0){ cpy.setA(ui->a_value_edit->text().toFloat());}
    if(ui->p_value_edit->text().size() != 0){ cpy.setP(ui->p_value_edit->text().toInt());}
    cpy.setBit(0, ui->R1_val_checkbox->isChecked());
    cpy.setBit(1, ui->R2_val_checkbox->isChecked());
    cpy.setBit(2, ui->R3_val_checkbox->isChecked());
    cpy.setBit(3, ui->R4_val_checkbox->isChecked());
    cpy.setBit(4, ui->R5_val_checkbox->isChecked());
    cpy.setBit(5, ui->R6_val_checkbox->isChecked());
    cpy.setBit(6, ui->R7_val_checkbox->isChecked());
    cpy.setBit(7, ui->R8_val_checkbox->isChecked());
    cpy.setBit(8, ui->R9_val_checkbox->isChecked());
    cpy.setBit(9, ui->R10_val_checkbox->isChecked());
    cpy.setBit(10, ui->R11_val_checkbox->isChecked());
    cpy.setBit(11, ui->R12_val_checkbox->isChecked());
    cpy.setBit(12, ui->R13_val_checkbox->isChecked());
    cpy.setBit(13, ui->R14_val_checkbox->isChecked());
    cpy.setBit(14, ui->R15_val_checkbox->isChecked());
    cpy.setBit(15, ui->R16_val_checkbox->isChecked());

    m_client->setDataToWrite(cpy);
}

void ClientWidget::onSettingsBtnClicked()
{
    ConnectionSettingsWidget wgt(ConnectionSettingsWidget::DlgMode::ClientSettings);
    wgt.setServerIP(m_client->getServerIP());
    wgt.setServerPort(m_client->getServerPort());
    wgt.setClientPort(m_client->getClientPort());
    if(QDialog::Accepted == wgt.exec()){
        m_client->setServerIP(wgt.getNewServerIp());
        m_client->setServerPort(wgt.getNewServerPort());
        m_client->setClientPort(wgt.getNewClientPort());
    }
}

void ClientWidget::onConnectionStateChanged(bool connection)
{
    if(connection){
        ui->connection_label->setText("Связь есть");
    }
    else{
        ui->connection_label->setText("Отсутствие связи");
    }
}
