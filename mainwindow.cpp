#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

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
    m_udpFilePlayer = new UDPFilePlayer(m_fileName);
    m_udpFilePlayer->setBroadCastProperties("192.168.1.26",9999);
//    m_audioHandler = new AudioHandler(m_fileName, 16000,1,16,"audio/pcm",QAudioFormat::UnSignedInt , QAudioFormat::LittleEndian);
    ui->fileName_textEdit->setText(m_fileName.mid(m_fileName.lastIndexOf("/")+1));
    ui->fileName_textEdit->setAlignment(Qt::AlignVCenter);
    ui->start_button->setEnabled(true);
    ui->file_checkBox->setEnabled(true);

}

void MainWindow::on_stop_button_clicked()
{
    m_udpFilePlayer->stop();
//    ui->start_button->setText("Start");
    ui->start_button->setEnabled(true);
    ui->stop_button->setEnabled(false);
    ui->pause_button->setEnabled(false);
}


void MainWindow::on_pause_button_clicked()
{
    m_udpFilePlayer->pause();
    ui->start_button->setEnabled(true);
    ui->pause_button->setEnabled(false);
    ui->start_button->setText("Resume");
}


void MainWindow::on_start_button_clicked(bool checked)
{
    std::cout << "hello clicked" << std::endl;
    m_udpFilePlayer->setBroadCastProperties("192.168.1.26",9999);
    m_udpFilePlayer->start();
//    if(!checked)
//    {
//        std::cout << "not clicked" << std::endl;
//       if(ui->streamType_buttonGroup->checkedButton() == ui->file_checkBox)


//       if(ui->streamType_buttonGroup->checkedButton() == ui->live_checkBox)
//           m_audioHandler->start(AudioHandler::StreamType::live);
//    }
//    if(checked)
//    {
//        std::cout << "clicked" << std::endl;
//        m_udpFilePlayer->resume();
//    }
    ui->start_button->setEnabled(false);
    ui->stop_button->setEnabled(true);
    ui->pause_button->setEnabled(true);
}

