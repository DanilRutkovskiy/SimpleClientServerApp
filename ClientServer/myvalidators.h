#ifndef MYVALIDATORS_H
#define MYVALIDATORS_H

#include <QIntValidator>

class MyIntValidator : public QIntValidator{
public:
    explicit MyIntValidator(qint32 bot, qint32 top, QObject *parent = nullptr);

    void fixup(QString &input) const override;

private:
    qint32 m_bot;
    qint32 m_top;
};

#endif // MYVALIDATORS_H
