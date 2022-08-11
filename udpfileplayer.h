#ifndef UDPFILEPLAYER_H
#define UDPFILEPLAYER_H

#include <QFile>
#include <QUdpSocket>
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QAudioDecoder>
#include <QAudioBuffer>
class UDPFilePlayer : public QObject
{
    Q_OBJECT
public:
    struct AudioData
    {
        char audioData[7680];
        int len{};
    };

    UDPFilePlayer(QString filePath);
    void setBroadCastProperties(QString address, quint16 port);
    void start();
    void stop();
    void pause();
    void resume();
private slots:
    void streamFile();
    void handleStateChanged(QAudio::State newState);
private:
    void setAudioFormat();
    void connectSignalSlots();

    QAudioDeviceInfo* m_info;
    QAudioFormat* m_format;

    QIODevice *m_ioDevice;
    QAudioBuffer* m_audioBuffer;
    QAudioDecoder* m_audioDecoder;
    QAudioOutput* m_output;
    QString m_filePath{};
    QFile m_file;

    // udp
    QUdpSocket *m_socket;
    QString m_address;
    quint16 m_port;
};

#endif // UDPFILEPLAYER_H
