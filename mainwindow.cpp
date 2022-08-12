#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QTimer>
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
    m_udpFilePlayer = new UDPPlayer(m_fileName);
    m_udpFilePlayer->setBroadCastProperties("192.168.1.22",9999);
//    m_audioHandler = new AudioHandler(m_fileName, 16000,1,16,"audio/pcm",QAudioFormat::UnSignedInt , QAudioFormat::LittleEndian);
    m_name = m_fileName.mid(m_fileName.lastIndexOf("/")+1);
    m_name.remove(m_name.lastIndexOf('.'),4);
    ui->fileName_textEdit->setText(m_name);
    ui->fileName_textEdit->setAlignment(Qt::AlignVCenter);
    ui->start_button->setEnabled(true);
    ui->file_checkBox->setEnabled(false);
    ui->live_checkBox->setEnabled(false);
    ui->openFile_button->setEnabled(false);

}

void MainWindow::on_stop_button_clicked()
{
    m_udpFilePlayer->stop();
    m_udpFilePlayer->deleteLater();
//    ui->start_button->setText("Start");
    ui->start_button->setEnabled(false);
    ui->stop_button->setEnabled(false);
    ui->pause_button->setEnabled(false);
    ui->file_checkBox->setEnabled(true);
    ui->live_checkBox->setEnabled(true);
    if(!ui->live_checkBox->isChecked())
      ui->openFile_button->setEnabled(true);
    ui->fileName_textEdit->setText("");
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
    if(ui->streamType_buttonGroup->checkedButton() == ui->file_checkBox)
    {
        m_udpFilePlayer->setBroadCastProperties("192.168.1.26",9999);
        m_udpFilePlayer->start();
        ui->fileName_textEdit->setText("Playing...  " + m_name);
        m_sliderValue = m_udpFilePlayer->getFileSize();
        std::cout << m_sliderValue << " slider" << std::endl;
        int sliderPosition = 0;
        ui->horizontalSlider->setMaximum(100);
        ui->horizontalSlider->setSliderPosition(sliderPosition);
        ui->horizontalSlider->setSingleStep(100/(m_sliderValue/1280));
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [&](){ui->horizontalSlider->setSliderPosition(
                                                    ui->horizontalSlider->sliderPosition()+1);});
        timer->start(250);
    }
    else
    {
        m_udpFilePlayer = new UDPPlayer();
        m_udpFilePlayer->setBroadCastProperties("192.168.1.26",9999);
        m_udpFilePlayer->start();
        ui->fileName_textEdit->setText("Live streaming...");
    }

    ui->start_button->setEnabled(false);
    ui->stop_button->setEnabled(true);
    ui->pause_button->setEnabled(true);
}


void MainWindow::on_live_checkBox_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->openFile_button->setEnabled(false);
        ui->start_button->setEnabled(true);
    }
}


void MainWindow::on_file_checkBox_stateChanged(int arg1)
{
   if(arg1)
     ui->openFile_button->setEnabled(true);
}

