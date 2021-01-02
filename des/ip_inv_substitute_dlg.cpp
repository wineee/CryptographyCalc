#include "ip_inv_substitute_dlg.h"
#include "ui_ip_inv_substitute_dlg.h"
#include "destable.h"

IP_Inv_Substitute_Dlg::IP_Inv_Substitute_Dlg(qint64 RL, qint64 cText, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IP_Inv_Substitute_Dlg)
{
    ui->setupUi(this);
    model = new QStandardItemModel(8,8);
    for (int i = 0; i < 64; i++)
       model->setItem(i/8, i%8, new QStandardItem(QString::number(des::IP_Inv[i])));
    ui->tableView->setModel(model);
    for (int i = 0; i < 8; i++) {
       ui->tableView->setColumnWidth(i, 5);
       ui->tableView->setRowHeight(i, 5);
    }
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->textEdit->setText(QString("经过16轮加密的明文通过终结置换表，进行终结置换形成最终的64位密文具体置换方法:"
                                  "按照置换表，将经过16轮加密的密文的第1个比特位与第40个比特位进行置换，"
                                  "第2个比特位与第8个比特进行置换，以此类推直至完成64比特密文的置换。"));
    ui->lineEdit_RL->setText(QString("%1").arg(RL, 16, 16, QLatin1Char('0')).toUpper());
    ui->lineEdit_cText->setText(QString("%1").arg(cText, 16, 16, QLatin1Char('0')).toUpper());
}

IP_Inv_Substitute_Dlg::~IP_Inv_Substitute_Dlg()
{
    delete ui;
    delete model;
}
