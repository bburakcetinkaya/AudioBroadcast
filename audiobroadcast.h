//#ifndef AUDIOBROADCAST_H
//#define AUDIOBROADCAST_H


//#include "audiohandler.h"
//#include <QObject>
//#include <QUdpSocket>
//#include <QAudioInput>
//#include <QAudioOutput>
//#include <QIODevice>

//class AudioHandler;
//class AudioBroadcast : public QObject
//{
//    Q_OBJECT
//public:
//    enum StreamType
//    {
//        file,
//        live
//    };
//    AudioBroadcast(QString targetAddress, quint16 port, AudioHandler *ah);

//    void stop();
//    void start(StreamType t);
//    void resume();
//    void pause();

//private:
//    void liveStream();
//    void fileStream();

//    QUdpSocket *m_socket;
//    QString m_targetAddress;
//    quint16 m_targetPort;


//    AudioHandler *m_audioHandler;
//    QAudioDeviceInfo *m_deviceInfo;
//    QAudioInput *m_input;
//    QIODevice *m_ioDevice;

//signals:

//};

//#endif // BROADCASTUDPSERVER_H
