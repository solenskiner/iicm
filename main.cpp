#include <QApplication>
#include "iicm_gui.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    iicm_gui w;
    w.show();
    return a.exec();
}
