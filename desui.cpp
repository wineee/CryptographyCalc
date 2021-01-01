#include "desui.h"
#include "ui_desui.h"
#include "descalc.h"
#include <QDebug>

DesUi::DesUi(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::DesUi),
    des(nullptr)
{
    ui->setupUi(this);
}

DesUi::~DesUi()
{
    delete ui;
}

void DesUi::on_pushButton_Encrypt_clicked()
{
    QString str_mText = ui->lineEdit_mText->text();
    QString str_Key = ui->lineEdit_Key->text();
    QByteArray bit_mText = str_mText.toLocal8Bit().toHex();
    QByteArray bit_Key = str_Key.toLocal8Bit().toHex();
    quint64 Key_64 = bit_Key.toULongLong(nullptr, 16);
    quint64 mText_64 = bit_mText.toULongLong(nullptr, 16);
    if (des != nullptr)
        delete des;
    des = new DesCalc(Key_64);
    quint64 cText = des->Encrypt(mText_64);
    qDebug() << bit_Key << " " << bit_mText << "\n";
    qDebug("end:%llx %llx %llx", Key_64, mText_64, cText);
    ui->lineEdit_cText->setText(QString("%1").arg(cText, 16, 16, QLatin1Char('0')).toUpper());
}
