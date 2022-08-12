#ifndef UDPPLAYER_H
#define UDPPLAYER_H

#include <QFile>
#include <QUdpSocket>
#include <QAudioDeviceInfo>
#include <QAudioInput>

class UDPPlayer : public QObject
{
    Q_OBJECT
public:
    enum StreamType
    {
        liveStream,
        fileStream
    };

    struct AudioData
    {
        char audioData[7680];
        int len{};
    };

    UDPPlayer(QString filePath);
    UDPPlayer();
    ~UDPPlayer();
    void setBroadCastProperties(QString address, quint16 port);
    void start();
    void stop();
    void pause();
    void resume();
private slots:
    void streamFile();
    void streamLive();
private:
    void setAudioFormat();
    void connectSignalSlots();

    QAudioDeviceInfo* m_info;
    QAudioFormat* m_format;

    QIODevice *m_ioDevice;
    QAudioInput* m_input;
    QString m_filePath{};
    QFile m_file;

    // udp
    QUdpSocket *m_socket;
    QString m_address;
    quint16 m_port;

    StreamType m_type;
};

#endif // UDPPLAYER_H
