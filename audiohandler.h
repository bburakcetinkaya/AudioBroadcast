#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H

#include <QObject>
#include <QAudio>
#include <QAudioFormat>
#include <QAudioInput>
#include <QAudioOutput>
#include <QIODevice>
#include <QDebug>
#include <QAudioDecoder>
#include <QFile>
#include <QDir>

class AudioHandler
{
public:

    struct AudioData
    {
        char audioData[7680];
        int len{};
    };

    AudioHandler(QString fileName, int sampleRate,int channelCount,int sampleSize,QString codec,QAudioFormat::SampleType audioFormat, QAudioFormat::Endian byteOrder);
    QAudioFormat* getAudioFormat()const { return m_format; }
    void readAudioFile();
    AudioData* getAudioData() const { return m_data; }
private:

    void setAudioFormat();
    void constructAudio(QString fileName);

    int m_sampleRate{};
    int m_channelCount{};
    int m_sampleSize{};
    QString m_codec{};
    QAudioFormat::SampleType m_audioFormat{};
    QAudioFormat::Endian m_byteOrder{};

    QFile m_file;

    QAudioFormat *m_format;
    AudioData* m_data;
    QAudioDeviceInfo *m_deviceInfo;
    QAudioInput *m_input;

};

#endif // AUDIO_H
