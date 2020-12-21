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
#include <QComboBox> 
#include <QLabel> 

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

    // 左侧使用垂直布局,放置控制曲线显示的控件
    QVBoxLayout *leftLayout = new QVBoxLayout(this);

    QHBoxLayout *themeCtrlLayout = new QHBoxLayout(this);
    QLabel *lblTheme = new QLabel(this);
    lblTheme->setText(tr("图表主题:"));
    lblTheme->setFixedSize(55, 20);//固定大小，宽40，高20

    themeCbox  = new QComboBox(this);
    themeCbox->addItem(tr("浅色"), QChart::ChartThemeLight);
    themeCbox->addItem(tr("天蓝色"), QChart::ChartThemeBlueCerulean);
    themeCbox->addItem(tr("暗色"), QChart::ChartThemeDark);
    themeCbox->addItem(tr("棕砂"), QChart::ChartThemeBrownSand);
    themeCbox->addItem(tr("NCS蓝"), QChart::ChartThemeBlueNcs);
    themeCbox->addItem(tr("高对比度"), QChart::ChartThemeHighContrast);
    themeCbox->addItem(tr("蓝色常春藤"), QChart::ChartThemeBlueIcy);
    themeCbox->addItem(tr("Qt"), QChart::ChartThemeQt);
    
    themeCbox->setFixedSize(80, 20);

    themeCtrlLayout->addWidget(lblTheme);
    themeCtrlLayout->addWidget(themeCbox);
    /**
     * 构造了两个宽40px、高20px的空白区：
     * QSizePolicy::Minimum：空白区不能小于该面积量，但可以在有效空间内放大。
     * QSizePolicy::Expanding：空白区会随窗口的放大缩小而放大缩小。
     * 第一个参数：构造空白区域的宽
     * 第二个参数：构造空白区域的高
     * 第三个参数：宽度适应策略，Expanding为宽度随着窗口的缩放而缩放
     * 第四个参数：高度适应策略，Minimum高度不能小于该面积了
    */
    QSpacerItem * spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    themeCtrlLayout->addSpacerItem(spacerItem);
    

    btnShowChart = new QPushButton(this);
    btnShowChart->setText(tr("显示曲线"));
    

    QTextEdit * textEdit1 = new QTextEdit(this);
    textEdit1->setText(tr("test1"));
    
    connect(themeCbox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MyChartWidget::updateChartUi);
    connect(btnShowChart, &QPushButton::clicked, [=]() {
        textEdit1->setText(tr("btnShowChart clicked"));
    });
    // QTextEdit * textEdit2 = new QTextEdit(this);
    // textEdit2->setText(tr("test2"));
    
    // QTextEdit * textEdit3 = new QTextEdit(this);
    // textEdit3->setText(tr("test3"));

    QWidget *widget = new QWidget(this);
    widget->setLayout(leftLayout);
    leftLayout->addLayout(themeCtrlLayout);
    leftLayout->addWidget(btnShowChart);
    leftLayout->addWidget(textEdit1);
    // leftLayout->addWidget(textEdit2);
    // leftLayout->addWidget(textEdit3);


    QVBoxLayout *rightLayout = new QVBoxLayout(this); // 左侧使用垂直布局

    QSplitter *splitterMain;
    QSplitter *splitterRight;
    splitterMain = new QSplitter(Qt::Horizontal,this);  //Horizontal:水平的
    mainLayout->addWidget(splitterMain);
    
    splitterMain->addWidget(widget);

    lineChartView = new QChartView(this);
    QLineSeries *seriesFtBugs = new QLineSeries();
    QLineSeries *seriesFtFind = new QLineSeries();
    // k*(1 - (np.e ** (0 - ((1/(2*(tm**2)))*(t**2)))))    k=1000;tm=5
    // k*( ((1/tm)**2) * t * (np.e ** (0 - ((1/(2*(tm**2)))*(t**2)) )) )
    int timeT = 100;
    int kValue = 1000;
    int tmValue = 5;

    for(int i=0; i<timeT + 1; i++) {
        qreal fValue = kValue*(1 -   (qExp(0 - ((1/(2* qPow((float)tmValue, 2))) * qPow((float)i, 2)))));
        seriesFtBugs->append(i, fValue);

        qreal ftFind = kValue*(qPow(1/(float)tmValue, 2) * i * ((float)qExp(0 - ((1/ (2* qPow(tmValue, 2))) * qPow(i, 2)) )));
        seriesFtFind->append((int)i, float(ftFind));
    }
    /* 其他属性的设置 */
    // chart->createDefaultAxes();
    // chart->axes(Qt::Horizontal).first()->setRange(0, m_valueMax);
    // chart->axes(Qt::Vertical).first()->setRange(0, m_valueCount);
    lineChartView->chart()->addSeries(seriesFtBugs);
    seriesFtBugs->setName(tr("F(t) data"));                     // x曲线数据的名称

    lineChartView->chart()->addSeries(seriesFtFind);
    seriesFtFind->setName(tr("f(t) data"));                     // 第二条曲线数据的名称

    // 设置x轴和y轴值的范围
    // lineChartView->chart()->setAxisX(axisx, seriesFtBugs);     //已过时
    // lineChartView->chart()->setAxisY(axisFtFind,seriesFtBugs); //已过时
    lineChartView->chart()->createDefaultAxes();
    lineChartView->chart()->axes(Qt::Horizontal).first()->setRange(0, 100);
    lineChartView->chart()->axes(Qt::Vertical).first()->setRange(0, 1000);

    // lineChartView->chart()->setTheme(QChart::ChartThemeDark); // 设置主题
    lineChartView->chart()->setTitle(tr("图表标题"));          // 图表标题
    QValueAxis *axisx = new QValueAxis;
    axisx->setTitleText("time(Day)");                       // x轴刻度标题
    axisx->setLabelFormat("%d");                            // 设置刻度的格式，也就是刻度值为整数
    QValueAxis *axisFtFind = new QValueAxis;
    axisFtFind->setTitleText("Bugs");                       // y轴刻度标题
    axisFtFind->setLabelFormat("%d");                       // 设置刻度的格式，也就是刻度值为整数
    
    lineChartView->chart()->legend()->setVisible(true);
    lineChartView->chart()->legend()->setAlignment(Qt::AlignBottom);
    lineChartView->chart()->setAnimationOptions(QChart::AllAnimations);//动画

    // mainLayout->addLayout(leftLayout, 0);
    // mainLayout->addWidget(lineChartView); //
    // rightLayout->addWidget(lineChartView);
    splitterMain->addWidget(lineChartView);
    splitterMain->setStretchFactor(1, 4);

    
}

void MyChartWidget::updateChartUi()
{
    //![6]
    QChart::ChartTheme theme = static_cast<QChart::ChartTheme>(
    themeCbox->itemData(themeCbox->currentIndex()).toInt());
    //![6]
    if (lineChartView->chart()->theme() != theme) {
        lineChartView->chart()->setTheme(theme);

        // Set palette colors based on selected theme
        // 根据选择的主题设置面板的颜色
        // ![8]
        // QPalette pal = window()->palette();
        // if (theme == QChart::ChartThemeLight) {
        //     pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
        //     pal.setColor(QPalette::WindowText, QRgb(0x404044));
        // //![8]
        // } else if (theme == QChart::ChartThemeDark) {
        //     pal.setColor(QPalette::Window, QRgb(0x121218));
        //     pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        // } else if (theme == QChart::ChartThemeBlueCerulean) {
        //     pal.setColor(QPalette::Window, QRgb(0x40434a));
        //     pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        // } else if (theme == QChart::ChartThemeBrownSand) {
        //     pal.setColor(QPalette::Window, QRgb(0x9e8965));
        //     pal.setColor(QPalette::WindowText, QRgb(0x404044));
        // } else if (theme == QChart::ChartThemeBlueNcs) {
        //     pal.setColor(QPalette::Window, QRgb(0x018bba));
        //     pal.setColor(QPalette::WindowText, QRgb(0x404044));
        // } else if (theme == QChart::ChartThemeHighContrast) {
        //     pal.setColor(QPalette::Window, QRgb(0xffab03));
        //     pal.setColor(QPalette::WindowText, QRgb(0x181818));
        // } else if (theme == QChart::ChartThemeBlueIcy) {
        //     pal.setColor(QPalette::Window, QRgb(0xcee7f0));
        //     pal.setColor(QPalette::WindowText, QRgb(0x404044));
        // } else {
        //     pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
        //     pal.setColor(QPalette::WindowText, QRgb(0x404044));
        // }
        // window()->setPalette(pal);
    }
}