#include "mainwindow.h"
#include "desui.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(600,400);
    desui = new DesUi;
    this->setCentralWidget(desui);
}

MainWindow::~MainWindow()
{
}

