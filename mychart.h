#ifndef MYCHART_H
#define MYCHART_H

#include <QtWidgets>
#include <QtCharts>
#include <QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

class MyChartWidget : public QWidget
{
    Q_OBJECT

public:
    MyChartWidget(QWidget *parent = nullptr);
    ~MyChartWidget();

public slots:
    void updateChartUi();  // 槽函数

private:
    void initChartUi();

    QComboBox *themeCbox;           // 主题选择框
    QPushButton * btnShowChart;     // 显示曲线按钮
    QChartView *lineChartView;
};

#endif // MYCHART_H
