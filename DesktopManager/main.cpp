#include "widgets/mainwindow.h"

#include <QApplication>
#include "utils/videoUtils/videoutils.h"
int main(int argc, char *argv[])
{



    QApplication a(argc, argv);
//    VideoUtils v("D:/test.mp4");
//    v.play();
    MainWindow w;
    w.show();
    return a.exec();
}
