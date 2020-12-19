#include "mychart.h"
#include "QSplitter"
#include "QTextEdit"
#include "QDebug"
#include "QHBoxLayout"

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

MyChartWidget::MyChartWidget(QWidget *parent)
    : QWidget(parent)
{
    initChartUi();
}

/**
 * 析构函数
*/
MyChartWidget::~MyChartWidget()
{
}

void MyChartWidget::initChartUi()
{

    QHBoxLayout *mainLayout = new QHBoxLayout(this); //使用QHBoxLayout布局
    QChartView *_chart_view = new QChartView(this);
    QLineSeries *seriesx = new QLineSeries();
    for(int i=0; i<10; ++i) {
        seriesx->append(i, i * 1.0);
    }
    /* 其他属性的设置 */
    _chart_view->chart()->addSeries(seriesx);
    _chart_view->chart()->setTheme(QChart::ChartThemeDark);//设置主题
    _chart_view->chart()->setTitle(tr("图表标题"));        // 图表标题
    seriesx->setName(tr("数据名称"));                      // x曲线数据的名称
    QValueAxis *axisx = new QValueAxis;
    axisx->setTitleText("sample time(s)");                // x轴刻度标题
    _chart_view->chart()->setAxisX(axisx, seriesx);
    QValueAxis *axisy = new QValueAxis;
    axisy->setTitleText("height(meter)");                 // y轴刻度标题
    _chart_view->chart()->setAxisY(axisy,seriesx);
    _chart_view->chart()->legend()->setVisible(true);
    _chart_view->chart()->legend()->setAlignment(Qt::AlignBottom);
    mainLayout->addWidget(_chart_view);
    _chart_view->chart()->setAnimationOptions(QChart::AllAnimations);//动画
}