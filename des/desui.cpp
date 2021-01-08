#include "desui.h"
#include "ui_desui.h"
#include "ip_substitute_dlg.h"
#include "ip_inv_substitute_dlg.h"
#include "key_gen_dlg.h"
#include "iteration_16_dlg.h"
#include "descalc.h"
#include <QDebug>
#include <QMessageBox>
#include <cstring>

using std::string;

DesUi::DesUi(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::DesUi),
    des(nullptr),
    des2(nullptr)
{
    ui->setupUi(this);
}

DesUi::~DesUi()
{
    delete ui;
    if (des != nullptr) delete des;
    if (des2 != nullptr) delete des2;
}

void DesUi::on_pushButton_Encrypt_clicked()
{
    QString str_mText = ui->lineEdit_mText->text();
    QString str_Key = ui->lineEdit_Key->text();
    QByteArray bit_mText = str_mText.toLocal8Bit().toHex();
    QByteArray bit_Key = str_Key.toLocal8Bit().toHex();
    bool succ = true;
    quint64 Key_64 = bit_Key.toULongLong(&succ, 16);
    if (!succ) {
        QMessageBox::warning(this, tr("警告"), tr("密钥超出64位!"));
        return;
    }
    quint64 mText_64 = bit_mText.toULongLong(&succ, 16);
    if (!succ) {
        QMessageBox::warning(this, tr("警告"), tr("明文超出64位!"));
        return;
    }
    if (des != nullptr)
        delete des;
    des = new DesCalc(Key_64);
    quint64 cText = des->Encrypt(mText_64);
    //qDebug() << bit_Key << " " << bit_mText << "\n";
    //qDebug("end:%llx %llx %llx", Key_64, mText_64, cText);
    ui->lineEdit_cText->setText(QString("%1").arg(cText, 16, 16, QLatin1Char('0')).toUpper());
}

void DesUi::on_pushButton_IpSub_clicked()
{
    if (des == nullptr) return;
    IP_Substitute_Dlg dlg(des->M_Text, des->M0_Text);
    dlg.exec();
}

void DesUi::on_pushButton_InvIpSub_clicked()
{
    if (des == nullptr) return;
    IP_Inv_Substitute_Dlg dlg(des->M_RL, des->C_Text);
    dlg.exec();
}

void DesUi::on_pushButton_KeyGen_clicked()
{
    if (des == nullptr) return;
    Key_Gen_Dlg dlg(des);
    dlg.exec();
}

void DesUi::on_pushButton_Iter16_clicked()
{
    if (des == nullptr) return;
    Iteration_16_Dlg dlg(des);
    dlg.exec();
}

void DesUi::on_pushButton_Encrypt_2_clicked()
{
    QString str_Key = ui->lineEdit_Key2->text();
    QByteArray bit_Key = str_Key.toLocal8Bit().toHex();
    bool succ = true;
    quint64 Key_64 = bit_Key.toULongLong(&succ, 16);
    if (!succ) {
        QMessageBox::warning(this, tr("警告"), tr("密钥超出64位!"));
        return;
    }
    if (des2 != nullptr)
        delete des2;
    des2 = new DesCalc(Key_64);
    QString str_mText = ui->textEdit_mText2->toPlainText();
    QByteArray b_mText = str_mText.toLocal8Bit().toHex();
    QString str_cText = "";
    int len = b_mText.length();
    for (int i = 0; i < len; ) {
        QByteArray byte_64;
        int st = i;
        for ( ; i < len && i-st+1 <= 16; i++)
            byte_64.append(b_mText.at(i));
        if (i == len) {
            for ( ; i-st+1 <= 16; i++)
                byte_64.append('0');
        }
        qDebug() << "byte: "  << byte_64 << "\n";
        quint64 m_i = byte_64.toULongLong(nullptr, 16);
        quint64 c_i = des2->Encrypt(m_i);
       // QMessageBox::warning(this, tr(""), );
        str_cText += tr("%1").arg(c_i, 16, 16, QLatin1Char('0')).toUpper();
      //  QMessageBox::warning(this, tr(""), str_cText);

    }
    ui->textEdit_cText2->setText(str_cText);
}

inline char HexBit_to_Ascii(int val) {
    return val < 10 ? '0'+val : 'A'+val-10;
}

void DesUi::on_pushButton_Decrypt_2_clicked()
{
    QString str_Key = ui->lineEdit_Key2->text();
    QByteArray bit_Key = str_Key.toLocal8Bit().toHex();
    bool succ = true;
    quint64 Key_64 = bit_Key.toULongLong(&succ, 16);
    if (!succ) {
        QMessageBox::warning(this, tr("警告"), tr("密钥超出64位!"));
        return;
    }
    if (des2 != nullptr)
        delete des2;
    des2 = new DesCalc(Key_64);
    QString str_cText = ui->textEdit_cText2->toPlainText();
    int clen = str_cText.length();
    QByteArray mByte;
    mByte.resize(clen);
    for (int i = 0; i < clen; i += 16) {
        string s_sub_c = str_cText.toStdString().substr(i,16);
        quint64 m_sub_c = QString::fromStdString(s_sub_c).toULongLong(nullptr, 16);
        quint64 m_sub_m = des2->Decrypt(m_sub_c);

        for (int j = 15; j >= 0; j--) {
            mByte[i+j] = HexBit_to_Ascii(m_sub_m % 16);
            m_sub_m /= 16;
        }
    }
    //qDebug() << mByte << "\n";
    ui->textEdit_mText2->setText(QString::fromLocal8Bit(QByteArray::fromHex(mByte)));
}
