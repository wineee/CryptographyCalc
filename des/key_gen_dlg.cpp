#include "key_gen_dlg.h"
#include "ui_key_gen_dlg.h"
#include "descalc.h"
#include "destable.h"

Key_Gen_Dlg::Key_Gen_Dlg(DesCalc *des, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Key_Gen_Dlg)
{
    ui->setupUi(this);
    cnt = 0;
    mydes = des;
    this->show();
}


Key_Gen_Dlg::~Key_Gen_Dlg()
{
    delete ui;
    //delete mydes;
}

void Key_Gen_Dlg::show()
{//    ui->lineEdit_mText->setText(QString("%1").arg(mText, 16, 16, QLatin1Char('0')).toUpper());

    ui->lineEdit_Cnt->setText(QString::number(cnt+1));
    ui->lineEdit_Key64->setText(QString("%1").arg(mydes->Key_64, 16, 16, QLatin1Char('0')).toUpper());
    ui->lineEdit_Key56->setText(QString("%1").arg(mydes->Key_56, 14, 16, QLatin1Char('0')).toUpper());

    ui->lineEdit_LSbit->setText(QString::number(des::shiftBits[cnt]));
    ui->lineEdit_Ci->setText(QString("%1").arg(mydes->Key_C[cnt], 7, 16, QLatin1Char('0')).toUpper());
    ui->lineEdit_Di->setText(QString("%1").arg(mydes->Key_D[cnt], 7, 16, QLatin1Char('0')).toUpper());
    ui->lineEdit_Next_Ci->setText(QString("%1").arg(mydes->Key_C[cnt+1], 7, 16, QLatin1Char('0')).toUpper());
    ui->lineEdit_Next_Di->setText(QString("%1").arg(mydes->Key_D[cnt+1], 7, 16, QLatin1Char('0')).toUpper());
    ui->lineEdit_Key->setText(QString("%1").arg(mydes->Key_Sub[cnt], 12, 16, QLatin1Char('0')).toUpper());
}

void Key_Gen_Dlg::on_pushButton_pre_clicked()
{
    cnt--;
    if (cnt < 0) cnt = 15;
    this->show();
}

void Key_Gen_Dlg::on_pushButton_clicked()
{
    cnt++;
    if (cnt == 16) cnt = 0;
    this->show();
}
