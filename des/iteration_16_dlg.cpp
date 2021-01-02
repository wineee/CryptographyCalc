#include "iteration_16_dlg.h"
#include "ui_iteration_16_dlg.h"
#include "descalc.h"

Iteration_16_Dlg::Iteration_16_Dlg(DesCalc *des, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Iteration_16_Dlg)
{
    ui->setupUi(this);
    this->cnt = 0;
    this->mydes = des;
    this->show();
}

void Iteration_16_Dlg::show()
{
    ui->lineEdit_Cnt->setText(QString::number(cnt+1));
    ui->lineEdit_Li->setText(QString("%1").arg(mydes->M_L[cnt] , 8, 16, QLatin1Char('0')).toUpper());
    ui->lineEdit_Ri->setText(QString("%1").arg(mydes->M_R[cnt] , 8, 16, QLatin1Char('0')).toUpper());
    ui->lineEdit_Next_Li->setText(QString("%1").arg(mydes->M_L[cnt+1] , 8, 16, QLatin1Char('0')).toUpper());
    ui->lineEdit_Next_Ri->setText(QString("%1").arg(mydes->M_R[cnt+1] , 8, 16, QLatin1Char('0')).toUpper());
    ui->lineEdit_Key->setText(QString("%1").arg(mydes->Key_Sub[cnt] , 12, 16, QLatin1Char('0')).toUpper());
}


Iteration_16_Dlg::~Iteration_16_Dlg()
{
    delete ui;
}

void Iteration_16_Dlg::on_pushButton_Per_clicked()
{
    cnt--;
    if (cnt < 0) cnt = 15;
    this->show();
}

void Iteration_16_Dlg::on_pushButton_2_clicked()
{
    cnt++;
    if (cnt == 16) cnt = 0;
    this->show();
}
