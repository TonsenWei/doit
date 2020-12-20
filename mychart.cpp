#include "mychart.h"
#include "QSplitter"
#include "QTextEdit"
#include "QDebug"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "QTextEdit"

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

#include <QtMath>

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


    QVBoxLayout *leftLayout = new QVBoxLayout(this); // 左侧使用垂直布局
    
    QTextEdit * textEdit1 = new QTextEdit(this);
    textEdit1->setText(tr("test1"));
    
    QTextEdit * textEdit2 = new QTextEdit(this);
    textEdit2->setText(tr("test2"));
    
    QTextEdit * textEdit3 = new QTextEdit(this);
    textEdit3->setText(tr("test3"));

    QWidget *widget = new QWidget(this);
    widget->setLayout(leftLayout);
    leftLayout->addWidget(textEdit1);
    leftLayout->addWidget(textEdit2);
    leftLayout->addWidget(textEdit3);


    QVBoxLayout *rightLayout = new QVBoxLayout(this); // 左侧使用垂直布局

    QSplitter *splitterMain;
    QSplitter *splitterRight;
    splitterMain = new QSplitter(Qt::Horizontal,this);  //Horizontal:水平的
    mainLayout->addWidget(splitterMain);
    
    splitterMain->addWidget(widget);

    QChartView *_chart_view = new QChartView(this);
    QLineSeries *seriesFtBugs = new QLineSeries();
    QLineSeries *seriesFtFind = new QLineSeries();
    // k*(1 - (np.e ** (0 - ((1/(2*(tm**2)))*(t**2)))))    k=1000;tm=5
    // k*( ((1/tm)**2) * t * (np.e ** (0 - ((1/(2*(tm**2)))*(t**2)) )) )
    int timeT = 100;
    int kValue = 1000;
    int tmValue = 30;
    for(int i=0; i<timeT; i++) {
        qreal fValue = kValue*(1 -   (qExp(0 - ((1/(2* qPow((float)tmValue, 2))) * qPow((float)i, 2)))));
        seriesFtBugs->append(i, fValue);

        qreal ftFind = kValue*(qPow(1/(float)tmValue, 2) * i * (qExp(0 - ((1/ (2* qPow((float)tmValue, 2))) * qPow((float)i, 2)) )));
        seriesFtFind->append((int)i, ftFind);
    }
    /* 其他属性的设置 */
    _chart_view->chart()->addSeries(seriesFtBugs);
    seriesFtBugs->setName(tr("F(t) data"));                  // x曲线数据的名称

    _chart_view->chart()->addSeries(seriesFtFind);
    seriesFtFind->setName(tr("f(t) data"));                 // 第二条曲线数据的名称

    _chart_view->chart()->setTheme(QChart::ChartThemeDark); // 设置主题
    _chart_view->chart()->setTitle(tr("图表标题"));          // 图表标题
    QValueAxis *axisx = new QValueAxis;
    axisx->setTitleText("time(Day)");                       // x轴刻度标题
    _chart_view->chart()->setAxisX(axisx, seriesFtBugs);
    QValueAxis *axisy = new QValueAxis;
    axisy->setTitleText("Bugs");                            // y轴刻度标题
    _chart_view->chart()->setAxisY(axisy,seriesFtBugs);
    _chart_view->chart()->legend()->setVisible(true);
    _chart_view->chart()->legend()->setAlignment(Qt::AlignBottom);
    _chart_view->chart()->setAnimationOptions(QChart::AllAnimations);//动画

    // mainLayout->addLayout(leftLayout, 0);
    // mainLayout->addWidget(_chart_view); //
    // rightLayout->addWidget(_chart_view);
    splitterMain->addWidget(_chart_view);
    splitterMain->setStretchFactor(1, 4);

    
}
