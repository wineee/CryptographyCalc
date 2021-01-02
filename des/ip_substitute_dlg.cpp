#include "ip_substitute_dlg.h"
#include "ui_ip_substitute_dlg.h"
#include "destable.h"

IP_Substitute_Dlg::IP_Substitute_Dlg(quint64 mText, quint64 m0Text, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IP_Substitute_Dlg)
{
    ui->setupUi(this);
    model = new QStandardItemModel(8,8);
    for (int i = 0; i < 64; i++)
       model->setItem(i/8, i%8, new QStandardItem(QString::number(des::IP[i])));
    ui->tableView->setModel(model);
    for (int i = 0; i < 8; i++) {
       ui->tableView->setColumnWidth(i, 5);
       ui->tableView->setRowHeight(i, 5);
    }
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->textEdit->setText(QString("经过分组后的64位明文分组将按照初始置换表重新排列次序，进行初始置换，"
                                  "置换方法如下：初始置换表从左到右，从上到下读取，如第一行第一列为58，"
                                  "意味着将原明文分组的第58位置换到第1位，初始置换表的下一个数为50，"
                                  "意味着将原明文分组的第50位置换到第2位，依次类推，将原明文分组的64位全部置换完成。"));
    ui->lineEdit_mText->setText(QString("%1").arg(mText, 16, 16, QLatin1Char('0')).toUpper());
    ui->lineEdit_m0Text->setText(QString("%1").arg(m0Text, 16, 16, QLatin1Char('0')).toUpper());
}

IP_Substitute_Dlg::~IP_Substitute_Dlg()
{
    delete model;
    delete ui;
}
