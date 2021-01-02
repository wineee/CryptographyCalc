#ifndef KEY_GEN_DLG_H
#define KEY_GEN_DLG_H

#include <QDialog>

class DesCalc;

namespace Ui {
class Key_Gen_Dlg;
}

class Key_Gen_Dlg : public QDialog
{
    Q_OBJECT

public:
     Key_Gen_Dlg(DesCalc *des, QWidget *parent = nullptr);
    ~Key_Gen_Dlg();
    void show();
private slots:
    void on_pushButton_pre_clicked();

    void on_pushButton_clicked();

private:
    Ui::Key_Gen_Dlg *ui;
    const DesCalc *mydes;
    int cnt;
};

#endif // KEY_GEN_DLG_H
