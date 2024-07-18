#ifndef OPENCLIENTSERVERWIDGET_H
#define OPENCLIENTSERVERWIDGET_H

#include <QWidget>
#include "clientwidget.h"
#include "serverwidget.h"

namespace Ui {
class OpenClientServerWidget;
}

class OpenClientServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OpenClientServerWidget(QWidget *parent = nullptr);
    ~OpenClientServerWidget();

private slots:
    void onOpenClientBtnClicked();
    void onOpenServerBtnClicked();

private:
    QApplication* m_app;
    ClientWidget *m_client;
    ServerWidget *m_server;

private:
    Ui::OpenClientServerWidget *ui;
};

#endif // OPENCLIENTSERVERWIDGET_H

