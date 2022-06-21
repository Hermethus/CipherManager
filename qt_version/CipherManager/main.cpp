#include "mainwindow.h"
#include "util/cipherutil.h"
#include "cipherbook.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow m;
    m.show();

    return a.exec();
}
