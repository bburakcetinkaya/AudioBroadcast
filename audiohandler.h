#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H

#include <QObject>
#include <QAudio>
#include <QAudioFormat>
#include <QAudioInput>
#include <QAudioOutput>
#include <QIODevice>
#include <QUdpSocket>
#include <QDebug>
#include <QAudioDecoder>
#include <QFile>
#include <QDir>

class AudioHandler : public QObject
{
    Q_OBJECT
public:
    enum StreamType
    {
        file,
        live
    };
    struct AudioData
    {
        char audioData[7680];
        int len{};
    };

    AudioHandler(QString fileName, int sampleRate,int channelCount,int sampleSize,QString codec,QAudioFormat::SampleType audioFormat, QAudioFormat::Endian byteOrder);
    QAudioFormat* getAudioFormat()const { return m_format; }
    void setBroadCastProperties(QString address, quint16 port);
    void readAudioFile();

    void start(StreamType t);
    void stop();
    void resume();
    void pause();

    void liveStream();
    void fileStream();
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
    QIODevice *m_ioDevice;

    // udp
    QUdpSocket *m_socket;
    QString m_address;
    quint16 m_port;
};

#endif // AUDIO_H
