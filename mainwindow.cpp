#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->horizontalSlider->setMaximum(255);
    ui->horizontalSlider->setSingleStep(2);
//    ui->horizontalSlider->setSliderPosition(80);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openFile_button_clicked()
{
    m_fileName = QFileDialog::getOpenFileName(this, tr("Open Audio File"), "../", tr("Audio Files (*.wav)"));
    if(m_fileName.isEmpty()) return;
    m_udpFilePlayer = new UDPPlayer(m_fileName);
    m_udpFilePlayer->setBroadCastProperties("10.0.0.2",9999,7777,8888);
    m_name = m_fileName.mid(m_fileName.lastIndexOf("/")+1);
    m_name.remove(m_name.lastIndexOf('.'),4);
    ui->fileName_textEdit->setText(m_name);
    ui->fileName_textEdit->setAlignment(Qt::AlignVCenter);
    if(m_fileName.isEmpty())
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

//    if(!ui->live_checkBox->isChecked())
    ui->openFile_button->setEnabled(true);
    ui->horizontalSlider->setEnabled(false);
    ui->fileName_textEdit->setText("");
}


void MainWindow::on_pause_button_clicked()
{
    m_udpFilePlayer->pause();
    ui->start_button->setEnabled(true);
    ui->pause_button->setEnabled(false);    
}


void MainWindow::on_start_button_clicked(bool checked)
{
    if(ui->streamType_buttonGroup->checkedButton() == ui->file_checkBox)
    {
        m_udpFilePlayer->setBroadCastProperties("10.0.0.2",9999,7777,8888);
        m_udpFilePlayer->start();
        m_udpFilePlayer->setVolumeLevel(ui->horizontalSlider->value());
        ui->fileName_textEdit->setText("Playing...  " + m_name);


    }
    else
    {
        m_udpFilePlayer = new UDPPlayer();
        m_udpFilePlayer->setBroadCastProperties("10.0.0.2",9999,7777,8888);
        m_udpFilePlayer->start();
        m_udpFilePlayer->setVolumeLevel(ui->horizontalSlider->value());
        ui->fileName_textEdit->setText("Live streaming...");
    }

    ui->start_button->setEnabled(false);
    ui->stop_button->setEnabled(true);
    ui->pause_button->setEnabled(true);
    ui->horizontalSlider->setEnabled(true);
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
   {
        ui->openFile_button->setEnabled(true);
        ui->start_button->setEnabled(true);
   }
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{

    m_udpFilePlayer->setVolumeLevel(value);
    ui->volume_label->setText(QString::number(value*100/255));
}

