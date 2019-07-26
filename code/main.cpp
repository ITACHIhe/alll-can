#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowFlags(Qt::WindowMinimizeButtonHint| Qt::WindowCloseButtonHint);
   // w.setWindowFlags(Qt::FramelessWindowHint);//无边框窗口
    //实现去掉最大化的功能
    w.setWindowTitle("All Can");

    w.show();
    QSize this_size=w.frameSize();
    w.setMaximumSize(this_size);
    w.setMinimumSize(this_size);


    //实现固定大小的功能
    return a.exec();
}
