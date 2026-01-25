#include "mainwindow.h"
#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyleSheet(
        "QMessageBox { background-color: #0b1d3a; }"
        "QMessageBox QLabel { color: white; }"
        "QMessageBox QPushButton { color: white; }"
        );

    login log;

    if (log.exec() == QDialog::Accepted) {
        MainWindow w;
        w.show();
        return a.exec();
    }

    return 0;
}
