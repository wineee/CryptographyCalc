#ifndef IP_INV_SUBSTITUTE_DLG_H
#define IP_INV_SUBSTITUTE_DLG_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class IP_Inv_Substitute_Dlg;
}

class IP_Inv_Substitute_Dlg : public QDialog
{
    Q_OBJECT

public:
    explicit IP_Inv_Substitute_Dlg(qint64 RL, qint64 cText, QWidget *parent = nullptr);
    ~IP_Inv_Substitute_Dlg();

private:
    Ui::IP_Inv_Substitute_Dlg *ui;
    QStandardItemModel *model;
};

#endif // IP_INV_SUBSTITUTE_DLG_H
