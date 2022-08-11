#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "audiohandler.h"

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openFile_button_clicked();

    void on_stop_button_clicked();

    void on_pause_button_clicked();

    void on_start_button_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    QString m_fileName{};
    QFile m_file{};

    AudioHandler *m_audioHandler;
//    AudioBroadcast *m_audioBroadcast;
};
#endif // MAINWINDOW_H
