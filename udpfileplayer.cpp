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
//    connect(m_ioDevice,SIGNAL(readyRead()),this,SLOT(streamFile()));
//    QByteArray data;
//    data.append(m_file.readAll());
//    m_file.close();
//    m_socket->writeDatagram(data,sizeof(data), QHostAddress(m_address),m_port);

//    std::cout << "size of data: " << sizeof(data);
}
void UDPFilePlayer::stop()
{

}
void UDPFilePlayer::pause()
{

}
void UDPFilePlayer::resume()
{

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
    m_output->stop();
}
void UDPFilePlayer::handleStateChanged(QAudio::State newState)
{
    switch (newState) {
        case QAudio::IdleState:
            // Finished playing (no more data)
            m_output->stop();
            m_file.close();
            delete m_output;
            break;

        case QAudio::StoppedState:
            // Stopped for other reasons
            if (m_output->error() != QAudio::NoError) {
                // Error handling
            }
            break;

        default:
            // ... other cases as appropriate
            break;
    }
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
//void AudioHandler::start(StreamType t)
//{
//    m_output = new QAudioOutput(*m_format);
//    m_ioDevice = m_output->start();

//    if(t == StreamType::file)
//        connect(m_ioDevice,SIGNAL(readyRead()),this,SLOT(fileStream()));
//    if(t == StreamType::live)
//        connect(m_ioDevice,SIGNAL(readyRead()),this,SLOT(liveStream()));
//}
//void AudioHandler::liveStream()
//{

//}
//void AudioHandler::fileStream()
//{
//    AudioData m_data;
//    memset(&m_data,0,sizeof(m_data));
//    QByteArray dummy;
//    dummy = m_ioDevice->readAll();
//    m_data.len = m_file.read(m_data.audioData,m_format->bytesForFrames(m_format->framesForDuration(40000)));
//    if(m_data.len)
//    {
//        m_socket->writeDatagram(m_data.audioData,m_data.len,QHostAddress(m_address),m_port);
//        std::cout << "data size: " << m_data.len;
//    }
//}
//void AudioHandler::resume()
//{
//    m_output->resume();
//}
//void AudioHandler::pause()
//{
//    m_output->suspend();
//}

//void AudioHandler::stop()
//{
//    if(m_socket->isOpen())
//    {
//        m_socket->disconnect();
//        m_socket->disconnectFromHost();
//        m_socket->close();
//        m_socket->deleteLater();
//    }
//}
