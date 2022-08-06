#include "mainwindow.h"
#include "util/cipherutil.h"
#include "cipherbook.h"

#include <QApplication>
#include <QDebug>
#include <QString>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow m;
    m.show();

    if (argc > 1) {
        QString param = QString(argv[1]);
        QFileInfo fi = QFileInfo(param);
        if (fi.isFile() && fi.isReadable()) {
            if (!fi.suffix().compare("cipherbook")) {
                m.openCipherByFilename(param);
            } else if (!fi.suffix().compare("json")) {
                m.openPlainByFilename(param);
            }
        }
    }

    return a.exec();
}
