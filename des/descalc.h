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
public:
    quint64 Key_64; // 64 位密钥
    quint56 Key_56; // 56 位压缩密钥
    quint28 Key_C[17];
    quint28 Key_D[17];
    quint48 Key_Sub[16]; // 轮密钥
    quint64 M_Text; //明文
    quint64 M0_Text; // 明文经过初始置换
    quint32 M_L[17];
    quint32 M_R[17];
    quint64 M_RL; //终结置换前的
    quint64 C_Text; // 密文;
};

#endif // DESCALC_H
