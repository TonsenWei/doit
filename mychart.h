#ifndef MYCHART_H
#define MYCHART_H

#include <QWidget>
#include <QtCharts>
#include <QComboBox>
#include <QPushButton>

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
    void addMySeries();
    void showMyDefaultSeries();

    QComboBox *themeCbox;           // 主题选择框
    QPushButton * btnShowChart;     // 显示曲线按钮
    QPushButton * addChartLinesBtn;     // 增加曲线按钮
    QChartView *lineChartView;
    QStandardItemModel *myModel;
    QLineSeries *defaultSeriesFtBugs;
    QLineSeries *defaultSeriesFtFind;
    bool showDefault;
};

#endif // MYCHART_H
