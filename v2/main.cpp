#include <QApplication>
#include "menuview.h"

int main(int _argc, char *_argv[]) {
    QApplication a(_argc, _argv);

    MenuView m;
    m.show();

    return a.exec();
}
