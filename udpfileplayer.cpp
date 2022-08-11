#include "udpfileplayer.h"
#include <QDebug>
#include <iostream>
UDPFilePlayer::UDPFilePlayer(QString filePath)
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
        setAudioFormat();
    }
    connectSignalSlots();
}
UDPFilePlayer::~UDPFilePlayer()
{
    if (m_file.open(QIODevice::ReadOnly))
    {
        m_file.close();
    }
    if(m_socket->isOpen())
    {
        m_socket->close();
    }
    delete m_socket;
    delete m_output;
    delete m_info;
    delete m_format;
}
void UDPFilePlayer::connectSignalSlots()
{
//    connect(m_output, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));
}
void UDPFilePlayer::setBroadCastProperties(QString address, quint16 port)
{
    m_socket = new QUdpSocket();
    m_address = address;
    m_port = port;
}
void UDPFilePlayer::start()
{
    m_output->start(m_ioDevice);
    streamFile();
}
void UDPFilePlayer::stop()
{
    m_output->stop();    
}
void UDPFilePlayer::pause()
{
    m_output->suspend();
}
void UDPFilePlayer::resume()
{
    m_output->resume();
}
void UDPFilePlayer::streamFile()
{
    qDebug() << "hello there";
    qDebug() << "hahaha";
    AudioData m_data;
    memset(&m_data,0,sizeof(m_data));


    do
    {
        m_data.len = m_file.read(m_data.audioData,m_format->bytesForFrames(m_format->framesForDuration(40000)));
        m_socket->writeDatagram(m_data.audioData,m_data.len,QHostAddress(m_address),m_port);
    }while (m_data.len);
    stop();
}

void UDPFilePlayer::setAudioFormat()
{
        // Set up the desired format, for example:
        m_format = new QAudioFormat();
        m_format->setSampleRate(16000);
        m_format->setChannelCount(1);
        m_format->setSampleSize(16);
        m_format->setCodec("audio/pcm");
        m_format->setByteOrder(QAudioFormat::LittleEndian);
        m_format->setSampleType(QAudioFormat::UnSignedInt);


    m_info = new QAudioDeviceInfo(QAudioDeviceInfo::defaultOutputDevice());
    if (!m_info->isFormatSupported(*m_format))
        *m_format = m_info->nearestFormat(*m_format);

    m_output = new QAudioOutput(*m_format, this);
}
