#include "UDPPlayer.h"
#include <QDebug>
#include <iostream>
#include <windows.h>
UDPPlayer::UDPPlayer(QString filePath)
    :m_filePath{filePath}
{
    qDebug() << m_filePath;
    m_file.setFileName(filePath);
    if (!m_file.open(QIODevice::ReadOnly))
    {
         assert("Cannot open audio file!");
    }
    else
    {
        m_fileSize = m_file.size();
        setAudioFormat();
        m_type = StreamType::fileStream;
    }

}
UDPPlayer::UDPPlayer()
{
    setAudioFormat();
    m_type = StreamType::liveStream;

}
UDPPlayer::~UDPPlayer()
{
    if (m_file.isOpen())
    {
        m_file.close();
    }
    if(m_socket->isOpen())
    {
        m_socket->close();
    }
    delete m_socket;
    delete m_input;
    delete m_info;
    delete m_format;
}
void UDPPlayer::connectSignalSlots()
{
//    connect(m_input, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));
}
void UDPPlayer::setBroadCastProperties(QString address, quint16 port)
{
    m_socket = new QUdpSocket();
    m_address = address;
    m_port = port;
}
void UDPPlayer::start()
{
    m_ioDevice = m_input->start();
    if(m_type == fileStream)
        connect(m_ioDevice,SIGNAL(readyRead()),this,SLOT(streamFile()));
    else
        connect(m_ioDevice,SIGNAL(readyRead()),this,SLOT(streamLive()));
}
void UDPPlayer::stop()
{
    m_input->stop();
}
void UDPPlayer::pause()
{
    m_input->suspend();
}
void UDPPlayer::resume()
{
    m_input->resume();
}
void UDPPlayer::streamFile()
{
    AudioData data;
    memset(&data,0,sizeof(data));

    QByteArray dummy;
    dummy = m_ioDevice->readAll();
        data.len = m_file.read(data.audioData,m_format->bytesForFrames(m_format->framesForDuration(40000)));
        qDebug() << "file stream current data size: " << data.len;
        if(data.len)
            m_socket->writeDatagram(data.audioData,data.len,QHostAddress(m_address),m_port);
        else
            stop();

}
void UDPPlayer::streamLive()
{
    AudioData data;
    memset(&data,0,sizeof(data));

    data.len = m_ioDevice->read(data.audioData,m_format->bytesForFrames(m_format->framesForDuration(40000)));
    qDebug() << "live stream current data size: " << data.len;
    if(data.len)
        m_socket->writeDatagram(data.audioData,data.len,QHostAddress(m_address),m_port);
    else
        stop();
    qDebug() << "live stream current data size: " << data.len;
}

void UDPPlayer::setAudioFormat()
{
    // Set up the desired format
    m_format = new QAudioFormat();
    m_format->setSampleRate(16000);
    m_format->setChannelCount(1);
    m_format->setSampleSize(16);
    m_format->setCodec("audio/pcm");
    m_format->setByteOrder(QAudioFormat::LittleEndian);
    m_format->setSampleType(QAudioFormat::UnSignedInt);


    m_info = new QAudioDeviceInfo(QAudioDeviceInfo::defaultInputDevice());
    if (!m_info->isFormatSupported(*m_format))
        *m_format = m_info->nearestFormat(*m_format);

    m_input = new QAudioInput(*m_format, this);
}
