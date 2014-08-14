#include "sandboxbrowser.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SandboxBrowser w;
    w.show();

    return a.exec();
}
