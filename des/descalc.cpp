#include "descalc.h"
#include "destable.h"

DesCalc::DesCalc(quint64 key) {
    this->Key_64 = key;
}

DesCalc::~DesCalc() {
}

/**
 * @brief DesCalc::Encrypt
 * @param plaintext
 * @return ciphertext
 * 加密
 */

quint64 DesCalc::Encrypt(quint64 Text) {
    qDebug("mText %llx", Text);
    this->M_Text = Text;
    this->M0_Text = IP_Substitute(Text); // 初始置换
    //quint48 * Key_Sub = new quint48[16];
    Key_Gen(Key_64);
    this->M_RL = T_Iteration(this->M0_Text); //16轮循环
    this->C_Text = IP_Inv_Substitute(this->M_RL); //终结置换
    return C_Text;
}

/**
 * @brief DesCalc::Decrypt
 * @param ciphertext
 * @return plaintext
 * 解密
 */

quint64 DesCalc::Decrypt(quint64 Text) {
    quint64 C0 = IP_Substitute(Text);
    //quint48 * Key_Sub = new quint48[16];
    Key_Gen(Key_64);
    Key_Inv();
    this->M_RL = T_Iteration(C0);
    quint64 M = IP_Inv_Substitute(this->M_RL);
    return M;
}

/**
 * @brief DesCalc::IP_Substitute
 * @param M
 * @return M0
 * 初始置换
 */
quint64 DesCalc::IP_Substitute(quint64 M) {
    quint64 M0 = 0;
    for (int i = 63; i >= 0; i--) {
       // M0[i] = M[des::IP[i] - 1];
       M0 <<= 1;
       M0 |= (M>>(des::IP[i]-1)) & 1;
    }
    qDebug("初始置换: %llx\n", M0);
    return M0;
}

/**
 * @brief DesCalc::Key_Gen
 * @param Key_64
 * @param Key_Sub
 * 密钥生成
 */
void DesCalc::Key_Gen(quint64 Key_64) {
    qDebug("i Key64: %llx\n", Key_64);
    this->Key_56 = Key_64_To_56(Key_64);
    qDebug("i Key56: %llx\n", Key_56);
    quint28 C, D;
    C = Key_56 & ((1 << 28) - 1);
    D = Key_56 >> 28;
    this->Key_C[0] = C;
    this->Key_D[0] = D;
    qDebug("C: %x\n", C);
    qDebug("D: %x\n", D);

    for (int i = 0; i < 16; i++) {
        if (i == 0 || i == 1 || i == 8 || i == 15) {
            C = Key_28_Shift_Left(C, 1);
            D = Key_28_Shift_Left(D, 1);
        } else {
            C = Key_28_Shift_Left(C, 2);
            D = Key_28_Shift_Left(D, 2);
        }
        this->Key_C[i+1] = C;
        this->Key_D[i+1] = D;
        Key_56 = C | (quint56)D<<28;
        qDebug("i Key:%d %llx\n", i, Key_56);
        this->Key_Sub[i] = Key_56_To_48(Key_56);
        qDebug("i Key:%d %llx\n", i, Key_Sub[i]);
    }
}

/**
 * @brief DesCalc::Key_Inv
 * @param Key_Sub
 */
void DesCalc::Key_Inv() {
    for (int i = 0; i < 8; i++) {
        quint48 tmp = Key_Sub[i];
        Key_Sub[i] = Key_Sub[15 - i];
        Key_Sub[15 - i] = tmp;
    }
}

quint32 DesCalc::Feistel(quint32 R, quint48 ki) {
    quint48 E_R = E_Expand(R); // 扩展置换(E表)
    //qDebug("E_R %llx\n", E_R);
    quint48 result = E_R ^ ki;
    //qDebug("result %llx\n", result);

    quint32 F_S = 0;
    // 代换 选择 (S盒)
    // 分为8组, 每组6bit输入,4bit输出
    for (int i = 7; i >= 0; i--) {
        int lowbit_6 = result & ((1ul << 6) - 1);
        //qDebug("lowbit6 %x\n", lowbit_6);
        result >>= 6;
        quint8 s_row = (lowbit_6 & 1) | ((lowbit_6 >> 5) << 1);
        quint8 s_col = (lowbit_6 & ((1 << 5) - 1))>>1;
        quint32 s_out = des::S_BOX[i][s_row][s_col];
        //qDebug() << s_row << " " << s_col << " " << s_out;
        //F_S = (F_S << 4) | s_out;
        F_S |= s_out << ((7-i) << 2);
    }
    //qDebug("F_S %x\n", F_S);
    quint32 F_P = P_Substitute(F_S); // 置换(P)
    //qDebug("F_P %x\n", F_P);
    return F_P;
}

DesCalc::quint48 DesCalc::E_Expand(quint32 R) {
    quint48 E_R = 0;
    /*for (int i = 0; i < 48; i++) {
        E_R[47-i] = R[32-E[i]];
    }*/
    for (int i = 0; i < 48; i++) {
        E_R <<= 1;
        E_R |= (R >> (32-des::E[i])) & 1;
    }
    return E_R;
}

quint32 DesCalc::P_Substitute(quint32 F_S) {
    quint32 F_P = 0;
    /*
    for(int i = 0; i < 32; i++) {
        F_P[31-i] = F_S[32-P[i]];
    }*/
    for (int i = 0; i < 32; i++) {
        F_P <<= 1;
        F_P |= (F_S >> (32-des::P[i])) & 1;
    }
    return F_P;
}

/**
 * @brief DesCalc::T_Iteration
 * @param M0
 * @param Key_Sub
 * @return RL
 * 16轮循环
 */
quint64 DesCalc::T_Iteration(quint64 M0) {
    quint32 L, R;
    R = M0 & ((1ul << 32) - 1);
    L = M0 >> 32;
    this->M_R[0] = R;
    this->M_L[0] = L;
    //qDebug("L: %x R:%x\n", L, R);
    for (int i = 0; i < 16; i++) {
        quint32 L_Next(R);
        R = L ^ Feistel(R, Key_Sub[i]);
        L = L_Next;
        this->M_R[i+1] = R;
        this->M_L[i+1] = L;
        qDebug("L: %x R:%x\n", L, R);
    }
    // swap L,R
    quint64 RL = (quint64)R<<32 | L;
    qDebug("RL: %llx\n",RL);
    return RL;
}

/**
 * @brief DesCalc::IP_Inv_Substitute
 * @param RL
 * @return C
 * 逆初始置换
 */
quint64 DesCalc::IP_Inv_Substitute(quint64 RL) {
    quint64 C = 0;
    /*
    for (int i = 0; i < 64; i++) {
        C[i] = RL[IP_Inv[i] - 1];
    }*/
    for (int i = 63; i >= 0; i--) {
        C <<= 1;
        C |= (RL >> (des::IP_Inv[i]-1)) & 1;
    }
    qDebug("C: %llx\n",C);
    return C;
}

/**
 * @brief DesCalc::Key_64_To_56
 * @param Key_64
 * @return
 * 置换选择1
 */
DesCalc::quint56 DesCalc::Key_64_To_56(quint64 Key_64) {
    quint56 Key_56 = 0;
    /*
    for (int i = 0; i < 56; i++) {
        Key_56[55-i] = Key_64[64-PC_1[i]];
    }*/

    for (int i = 0; i < 56; i++) {
        Key_56 <<= 1;
        Key_56 |= (Key_64 >> (64-des::PC_1[i])) & 1;
    }
    qDebug("Key64to56: %llx %llx\n", Key_64, Key_56);
    return Key_56;
}

DesCalc::quint28
DesCalc::Key_28_Shift_Left(quint28 Key_56_Half, int num) {
    quint28 Key_28;
    Key_28 = (Key_56_Half << num) | (Key_56_Half >> (28 - num));
    return Key_28 & ((1<<28)-1);
}

DesCalc::quint48
DesCalc::Key_56_To_48(quint56 Key_56) {
    quint48 Key_48 = 0;
    /*for (int i = 0; i < 48; i++) {
        Key_48[47-i] = Key_56[56-PC_2[i]];
    }*/
    for (int i = 0; i < 48; i++) {
        Key_48 <<= 1;
        Key_48 |= (Key_56 >> (56-des::PC_2[i])) & 1;
    }
    return Key_48;
}

