#ifndef IP_SUBSTITUTE_DLG_H
#define IP_SUBSTITUTE_DLG_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class IP_Substitute_Dlg;
}

class IP_Substitute_Dlg : public QDialog
{
    Q_OBJECT

public:
    explicit IP_Substitute_Dlg(quint64 mText, quint64 m0Text, QWidget *parent = nullptr);
    ~IP_Substitute_Dlg();

private:
    Ui::IP_Substitute_Dlg *ui;
    QStandardItemModel *model;
};

#endif // IP_SUBSTITUTE_DLG_H
