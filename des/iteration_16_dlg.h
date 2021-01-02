#ifndef ITERATION_16_DLG_H
#define ITERATION_16_DLG_H

#include <QDialog>
class DesCalc;

namespace Ui {
class Iteration_16_Dlg;
}

class Iteration_16_Dlg : public QDialog
{
    Q_OBJECT

public:
    explicit Iteration_16_Dlg(DesCalc *des, QWidget *parent = nullptr);
    ~Iteration_16_Dlg();
    void show();
private slots:
    void on_pushButton_Per_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Iteration_16_Dlg *ui;
    const DesCalc *mydes;
    int cnt;
};

#endif // ITERATION_16_DLG_H
