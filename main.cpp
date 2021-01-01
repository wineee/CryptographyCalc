#include "mainwindow.h"
//#include "destable.h"
#include <QApplication>
#include "descalc.h"

int main(int argc, char *argv[])
{
    //DesCalc des(0x3233336672646466ull);
    //des.Encrypt(0x68656C6C6F776F20ull);
    //des.Encrypt(5861229659950765385ul);
   // des::IP[0] = 1;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
