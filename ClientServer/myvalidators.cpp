#include "myvalidators.h"

MyIntValidator::MyIntValidator(qint32 bot, qint32 top, QObject *parent) :
    QIntValidator(bot, top, parent),
    m_bot{bot}, m_top{top}
{}

void MyIntValidator::fixup(QString &input) const
{
    if(input.toInt() < m_bot)
        input = QString::number(m_bot);

    if(input.toInt() > m_top)
        input = QString::number(m_top);
}
