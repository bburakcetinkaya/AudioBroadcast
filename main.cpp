#include "mainwindow.h"
#include "DarkStyle.h"
#include "framelesswindow.h"

#include <QApplication>

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
    framelessWindow.show();

    return a.exec();
}
