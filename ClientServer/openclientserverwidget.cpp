#include "openclientserverwidget.h"
#include "ui_openclientserverwidget.h"

OpenClientServerWidget::OpenClientServerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::OpenClientServerWidget)
    , m_client{nullptr}
    , m_server{nullptr}
{
    ui->setupUi(this);

    QObject::connect(ui->clientBtn, &QPushButton::clicked, this, &OpenClientServerWidget::onOpenClientBtnClicked);
    QObject::connect(ui->serverBtn, &QPushButton::clicked, this, &OpenClientServerWidget::onOpenServerBtnClicked);

    this->setWindowTitle("Главное окно");
}

OpenClientServerWidget::~OpenClientServerWidget()
{
    delete ui;
}

void OpenClientServerWidget::onOpenClientBtnClicked()
{
    if(m_client == nullptr){
        m_client = new ClientWidget(this);
        m_client->setWindowFlag(Qt::Window, true);
    }

    m_client->show();
}

void OpenClientServerWidget::onOpenServerBtnClicked()
{
    if(m_server == nullptr){
        m_server = new ServerWidget(this);
        m_server->setWindowFlag(Qt::Window, true);
    }

    m_server->show();
}
