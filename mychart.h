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
    void addMySeries(int kValue, int tmValue, int timeT);
    void showMyDefaultSeries();

    QComboBox *themeCbox;               // 主题选择框
    QPushButton * btnShowChart;         // 显示曲线按钮
    QPushButton * addChartLinesBtn;     // 增加曲线按钮
    QPushButton * clearChartLinesBtn;   // 删除所有曲线按钮
    QChartView *lineChartView;
    QStandardItemModel *myModel;
    QLineSeries *defaultSeriesFtBugs;
    QLineSeries *defaultSeriesFtFind;
    bool showDefault;//是否已显示默认曲线
    int maxKValueInt;//最大K值
    int maxTValueInt;//最大T值
    int linesCounter;//多少对折线
};

#endif // MYCHART_H
