#include "data.h"

QDataStream& operator << (QDataStream& ds ,const Data& data){
    ds << data.m_word1 << data.m_word2 << data.m_word3 << data.m_word4;
    return ds;
}

QDataStream& operator >> (QDataStream& ds ,Data& data){
    int c = 0;
    while (!ds.atEnd()){
        ++c;
        if(c == 1){
            ds >> data.m_word1;
        }
        else if(c == 2){
            ds >> data.m_word2;
        }
        else if(c == 3){
            ds >> data.m_word3;
        }
        else if(c == 4){
            ds >> data.m_word4;
            data.m_RBits.fromQInt16(data.m_word4);
        }
        else{
            assert(0);
        }
    }
    return ds;
}

Data::Data() : m_word1{0}, m_word2{0}, m_word3{0}, m_word4{0}
{

}

quint8 Data::x() const
{
    qint16 bmask = 0b111111;
    return m_word1 & bmask;
}

qint8 Data::y() const
{
    qint16 bmask = 0b11111 << 8;
    qint8 ret = (m_word1 & bmask) >> 8;
    bmask = 0b1 << 13;

    ret = ret * (m_word1 & bmask ? -1 : 1);

    return ret;
}

quint8 Data::v() const
{
    qint16 bmask = 0b11111111;
    return m_word2 & bmask;
}

qint8 Data::m() const
{
    qint16 bmask = 0b11 << 8;
     return (m_word2 & bmask) >> 8;
}

qint8 Data::s() const
{
    qint16 bmask = 0b11 << 10;

    return (m_word2 & bmask) >> 10;
}

qfloat16 Data::a() const
{
    qint16 bmask = 0b111;
    qint16 fraction = m_word3 & bmask;
    bmask = 0b1111 << 3;
    qint16 integer = (m_word3 & bmask) >> 3;
    bmask = 0b1 << 7;
    bool minus = m_word3 & bmask;
    qfloat16 ret = (minus ? -1 : 1) * (integer + fraction / 10.0) ;

    return ret;
}

quint8 Data::p() const
{
    qint16 bmask = 0b11111111 << 8;
    return (m_word3 & bmask) >> 8;
}

void Data::setX(quint8 x)
{
    quint16 bmask = 0b111111 & x;
    m_word1 &= ~(0b111111);
    m_word1 |= bmask;
}

void Data::setY(qint8 y)
{
    bool minus = y < 0;
    y = std::abs(y);
    quint16 bmask = 0b11111 & y;
    bmask <<= 8;
    m_word1 &= ~(0b11111 << 8);
    m_word1 |= bmask;
    bmask = (minus ? 0b1 : 0b0) << 13;
    m_word1 &= ~(0b1 << 13);
    m_word1 |= bmask;
}

void Data::setV(quint8 v)
{
    qint16 bmask = 0b11111111 & v;
    m_word2 &= ~(0b11111111);
    m_word2 |= bmask;
}

void Data::setM(qint8 m)
{
    qint16 bmask = 0b11 & m;
    bmask <<= 8;
    m_word2 &= ~(0b11 << 8);
    m_word2 |= bmask;
}

void Data::setS(qint8 s)
{
    qint16 bmask = 0b11 & s;
    bmask <<= 10;
    m_word2 &= ~(0b11 << 10);
    m_word2 |= bmask;
}

void Data::setA(qfloat16 a)
{
    qint16 integer = std::abs(static_cast<qint16>(a));
    qint16 fraction = std::abs(static_cast<qint16>(std::round(a * 10)) % 10);
    qint16 bmask = 0b111 & fraction;
    m_word3 &= ~(0b111);
    m_word3 |= bmask;
    bmask = (0b1111 & integer) << 3;
    m_word3 &= ~(0b1111 << 3);
    m_word3 |= bmask;
    bmask = (a < 0 ? 0b1 : 0b0) << 7;
    m_word3 &= ~(0b1 << 7);
    m_word3 |= bmask;
}

void Data::setP(quint8 p)
{
    qint16 bmask = 0b11111111 & p;
    m_word3 &= ~(0b11111111 << 8);
    m_word3 |= (bmask << 8);
}

bool Data::bit(quint8 bit_num) const
{
    if(bit_num < 16){
        return m_RBits.m_bits[bit_num];
    }
    else{
        assert(0);//Таких битов нет
        return false;
    }
}

void Data::setBit(quint8 bit_num, bool val)
{
    if(bit_num < 16){
        m_RBits.m_bits[bit_num] = val;
        m_word4 = m_RBits.asQInt16();
    }
    else{
        assert(0);//Таких битов нет
    }
}

Data::RBits::RBits()
{
    m_bits.resize(16, 0);
}

qint16 Data::RBits::asQInt16()
{
    qint16 ret = 0;
    ret |= m_bits[15] ? 0b1 : 0b0; ret <<= 1;
    ret |= m_bits[14] ? 0b1 : 0b0; ret <<= 1;
    ret |= m_bits[13] ? 0b1 : 0b0; ret <<= 1;
    ret |= m_bits[12] ? 0b1 : 0b0; ret <<= 1;
    ret |= m_bits[11] ? 0b1 : 0b0; ret <<= 1;
    ret |= m_bits[10] ? 0b1 : 0b0; ret <<= 1;
    ret |= m_bits[9] ? 0b1 : 0b0; ret <<= 1;
    ret |= m_bits[8] ? 0b1 : 0b0; ret <<= 1;
    ret |= m_bits[7] ? 0b1 : 0b0; ret <<= 1;
    ret |= m_bits[6] ? 0b1 : 0b0; ret <<= 1;
    ret |= m_bits[5] ? 0b1 : 0b0; ret <<= 1;
    ret |= m_bits[4] ? 0b1 : 0b0; ret <<= 1;
    ret |= m_bits[3] ? 0b1 : 0b0; ret <<= 1;
    ret |= m_bits[2] ? 0b1 : 0b0; ret <<= 1;
    ret |= m_bits[1] ? 0b1 : 0b0; ret <<= 1;
    ret |= m_bits[0] ? 0b1 : 0b0;

    return ret;
}

void Data::RBits::fromQInt16(qint16 bits)
{
    for(auto it = m_bits.begin(); it != m_bits.end(); ++it){
        *it = bits & 0b1 ? true : false; bits >>= 1;
    }
}
