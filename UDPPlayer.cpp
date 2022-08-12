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
void UDPPlayer::setBroadCastProperties(QString address, quint16 port,quint16 ssPort,quint16 volumePort)
{
    m_socket = new QUdpSocket();
    m_startStopSocket = new QUdpSocket();
    m_volumeSocket = new QUdpSocket();
    m_address = address;
    m_port = port;
    m_startStopPort = ssPort;
    m_volumePort = volumePort;
}
void UDPPlayer::start()
{
    m_ioDevice = m_input->start();
    if(m_type == fileStream)
        connect(m_ioDevice,SIGNAL(readyRead()),this,SLOT(streamFile()));
    else
        connect(m_ioDevice,SIGNAL(readyRead()),this,SLOT(streamLive()));
    setVolumeLevel(80);
    char startCmd[6] = {'u','n','m','u','t','e'};
    m_startStopSocket->writeDatagram(startCmd,6,QHostAddress(m_address),m_startStopPort);
}
void UDPPlayer::stop()
{
    m_input->stop();
    char stopCmd[4] = {'m','u','t','e'};
    m_startStopSocket->writeDatagram(stopCmd,4,QHostAddress(m_address),m_startStopPort);
}
void UDPPlayer::pause()
{
    m_input->suspend();
//    char stopCmd[4] = {'m','u','t','e'};
//    m_startStopSocket->writeDatagram(stopCmd,4,QHostAddress(m_address),m_startStopPort);
}
void UDPPlayer::resume()
{
    m_input->resume();
//    char startCmd[6] = {'u','n','m','u','t','e'};
//    m_startStopSocket->writeDatagram(startCmd,6,QHostAddress(m_address),m_startStopPort);
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
    if(data.len > 0 && data.len <= 1280)
    {
        m_socket->writeDatagram(data.audioData,data.len,QHostAddress(m_address),m_port);
    }
    else
        stop();
}
void UDPPlayer::setVolumeLevel(BYTE volumeLevel)
{

    char data[1] = {~volumeLevel};
//    qDebug() << data;
    if(!m_address.isEmpty())
        m_volumeSocket->writeDatagram(data,sizeof(data),QHostAddress(m_address),m_volumePort);
    else
    {
        m_address = "10.0.0.2";
        m_volumePort = 8888;
        m_volumeSocket->writeDatagram(data,sizeof(data),QHostAddress(m_address),m_volumePort);
    }
}

void UDPPlayer::setAudioFormat()
{
    // Set up the desired format
    m_format = new QAudioFormat();
    m_format->setSampleRate(16000);
    m_format->setChannelCount(1);
    m_format->setSampleSize(16);
    m_format->setCodec("audio/pcm");
    m_format->setByteOrder(QAudioFormat::BigEndian);
    m_format->setSampleType(QAudioFormat::UnSignedInt);


    m_info = new QAudioDeviceInfo(QAudioDeviceInfo::defaultInputDevice());
    if (!m_info->isFormatSupported(*m_format))
        *m_format = m_info->nearestFormat(*m_format);

    m_input = new QAudioInput(*m_format, this);
}
