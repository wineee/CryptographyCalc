#ifndef DESUI_H
#define DESUI_H

#include <QTabWidget>
class DesCalc;

namespace Ui {
class DesUi;
}

class DesUi : public QTabWidget
{
    Q_OBJECT

public:
    explicit DesUi(QWidget *parent = nullptr);
    ~DesUi();

private slots:
    void on_pushButton_Encrypt_clicked();

    void on_pushButton_IpSub_clicked();

    void on_pushButton_InvIpSub_clicked();

    void on_pushButton_KeyGen_clicked();

    void on_pushButton_Iter16_clicked();

    void on_pushButton_Encrypt_2_clicked();

    void on_pushButton_Decrypt_2_clicked();

private:
    Ui::DesUi *ui;    
    DesCalc *des;
    DesCalc *des2;
};

#endif // DESUI_H
