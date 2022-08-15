#include "mainwindow.h"
#include "DarkStyle.h"
#include "framelesswindow.h"

#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(new DarkStyle);

    FramelessWindow framelessWindow;

    framelessWindow.setWindowTitle("UDP Audio");
//    framelessWindow.setWindowIcon(a.style()->standardIcon(QStyle::SP_DesktopIcon));

    // create our mainwindow instance
    MainWindow *mainWindow = new MainWindow;

    // add the mainwindow to our custom frameless window
    framelessWindow.setContent(mainWindow);
    framelessWindow.setGeometry(mainWindow->geometry());
    framelessWindow.setFixedSize(mainWindow->width(),mainWindow->height()+50);

    QDesktopWidget widget;
    QRect screenGeometry = widget.screenGeometry();//.availableGeometry(widget.primaryScreen());

    int height = screenGeometry.height();
    int width = screenGeometry.width();
    framelessWindow.move(-50000,-50000);

    framelessWindow.move((width - framelessWindow.width()) / 2.0,
                    (height - framelessWindow.height()) / 2.0);
    framelessWindow.show();

    return a.exec();
}
