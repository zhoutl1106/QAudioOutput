#include "widget.h"
#include "ui_widget.h"
#include <QBuffer>
#include <QDebug>
#include <math.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QAudioFormat format;
    format.setSampleRate(8000);
    format.setChannels(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());

    if (!info.isFormatSupported(format))
    {
        qWarning()<<"raw audio format not supported by backend, cannot play audio.";
        return;
    }
    audio = new QAudioOutput(format, this);

    QByteArray fData;
    QBuffer *m_pBuffer = new QBuffer();

    for( int i = 0; i <4000; ++i )
    {
        fData.push_back(256*sin(2*3.1415*i*440/8000));
    }

    m_pBuffer->open(QIODevice::ReadWrite);
    m_pBuffer->write( fData );

    m_pBuffer->close();


    QIODevice* ioDevice = audio->start();
    ioDevice->write( m_pBuffer->buffer() );
}

Widget::~Widget()
{
    delete ui;
}
