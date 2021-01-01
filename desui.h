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

private:
    Ui::DesUi *ui;    
    DesCalc *des;
};

#endif // DESUI_H
