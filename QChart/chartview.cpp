/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "chartview.h"
#include <QtGui/QMouseEvent>
#include <QtCore/QDebug>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QValueAxis>
#include <QtCore/QTime>

QT_CHARTS_USE_NAMESPACE

ChartView::ChartView(QWidget *parent)
    : QChartView(parent)
{
}

//![1]
void ChartView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {

    case Qt::Key_Up:
        chart()->zoom(1.1);
        polarChart->axisX()->setRange(0, 360);
        polarChart->axisY()->setMin(0);
        break;
    case Qt::Key_Down:
        chart()->zoom(0.9);
        polarChart->axisX()->setRange(0, 360);
        polarChart->axisY()->setMin(0);
        break;
    case Qt::Key_PageUp:
        chart()->zoom(1.5);
        polarChart->axisX()->setRange(0, 360);
        polarChart->axisY()->setMin(0);
        break;
    case Qt::Key_PageDown:
        chart()->zoom(0.7);
        polarChart->axisX()->setRange(0, 360);
        polarChart->axisY()->setMin(0);
        break;
    default:
        QGraphicsView::keyPressEvent(event);
        break;
    }
}
//![1]

void ChartView::initPolarChart(void)
{
    const qreal angularMin = 0;
    const qreal angularMax = 360;

    const qreal radialMin = 0;
    const qreal radialMax = 10000;

    series1 = new QScatterSeries();
    series1->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series1->setMarkerSize(5.0);
    series1->setBorderColor(series1->color());

    for (int i = angularMin; i <= angularMax; i += 10)
        series1->append(i, (i / radialMax) * radialMax + 8.0);

    series2 = new QSplineSeries();
    series2->setName("spline");
    for (int i = 135; i <= 225; i += 10)
        series2->append(i, 10000);

    series3 = new QAreaSeries();
    series3->setUpperSeries(series2);

    //![1]
    polarChart = new QPolarChart();
    //![1]
    polarChart->addSeries(series1);
    polarChart->addSeries(series2);
    polarChart->addSeries(series3);

    //![2]
    QValueAxis *angularAxis = new QValueAxis();
    angularAxis->setTickCount(9); // First and last ticks are co-located on 0/360 angle.
    angularAxis->setLabelFormat("%.1f");
    polarChart->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);

    QValueAxis *radialAxis = new QValueAxis();
    radialAxis->setTickCount(9);
    radialAxis->setLabelFormat("%d");
    polarChart->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);
    //![2]

    series1->attachAxis(radialAxis);
    series1->attachAxis(angularAxis);
    series2->attachAxis(radialAxis);
    series2->attachAxis(angularAxis);
    series3->attachAxis(radialAxis);
    series3->attachAxis(angularAxis);

    series2->setVisible(false);
    series3->setOpacity(0.3);
    series3->setColor(Qt::gray);

    radialAxis->setRange(radialMin, radialMax);
    angularAxis->setRange(angularMin, angularMax);

    polarChart->legend()->setVisible(false);

    setChart(polarChart);
    //setRenderHint(QPainter::Antialiasing);
}

void ChartView::updateData(char *p_pack, int size)
{
    for(int count = 0;count < ARRAY_SIZE;count++)
    {
        data[count] = *((int16_t*)(p_pack + count * 2));
    }

    for(int count = 0;count < ARRAY_SIZE - 2;count++)
    {
        if(data[count] == data[count+1] && data[count] == data[count+2])
        {
            data[count] = 0;
            data[count+1] = 0;
            data[count+2] = 0;

            count += 2;
            if(count >= ARRAY_SIZE)
                break;
        }
    }
}

void ChartView::updatePlot()
{
    series1->clear();

    for(int count = 0;count < ARRAY_SIZE;count++)
    {
        if(data[count] == 0)
            continue;

        float angle = (float)count/ARRAY_SIZE * 360;
        angle = (int)(angle + 360 - 145) % 360;
        angle = 360 - angle;

        if(angle < 135 || angle > 225)
            series1->append(angle, (float)data[count]);
    }

    polarChart->update();
}

//![2]
void ChartView::switchChartType()
{
    QChart *newChart;
    QChart *oldChart = chart();

    if (oldChart->chartType() == QChart::ChartTypeCartesian)
        newChart = new QPolarChart();
    else
        newChart = new QChart();

    // Move series and axes from old chart to new one
    const QList<QAbstractSeries *> seriesList = oldChart->series();
    const QList<QAbstractAxis *> axisList = oldChart->axes();
    QList<QPair<qreal, qreal> > axisRanges;

    for (QAbstractAxis *axis : axisList) {
        QValueAxis *valueAxis = static_cast<QValueAxis *>(axis);
        axisRanges.append(QPair<qreal, qreal>(valueAxis->min(), valueAxis->max()));
    }

    for (QAbstractSeries *series : seriesList)
        oldChart->removeSeries(series);

    for (QAbstractAxis *axis : axisList) {
        oldChart->removeAxis(axis);
        newChart->addAxis(axis, axis->alignment());
    }

    for (QAbstractSeries *series : seriesList) {
        newChart->addSeries(series);
        for (QAbstractAxis *axis : axisList)
            series->attachAxis(axis);
    }

    int count = 0;
    for (QAbstractAxis *axis : axisList) {
        axis->setRange(axisRanges[count].first, axisRanges[count].second);
        count++;
    }

    newChart->setTitle(oldChart->title());
    setChart(newChart);
    delete oldChart;
}
//![2]
