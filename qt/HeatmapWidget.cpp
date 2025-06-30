#include "heatmapwidget.h"
#include <QPainter>
#include <QColor>
#include <cmath>

HeatmapWidget::HeatmapWidget(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(800, 800);
}

void HeatmapWidget::setHeatmapData(const QVector<double>& data)
{
    if(data.size() != m_gridSize*m_gridSize) return;
    m_data = data;
    update();
}

void HeatmapWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const int cellWidth = width() / m_gridSize;
    const int cellHeight = height() / m_gridSize;

    // Find min/max for normalization
    // float minVal = INFINITY, maxVal = -INFINITY;
    // for(float val : m_data) {
    //     if(val < minVal) minVal = val;
    //     if(val > maxVal) maxVal = val;
    // }
    const double minVal = 0.0;
    const double maxVal = 20.0;

    // for(float val : m_data) {
    //     if(val < minVal) minVal = val;
    //     if(val > maxVal) maxVal = val;
    // }

    for(int y=0; y<m_gridSize; y++) {
        for(int x=0; x<m_gridSize; x++) {
            int index = y * m_gridSize + x;
            if(index >= m_data.size()) { // 防止越界
                continue;
            }

            // double normalized = (m_data[index] - minVal) / (maxVal - minVal);
            // QColor color = QColor::fromHsv(240 - static_cast<int>(240 * normalized), 255, 255);
            //qDebug() << normalized;
            double normalized = qBound(4.0, m_data[index], 125.0);
            //qDebug() << normalized;
            //QColor color = QColor::fromHsvF(0.66 * (1.0 - normalized), 255, 255);

            QColor color;
            color.setHsv(0,normalized*2,255,255);

            painter.fillRect(x*cellWidth, y*cellHeight, cellWidth, cellHeight, color);
        }
    }
}
