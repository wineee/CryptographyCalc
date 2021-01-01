#ifndef DESCALC_H
#define DESCALC_H
#include <qbitarray.h>
#include <QDebug>

class DesCalc
{
    typedef quint64 quint48;
    typedef quint64 quint56;
    typedef quint32 quint28;
public:
    DesCalc& operator=(const DesCalc&) = delete;
    DesCalc(quint64 Key);
    ~DesCalc();
    quint64 Encrypt(quint64 Text);
    quint64 Decrypt(quint64 Text);
private:
    quint64 IP_Substitute(quint64 M);
    quint64 IP_Inv_Substitute(quint64 RL);
    quint32 Feistel(quint32 R, quint48 ki);
    quint48 E_Expand(quint32 R);
    quint32 P_Substitute(quint32 F_S);
    quint64 T_Iteration(quint64 M0);
    quint56 Key_64_To_56(quint64 Key);
    quint28 Key_28_Shift_Left(quint28 Key_56_Half, int num);
    quint48 Key_56_To_48(quint56 Key_56);
    void Key_Gen(quint64 Key_64);
    void Key_Inv();
private:
    quint64 Key_64;
    quint48 *Key_Sub;
};

#endif // DESCALC_H
