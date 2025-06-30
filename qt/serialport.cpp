#include "serialport.h"

SerialPortBasic::SerialPortBasic(QObject *parent) : QObject(parent)
{


    qDebug()<<tr("SerialPortBasic::currentThreadId()  1 ==")<<QThread::currentThreadId();
    m_serial = new QSerialPort;
    m_thread = new QThread;

    connect(m_serial, SIGNAL(readyRead()), this, SLOT(slot_recvSerialData()));

    this->moveToThread(m_thread);

    m_thread->start();


}
SerialPortBasic::~SerialPortBasic()
{
    if(m_serial->isOpen())
    {
        m_serial->close();
        delete m_serial;
        m_serial = NULL;
    }
    if(m_thread->isRunning())
    {
        m_thread->quit();
        m_thread->wait();
        delete m_thread;
        m_thread = NULL;
    }

    qDebug() << "SerialPort exit !!!" ;
}


/**
 * @brief SerialPortBasic::initSerialPort
 */
void SerialPortBasic::initSerialPort(QString name, qint32 baud)
{

    //设置波特率
    m_serial->setBaudRate(115200);
    //设置数据位数
    m_serial->setDataBits(QSerialPort::Data8);
    //设置奇偶校验
    m_serial->setParity(QSerialPort::NoParity);
    //设置停止位
    m_serial->setStopBits(QSerialPort::OneStop);
    //serial->setStopBits(QSerialPort::TwoStop);
    //设置流控制
    m_serial->setFlowControl(QSerialPort::NoFlowControl);

    //设置端口号
    m_serial->setPortName(name);

    //设置波特率
    m_serial->setBaudRate(baud);



}

/**
 * @brief SerialPortBasic::openSerialPort
 * @return
 */
bool SerialPortBasic::openSerialPort(QString name, qint32 baud)
{
    initSerialPort(name, baud);

    //打开串口
    bool ret = m_serial->open(QIODevice::ReadWrite);

    return ret;



}

/**
 * @brief SerialPortBasic::startWork
 */
void SerialPortBasic::sendSerialData(QByteArray data)
{
    m_serial->write(data.data(), data.size());
}

/**
 * @brief SerialPortBasic::startWork
 */
void SerialPortBasic::slot_recvSerialData()
{
    QByteArray data = m_serial->readAll();		//读数据
    emit signal_recvSerialData(data);
    qDebug() << "new data -- "  << data.data()
             << "recvSerialData" << QThread::currentThreadId() ;

}
/**
 * @brief closeSerialPort
 */
void SerialPortBasic::closeSerialPort()
{
    if(m_serial->isOpen())
        m_serial->close();
}



