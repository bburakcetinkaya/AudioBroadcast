#include "audiohandler.h"


AudioHandler::AudioHandler(QString fileName, int sampleRate,int channelCount,int sampleSize,QString codec,QAudioFormat::SampleType audioFormat, QAudioFormat::Endian byteOrder)
    : m_sampleRate{sampleRate}
     ,m_channelCount{channelCount}
     ,m_sampleSize{sampleSize}
     ,m_codec{codec}
     ,m_audioFormat{audioFormat}
     ,m_byteOrder{byteOrder}
{
    m_deviceInfo = new QAudioDeviceInfo(QAudioDeviceInfo::defaultInputDevice());
    constructAudio(fileName);
    setAudioFormat();
}

void AudioHandler::setAudioFormat()
{
    m_format = new QAudioFormat();
    m_format->setSampleRate(m_sampleRate);
    m_format->setChannelCount(m_channelCount);
    m_format->setSampleSize(m_sampleSize);
    m_format->setCodec(m_codec);
    m_format->setSampleType(m_audioFormat);
    m_format->setByteOrder(m_byteOrder);

    *m_format = m_deviceInfo->nearestFormat(*m_format);
    m_input = new QAudioInput(*m_format);
}
void AudioHandler::constructAudio(QString fileName)
{

    m_file.setFileName(fileName);
    if (m_file.open(QIODevice::ReadOnly))
    {

    }
    else
        assert("Cannot open audio file!");

}
void AudioHandler::setBroadCastProperties(QString address, quint16 port)
{
    m_socket = new QUdpSocket();
    m_address = address;
    m_port = port;
}
void AudioHandler::readAudioFile()
{
//     m_data->len = m_file.read(m_data->audioData,m_format->bytesForFrames(a));
}
void AudioHandler::start(StreamType t)
{
    m_input = new QAudioInput(*m_format);
    m_ioDevice = m_input->start();

    if(t == StreamType::file)
        connect(m_ioDevice,SIGNAL(readyRead()),this,SLOT(fileStream()));
    if(t == StreamType::live)
        connect(m_ioDevice,SIGNAL(readyRead()),this,SLOT(liveStream()));
}
void AudioHandler::liveStream()
{

}
void AudioHandler::fileStream()
{
    AudioData m_data;
    memset(&m_data,0,sizeof(m_data));
    QByteArray dummy;
    dummy = m_ioDevice->readAll();
    m_data.len = m_file.read(m_data.audioData,m_format->bytesForFrames(m_format->framesForDuration(40000)));
    if(m_data.len)
    m_socket->writeDatagram(m_data.audioData,m_data.len,QHostAddress(m_address),m_port);
}
void AudioHandler::resume()
{
    m_input->resume();
}
void AudioHandler::pause()
{
    m_input->suspend();
}

void AudioHandler::stop()
{
    if(m_socket->isOpen())
    {
        m_socket->disconnect();
        m_socket->disconnectFromHost();
        m_socket->close();
        m_socket->deleteLater();
    }
}

