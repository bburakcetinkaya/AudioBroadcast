#include "audiohandler.h"


AudioHandler::AudioHandler(QString fileName, int sampleRate,int channelCount,int sampleSize,QString codec,QAudioFormat::SampleType audioFormat, QAudioFormat::Endian byteOrder)
    : m_sampleRate{sampleRate}
     ,m_channelCount{channelCount}
     ,m_sampleSize{sampleSize}
     ,m_codec{codec}
     ,m_audioFormat{audioFormat}
     ,m_byteOrder{byteOrder}
{

    m_deviceInfo = new QAudioDeviceInfo();
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
        qint32 a = m_format->framesForDuration(40000);
        m_data = new AudioData{};
        qDebug() << "çıkışş";
        memset(m_data,0,sizeof(*m_data));
        m_data->len = m_file.read(m_data->audioData,m_format->bytesForFrames(a));
        qDebug() << "çıkışş";
                    //        readAudioFile();
    }
    else
        assert("Cannot open audio file!");

}
void AudioHandler::readAudioFile()
{

}

