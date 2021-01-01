#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class DesUi;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    DesUi *desui;
};
#endif // MAINWINDOW_H
