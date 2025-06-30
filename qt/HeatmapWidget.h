#ifndef HEATMAPWIDGET_H
#define HEATMAPWIDGET_H

#include <QWidget>
#include <QVector>
#include <QDebug>

class HeatmapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HeatmapWidget(QWidget *parent = nullptr);
    void setHeatmapData(const QVector<double>& data);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<double> m_data;
    int m_gridSize = 16;
};

#endif // HEATMAPWIDGET_H
