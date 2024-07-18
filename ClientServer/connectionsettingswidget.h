#ifndef CONNECTIONSETTINGSWIDGET_H
#define CONNECTIONSETTINGSWIDGET_H

#include <QDialog>

namespace Ui {
class ConnectionSettingsWidget;
}

class ConnectionSettingsWidget : public QDialog
{
    Q_OBJECT
public:
    enum class DlgMode{
        ClientSettings,
        ServerSettings
    };

public:
    explicit ConnectionSettingsWidget(DlgMode mode, QWidget *parent = nullptr);
    ~ConnectionSettingsWidget();
    QString getNewClientIp() const;
    quint16 getNewClientPort() const;
    QString getNewServerIp() const;
    quint16 getNewServerPort() const;
    void setServerIP(const QString& addr);
    void setServerPort(quint16 port);
    void setClientIP(const QString& addr);
    void setClientPort(quint16 port);

private slots:
    void onAcceptBtnClicked();
    void onExitBtnClicked();

private:
    DlgMode m_mode;

private:
    Ui::ConnectionSettingsWidget *ui;
};

#endif // CONNECTIONSETTINGSWIDGET_H
