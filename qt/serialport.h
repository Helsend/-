#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QThread>
#include <QSerialPort>        //提供访问串口的功能
#include <QSerialPortInfo>    //提供系统中存在的串口的信息
#include <QDebug>
#include <QTimer>

class SerialPortBasic : public QObject
{
    Q_OBJECT

public:
    explicit SerialPortBasic(QObject *parent = nullptr);
    virtual  ~SerialPortBasic();

    //打开串口
    bool openSerialPort(QString name, qint32 baud);
    //关闭串口
    void closeSerialPort();
    //发送数据
    void sendSerialData(QByteArray);

signals:

    void signal_recvSerialData(QByteArray);

public slots:

    void slot_recvSerialData();

private:

    QSerialPort *m_serial;
    QThread     *m_thread;

    void initSerialPort(QString  , qint32  );

};




#endif // SERIALPORT_H
