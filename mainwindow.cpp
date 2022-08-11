#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openFile_button_clicked()
{
    m_fileName = QFileDialog::getOpenFileName(this, tr("Open Audio File"), "../", tr("Audio Files (*.wav *.mp3)"));
    m_audioHandler = new AudioHandler(m_fileName, 16000,1,16,"audio/pcm",QAudioFormat::UnSignedInt , QAudioFormat::LittleEndian);
}

void MainWindow::on_stop_button_clicked()
{
//    m_audioBroadcast->stop();
    ui->start_button->setText("Start");
}


void MainWindow::on_pause_button_clicked()
{
//    m_audioBroadcast->pause();
}


void MainWindow::on_start_button_clicked(bool checked)
{
    m_audioHandler->setBroadCastProperties("224.0.0.2",9999);
//    if(!checked)
//    {
//       if(ui->streamType_buttonGroup->checkedButton() == ui->file_checkBox)
    m_audioHandler->start(AudioHandler::StreamType::file);
    ui->start_button->setText("Resume");
//    }
//    if(checked)
//    m_audioBroadcast->resume();
}

