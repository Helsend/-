#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    heatmapWidget = new HeatmapWidget();
    QLayoutItem* item = ui->widget->parentWidget()->layout()->replaceWidget(ui->widget, heatmapWidget);
    delete item;
    delete ui->widget;

    foreach (const QSerialPortInfo &qspinfo, QSerialPortInfo::availablePorts())
    {
        ui->comboBox_wait->addItem(qspinfo.portName());
        //ui->comboBox_poll->addItem(qspinfo.portName());
    }

    connect(&serial_wait, SIGNAL(signal_recvSerialData(QByteArray)),
            this, SLOT(showSerialData(QByteArray)));

    connect(&serial_poll, SIGNAL(signal_recvSerialData(QByteArray)),
            this, SLOT(showSerialData(QByteArray)));


    connect(&timer, SIGNAL(timeout()), this, SLOT(timingTask()));


    qDebug()<<tr("MainWindow::currentThreadId()   ==")<<QThread::currentThreadId();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showSerialData(QByteArray data)
{
    QString string;
    string = QString::fromLocal8Bit(data);

    ui->plainTextEdit->appendPlainText(data);


    // ui->plainTextEdit->textCursor().deletePreviousChar();

    static QByteArray buffer;
    buffer.append(data);
    //qDebug() << buffer;

    // QVector<double> heatData;

    // heatData.append(data.toDouble());

    //qDebug() << heatData;







    if (data.isEmpty()) return;
    if(data.at(0)=='a'){
        currentFrameData.clear();
        //currentFrameData.append(0.5);
    }

    if(data.at(0)!='a'){


        bool ok;
        double val1=data.toDouble(&ok);
        qDebug() <<val1;
        // 将接收到的char转换为0.0~1.0的浮点数
        //unsigned char byteValue = static_cast<unsigned char>(data.at(0)); // 取值范围0~255
        //qDebug() <<data.at(0);
        double normalizedValue = val1 ; // 大于0的值


        // 添加到当前帧数据
        currentFrameData.append(normalizedValue);

        if (currentFrameData.size() == 255) {
            currentFrameData.append(125);
        }

        // 当收集满256个数据点时更新热力图
        if (currentFrameData.size() == 256) {
            qDebug() <<currentFrameData;
            heatmapWidget->setHeatmapData(currentFrameData);
            currentFrameData.clear(); // 清空缓存，准备接收下一帧
            qDebug() << "热力图已更新";
        }
    }


}



void MainWindow::timingTask()
{
    QString str = ui->lineEdit->text();

    //char*  ch;
    QByteArray ba = str.toLocal8Bit();
    //ch = ba.data();

    serial_wait.sendSerialData(ba);

}


void MainWindow::on_pushButton_con_clicked()
{

    bool ret = serial_wait.openSerialPort(ui->comboBox_wait->currentText(), 115200);
    if(ret)
        qDebug() << "open serial success"<< endl;
    else
        qDebug() << "open serial failed"<< endl;

    // ret = serial_poll.openSerialPort(ui->comboBox_poll->currentText(), 115200);
    // if(ret)
    //     qDebug() << "open serial_POLL success"<< endl;
    // else
    //     qDebug() << "open serial_POLL failed"<< endl;


}

void MainWindow::on_pushButton_dis_clicked()
{
    serial_wait.closeSerialPort();
    serial_poll.closeSerialPort();
    timer.stop();
    ui->pushButton_poll->setText("发送");
}

void MainWindow::on_pushButton_poll_clicked()
{
    if(ui->pushButton_poll->text() == "发送")
    {
        timer.start(5*1000);
        ui->pushButton_poll->setText("停止");
    }

    else
    {
        timer.stop();
        ui->pushButton_poll->setText("发送");
    }

}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->plainTextEdit->clear();
}
