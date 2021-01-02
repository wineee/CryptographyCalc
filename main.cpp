#include "mainwindow.h"
//#include "destable.h"
#include <QApplication>
#include "des/descalc.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //DesCalc des(0x3233336672646466ull);
    //qDebug("%llx", des.Decrypt(des.Encrypt(0x68656C6C6F776F20ull)));
    return a.exec();
}
