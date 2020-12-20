#ifndef MYCHART_H
#define MYCHART_H

#include <QtWidgets>
#include <QtCharts/QChartView>

class MyChartWidget : public QWidget
{
    Q_OBJECT

public:
    MyChartWidget(QWidget *parent = nullptr);
    ~MyChartWidget();

private:
    void initChartUi();

    int m_listCount;
    int m_valueMax;
    int m_valueCount;

};

#endif // MYCHART_H
