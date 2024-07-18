#ifndef DATA_H
#define DATA_H

#include <vector>
#include <QDataStream>
#include "qfloat16.h"
#include "qtypes.h"

struct Data
{
    struct RBits{
        RBits();
        qint16 asQInt16();
        void fromQInt16(qint16 bits);
        std::vector<bool> m_bits;
    };

public:
    Data();
    quint8 x() const;
    qint8 y() const;
    quint8 v() const;
    qint8 m() const;
    qint8 s() const;
    qfloat16 a() const;
    quint8 p() const;
    bool bit(quint8 bit_num) const;
    void setX(quint8 x);
    void setY(qint8 y);
    void setV(quint8 v);
    void setM(qint8 m);
    void setS(qint8 s);
    void setA(qfloat16 a);
    void setP(quint8 p);
    void setBit(quint8 bit_num, bool val);

private:
    qint16 m_word1;
    qint16 m_word2;
    qint16 m_word3;
    qint16 m_word4;
    RBits m_RBits;

    friend QDataStream& operator << (QDataStream& ds ,const Data& data);
    friend QDataStream& operator >> (QDataStream& ds ,Data& data);
};

QDataStream& operator << (QDataStream& ds ,const Data& data);
QDataStream& operator >> (QDataStream& ds ,Data& data);

#endif // DATA_H
