#include <QtGlobal>

#if QT_VERSION >= 0x050000
    #include <QtWidgets/QApplication>
#else
    #include <QApplication>
#endif

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow wid;
    wid.show();
    return a.exec();
}
