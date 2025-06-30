#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "serialport.h"
#include "heatmapwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void showSerialData(QByteArray);
    void timingTask();

    void on_pushButton_con_clicked();

    void on_pushButton_dis_clicked();

    void on_pushButton_poll_clicked();

    void on_pushButton_clear_clicked();

signals:
    void sendMsgData(char* data, qint64 len);

private:
    Ui::MainWindow *ui;
    QTimer timer;
    SerialPortBasic  serial_wait;
    SerialPortBasic  serial_poll;
    HeatmapWidget *heatmapWidget;

    QVector<double> currentFrameData;  // 存储当前接收的数据帧
    bool isCollectingData = false;// 标记是否在等待帧头
    int receivedCount = 0;
};

#endif // MAINWINDOW_H
