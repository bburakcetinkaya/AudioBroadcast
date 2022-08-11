//#include "audiobroadcast.h"

//AudioBroadcast::AudioBroadcast(QString targetAddress, quint16 port, AudioHandler* ah)
//    : m_targetAddress{targetAddress}
//    , m_targetPort{port}
//{
//    m_audioHandler = ah;
//    m_socket = new QUdpSocket();
//    m_deviceInfo = new QAudioDeviceInfo(QAudioDeviceInfo::defaultInputDevice());

//}
//void AudioBroadcast::start(StreamType t)
//{
//    m_input = new QAudioInput(*m_audioHandler->getAudioFormat());
//    qDebug() << "before io device";
//    m_ioDevice = m_input->start();
//    qDebug() << "after io device";
//    if(t == StreamType::file)
//        connect(m_ioDevice,SIGNAL(readyRead()),this,SLOT(fileStream()));
//    if(t == StreamType::live)
//        connect(m_ioDevice,SIGNAL(readyRead()),this,SLOT(liveStream()));
//}
//void AudioBroadcast::liveStream()
//{

//}
//void AudioBroadcast::fileStream()
//{
//    AudioHandler::AudioData* data = m_audioHandler->getAudioData();
//    m_socket->writeDatagram(data->audioData,data.len,QHostAddress(m_targetAddress),m_targetPort);
//}
//void AudioBroadcast::resume()
//{
//    m_input->suspend();
//}
//void AudioBroadcast::pause()
//{
//    m_input->stop();
//}

//void AudioBroadcast::stop()
//{
//    if(m_socket->isOpen())
//    {
//        m_socket->disconnect();
//        m_socket->disconnectFromHost();
//        m_socket->close();
//        m_socket->deleteLater();
//    }
//}
