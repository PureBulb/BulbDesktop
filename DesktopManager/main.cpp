#include "widgets/mainwindow.h"

#include <QApplication>
#include "utils/videoUtils/videoutils.h"
int main(int argc, char *argv[])
{



    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
