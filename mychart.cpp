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
#include <QString>

#include "mydialog.h"

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
    this->setContentsMargins(QMargins(0,0,0,0));
    // 头文件中已定义的变量或对象，需要在控件初始化时初始化
    defaultSeriesFtBugs = new QLineSeries(this);
    defaultSeriesFtFind = new QLineSeries(this);
    showDefault = true;
    maxKValueInt = 1000;
    maxTValueInt = 100;
    linesCounter = 0;

    QHBoxLayout *mainLayout = new QHBoxLayout(this); //使用QHBoxLayout布局
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);


    QHBoxLayout *themeCtrlLayout = new QHBoxLayout(this);//横向布局，放主题选择相关控件
    themeCtrlLayout->setSpacing(0);
    // themeCtrlLayout->setMargin(5);//四周的，下面单独设置上下左右的
    themeCtrlLayout->setContentsMargins(0, 5, 0, 5);  // 上边距5，下边距5，左右为0
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
    connect(themeCbox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MyChartWidget::updateChartUi);

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

    QHBoxLayout *linesCtrlLayout = new QHBoxLayout(this);//横向布局，放在主题选择相关控件
    linesCtrlLayout->setSpacing(15);//设置布局内各控件的间隔
    // linesCtrlLayout->setMargin(0);
    linesCtrlLayout->setContentsMargins(0, 0, 0, 5);
    btnShowChart = new QPushButton(this);
    btnShowChart->setContentsMargins(0, 0, 5, 0);
    btnShowChart->setText(tr("显示默认"));
    btnShowChart->setToolTip(tr("显示默认曲线"));
    btnShowChart->setFixedWidth(60);
    connect(btnShowChart, &QPushButton::clicked, [=]() {
        showMyDefaultSeries();
    });

    addChartLinesBtn = new QPushButton(this);
    addChartLinesBtn->setText(tr("增加曲线"));
    addChartLinesBtn->setFixedWidth(60);
    connect(addChartLinesBtn, &QPushButton::clicked, [&]() {
        CLoginDlg dlg;
        int ret = dlg.exec();
        if (ret == 1)
        {
            linesCounter ++;
            int k = dlg.getKvalueStr().toInt();
            int tm = dlg.getTmValueStr().toInt();
            int t = dlg.getTValueStr().toInt();
            if (k > maxKValueInt)
            {
                maxKValueInt = k;
            }
            if (t > maxTValueInt)
            {
                maxTValueInt = t;
            }
            addMySeries(k, tm, t);
            myModel->setItem(linesCounter, 0, new QStandardItem(QString::number(k, 10)));//ret为10进制
            myModel->setItem(linesCounter, 1, new QStandardItem(QString::number(tm, 10)));//ret为10进制
            myModel->setItem(linesCounter, 2, new QStandardItem(QString::number(t, 10)));//ret为10进制
            myModel->setItem(linesCounter, 3, new QStandardItem("已显示"));//ret为10进制
        }
        
        // myModel->setItem(1, 3, new QStandardItem(QString::number(ret, 10)));//ret为10进制
        // myModel->setItem(2, 3, new QStandardItem(dlg.getKvalueStr()));      
        // myModel->setItem(3, 3, new QStandardItem(dlg.getTmValueStr()));     
        // myModel->setItem(4, 3, new QStandardItem(dlg.getTValueStr()));
    });

    clearChartLinesBtn = new QPushButton(this);
    clearChartLinesBtn->setText(tr("清空曲线"));
    clearChartLinesBtn->setFixedWidth(60);
    connect(clearChartLinesBtn, &QPushButton::clicked, [&](){
        linesCounter = 0;
        lineChartView->chart()->removeAllSeries();//删除所有曲线
        int rowCounter = myModel->rowCount();
        for(int i=1; i<rowCounter; i++)
        {
            myModel->setItem(i, 0, new QStandardItem(""));
            myModel->setItem(i, 1, new QStandardItem(""));
            myModel->setItem(i, 2, new QStandardItem(""));
        }
    });

    linesCtrlLayout->addWidget(btnShowChart);
    linesCtrlLayout->addWidget(addChartLinesBtn);
    linesCtrlLayout->addWidget(clearChartLinesBtn);
    linesCtrlLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    // 左侧使用垂直布局,放置控制曲线显示的控件
    QVBoxLayout *leftLayout = new QVBoxLayout(this);
    leftLayout->setSpacing(0);
    leftLayout->setContentsMargins(0,0,0,0);//与外部控件的距离
    QWidget *widget = new QWidget(this);
    widget->setLayout(leftLayout);
    QTableView * tableView = new QTableView(this);
    // leftLayout->addWidget(btnShowChart);
    myModel = new QStandardItemModel(30, 4, this);
    tableView->setModel(myModel);
    myModel->setHeaderData(0, Qt::Horizontal, "K");
    myModel->setHeaderData(1, Qt::Horizontal, "Tm");
    myModel->setHeaderData(2, Qt::Horizontal, "t");
    myModel->setHeaderData(3, Qt::Horizontal, "状态");
    myModel->setItem(0, 0, new QStandardItem("1000"));
    myModel->setItem(0, 1, new QStandardItem("5"));
    myModel->setItem(0, 2, new QStandardItem("100"));
    myModel->setItem(0, 3, new QStandardItem("已隐藏"));
    /* 设置列宽在可视界面自适应宽度 */
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    /* 行颜色交替显示 */
    tableView->setAlternatingRowColors(true);
    /* 不允许在图形界面修改内容 */
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 左侧添加
    leftLayout->addLayout(themeCtrlLayout);
    leftLayout->addLayout(linesCtrlLayout);
    leftLayout->addWidget(tableView);

    

    QSplitter *splitterMain;
    splitterMain = new QSplitter(Qt::Horizontal, this);  //Horizontal:水平的
    mainLayout->addWidget(splitterMain);
    
    splitterMain->addWidget(widget);
    splitterMain->setHandleWidth(0);

    lineChartView = new QChartView(this);
    QLineSeries *seriesFtBugs = new QLineSeries(this);
    QLineSeries *seriesFtFind = new QLineSeries(this);

    /* 其他属性的设置 */
    lineChartView->chart()->addSeries(seriesFtBugs);
    seriesFtBugs->setName(tr("F(t) data"));                     // x曲线数据的名称
    seriesFtBugs->hide();  // 隐藏该series

    lineChartView->chart()->addSeries(seriesFtFind);
    seriesFtFind->setName(tr("f(t) data"));                     // 第二条曲线数据的名称
    seriesFtFind->hide();  // 隐藏该series

    lineChartView->chart()->setTheme(QChart::ChartThemeLight);  // 设置主题
    lineChartView->chart()->setTitle(tr("图表标题"));            // 图表标题
    QValueAxis *axisx = new QValueAxis;
    axisx->setTitleText("time(Day)");                       // x轴刻度标题
    axisx->setLabelFormat("%d");                            // 设置刻度的格式，也就是刻度值为整数
    QValueAxis *axisFtFind = new QValueAxis;
    axisFtFind->setTitleText("Bugs");                       // y轴刻度标题
    axisFtFind->setLabelFormat("%d");                       // 设置刻度的格式，也就是刻度值为整数
    
    lineChartView->chart()->legend()->setVisible(true);
    lineChartView->chart()->legend()->setAlignment(Qt::AlignBottom);
    lineChartView->chart()->setAnimationOptions(QChart::AllAnimations);//动画

    splitterMain->addWidget(lineChartView);
    
    // lineChartView->layout()->setContentsMargins(0, 0, 0, 0);//设置QChartView的外边界为0，报错，待分析.使用下面的设置可行
    lineChartView->chart()->layout()->setContentsMargins(0, 0, 0, 0);//设置QChartView中chart的外边界为0
    lineChartView->chart()->setMargins(QMargins(0, 0, 0, 0));  // 设置QChart的内边界
    splitterMain->setStretchFactor(1, 4);
    // splitterMain->setContentsMargins(0, 0, 0, 0);
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

void MyChartWidget::addMySeries(int kValue, int tmValue, int timeT)
{
    QLineSeries *seriesFtBugs = new QLineSeries(this);
    QLineSeries *seriesFtFind = new QLineSeries(this);
    // k*(1 - (np.e ** (0 - ((1/(2*(tm**2)))*(t**2)))))    k=1000;tm=5
    // k*( ((1/tm)**2) * t * (np.e ** (0 - ((1/(2*(tm**2)))*(t**2)) )) )

    for(int i=0; i<timeT + 1; i++) {
        qreal fValue = kValue*(1 -   (qExp(0 - ((1/(2* qPow((float)tmValue, 2))) * qPow((float)i, 2)))));
        seriesFtBugs->append(i, fValue);

        qreal ftFind = kValue*(qPow(1/(float)tmValue, 2) * i * ((float)qExp(0 - ((1/ (2* qPow(tmValue, 2))) * qPow(i, 2)) )));
        seriesFtFind->append((int)i, float(ftFind));
    }
    
    /* 其他属性的设置 */
    lineChartView->chart()->addSeries(seriesFtBugs);
    QString str = "F_";
    str.append(QString::number(linesCounter, 10)).append("(t) data");
    seriesFtBugs->setName(str);                     // x曲线数据的名称

    lineChartView->chart()->addSeries(seriesFtFind);
    QString strf = "f_";
    str.append(QString::number(linesCounter, 10)).append("(t) data");
    seriesFtFind->setName(str);                     // 第二条曲线数据的名称

    lineChartView->chart()->createDefaultAxes();
    lineChartView->chart()->axes(Qt::Horizontal).first()->setRange(0, maxTValueInt);
    lineChartView->chart()->axes(Qt::Vertical).first()->setRange(0, maxKValueInt);
}


void MyChartWidget::showMyDefaultSeries()
{
    if (showDefault)
    {
        showDefault = false;
        bool isContains = lineChartView->chart()->series().contains(defaultSeriesFtBugs);
        if(isContains == true) {
            defaultSeriesFtBugs->show();
            defaultSeriesFtFind->show();
        } else {
            defaultSeriesFtBugs = new QLineSeries(this);
            defaultSeriesFtFind = new QLineSeries(this);
            int timeT = 100;
            int kValue = 1000;
            int tmValue = 5;

            for(int i=0; i<timeT + 1; i++) {
                qreal fValue = kValue*(1 -   (qExp(0 - ((1/(2* qPow((float)tmValue, 2))) * qPow((float)i, 2)))));
                defaultSeriesFtBugs->append(i, fValue);

                qreal ftFind = kValue*(qPow(1/(float)tmValue, 2) * i * ((float)qExp(0 - ((1/ (2* qPow(tmValue, 2))) * qPow(i, 2)) )));
                defaultSeriesFtFind->append((int)i, float(ftFind));
            }
            lineChartView->chart()->addSeries(defaultSeriesFtBugs);
            defaultSeriesFtBugs->setName(tr("F_0(t) data"));                     // x曲线数据的名称
            lineChartView->chart()->addSeries(defaultSeriesFtFind);
            defaultSeriesFtFind->setName(tr("f_0(t) data"));                     // 第二条曲线数据的名称
            lineChartView->chart()->createDefaultAxes();
            lineChartView->chart()->axes(Qt::Horizontal).first()->setRange(0, maxTValueInt);
            lineChartView->chart()->axes(Qt::Vertical).first()->setRange(0, maxKValueInt);
            defaultSeriesFtBugs->show();
            defaultSeriesFtFind->show();
        }
        btnShowChart->setText(tr("隐藏默认"));
        myModel->setItem(0, 3, new QStandardItem("已显示"));
    } else
    {
        showDefault = true;
        bool isContains = lineChartView->chart()->series().contains(defaultSeriesFtBugs);
        if(isContains == true) {  // 已存在，则只操作隐藏
            defaultSeriesFtBugs->hide();
            defaultSeriesFtFind->hide();
        } else {  // 不存在，则添加后隐藏
            defaultSeriesFtBugs = new QLineSeries(this);
            defaultSeriesFtFind = new QLineSeries(this);
            int timeT = 100;
            int kValue = 1000;
            int tmValue = 5;

            for(int i=0; i<timeT + 1; i++) {
                qreal fValue = kValue*(1 -   (qExp(0 - ((1/(2* qPow((float)tmValue, 2))) * qPow((float)i, 2)))));
                defaultSeriesFtBugs->append(i, fValue);

                qreal ftFind = kValue*(qPow(1/(float)tmValue, 2) * i * ((float)qExp(0 - ((1/ (2* qPow(tmValue, 2))) * qPow(i, 2)) )));
                defaultSeriesFtFind->append((int)i, float(ftFind));
            }
            lineChartView->chart()->addSeries(defaultSeriesFtBugs);
            defaultSeriesFtBugs->setName(tr("F_0(t) data"));                     // x曲线数据的名称
            lineChartView->chart()->addSeries(defaultSeriesFtFind);
            defaultSeriesFtFind->setName(tr("f_0(t) data"));                     // 第二条曲线数据的名称
            lineChartView->chart()->createDefaultAxes();
            lineChartView->chart()->axes(Qt::Horizontal).first()->setRange(0, maxTValueInt);
            lineChartView->chart()->axes(Qt::Vertical).first()->setRange(0, maxKValueInt);

            defaultSeriesFtBugs->hide();
            defaultSeriesFtFind->hide();
        }
        btnShowChart->setText(tr("显示默认"));
        myModel->setItem(0, 3, new QStandardItem("已隐藏"));
    }
}
