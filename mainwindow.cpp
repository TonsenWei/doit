#include "mainwindow.h"
#include <QTextEdit>
#include <QDockWidget>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QGuiApplication>
#include <QScreen>
#include <QList>
#include <QRect>
#include <QLabel>
#include <QSplitter>
#include <QTabWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QIcon>
#include <QToolBar>

#include "myserialwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //设置主窗口的标题栏文字,如果不设置，默认使用工程名doit当窗口名
    setWindowTitle(tr("Doit by Tonsen"));
    initWindow();       // 初始化窗口位置和大小
    createMenuBar();    // 初始化菜单栏
    createToolBar();
    createStatusBar();  // 初始化状态栏
    // createMainContents();   // 初始化主窗口内容
    // createQDockWidgets();   // QDock窗口
    createQTabWidget();
}

/**
 * 析构函数
*/
MainWindow::~MainWindow()
{
}

/**
 * 初始化程序主窗口的位置和大小
 * 位置根据显示器大小和窗口大小计算放在屏幕正中间
*/
void MainWindow::initWindow()
{
    // 窗口位置和大小
    int winWidth = 1024;
    int winHeight = 768;
    resize(winWidth, winHeight);
    QList<QScreen *> list_screen = QGuiApplication::screens(); //多显示器
    QRect rect = list_screen.at(0)->geometry();
    int desktop_width = rect.width();
    int desktop_height = rect.height();
    move(desktop_width / 2 - winWidth / 2, desktop_height / 2 - winHeight / 2);
}

/**
 * 创建主要内容窗口
*/
void MainWindow::createMainContents() 
{
   // QSplitter使用
    QSplitter *splitterMain;
    QTextEdit *textleft;
    QSplitter *splitterRight;
    QTextEdit *textUp;
    QTextEdit *textBottom;
    splitterMain=new QSplitter(Qt::Horizontal,this);  //Horizontal:水平的
    textleft=new QTextEdit(QObject::tr("Left Widget"),splitterMain);
    textleft->setAlignment(Qt::AlignCenter);
    //右部分分割窗口
    splitterRight=new QSplitter(Qt::Vertical,splitterMain);//Vertical：垂直的
    splitterRight->setOpaqueResize(false); //Opaque：不透明的
    textUp =new QTextEdit(QObject::tr("Top Widget"),splitterRight);
    textUp->setAlignment(Qt::AlignCenter);
    textBottom=new QTextEdit(QObject::tr("Bottom Widget"),splitterRight);
    textBottom->setAlignment(Qt::AlignCenter);
    // splitterMain->setStretchFactor(0,1); //Stretch Factor:拉伸系数
    // splitterMain->setWindowTitle(QObject::tr("Splitter"));
    // splitterMain->show();
    setCentralWidget(splitterMain); 

    // QTextEdit
    // QTextEdit *te = new QTextEdit(this); // 定义一个QTextEdit对象作为主窗口
    // te->setText(tr("Main Window"));      // 窗口内显示文字
    // te->setAlignment(Qt::AlignCenter);   // 主要将是消除布局中的空隙，让两个控件紧紧挨在一起
    // setCentralWidget(te);                // 将此编辑框作为主窗体的中央窗体

}

void MainWindow::createQTabWidget()
{
    QTabWidget *tabWidget = new QTabWidget(this);

    MySerialWidget *myserialwidget = new MySerialWidget(this);
    QLabel *fileNameLabel = new QLabel(tr("File Name:"));
    tabWidget->addTab(myserialwidget, tr("General"));
    tabWidget->addTab(fileNameLabel, tr("test1"));
    // tabWidget->addTab(new PermissionsTab(fileInfo), tr("Permissions"));
    // tabWidget->addTab(new ApplicationsTab(fileInfo), tr("Applications"));
    setCentralWidget(tabWidget); 
    
    tabWidget->setTabIcon(0, newIcon);//要先addTab之后才能setIcon
    tabWidget->setTabsClosable(true); // 设置为可关闭
    // QVBoxLayout *mainLayout = new QVBoxLayout;
    // mainLayout->addWidget(tabWidget);
    // this->setLayout(mainLayout);
}

/**
 * 创建停靠窗口
*/
void MainWindow::createQDockWidgets()
{
    // 停靠窗口1
    QDockWidget *dock1 = new QDockWidget(tr("DockWindow1"), this);
    QDockWidget *dock2 = new QDockWidget(tr("DockWindow2"), this);
    QDockWidget *dock3 = new QDockWidget(tr("DockWindow3"), this);
    
    dock1->setFeatures(QDockWidget::DockWidgetMovable);  // 可移动
    dock1->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock1->setStyleSheet("border:none");  // 无边框

    QTextEdit *te1 = new QTextEdit();
    te1->setText(tr("Window1,The dock widget can be moved between dicks by user"));
    dock1->setWidget(te1);                         // 停靠窗口1内的Text控件
    te1->setAlignment(Qt::AlignCenter);            // 主要将是消除布局中的空隙，让两个控件紧紧挨在一起
    addDockWidget(Qt::RightDockWidgetArea, dock1); // dock1添加到主窗口

    // 停靠窗口2，可关闭，可浮动
    dock2->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetFloatable);
    QTextEdit *te2 = new QTextEdit();
    te2->setText(tr("Window2,The dock widget can be detached from the main window, and floated as an independent window,and can be closed"));
    dock2->setWidget(te2);
    te2->setAlignment(Qt::AlignCenter);     // 主要将是消除布局中的空隙，让两个控件紧紧挨在一起
    dock2->setStyleSheet("border:none");    // 无边框
    addDockWidget(Qt::RightDockWidgetArea, dock2);

    //停靠窗口3
    //dock3=new QDockWidget(tr("DockWindow3"),this);
    dock3->setFeatures(QDockWidget::AllDockWidgetFeatures);
    QTextEdit *te3 = new QTextEdit();
    te3->setText(tr("Window3,The dock widget can be closed,moved,add floated"));
    dock3->setWidget(te3);
    te3->setAlignment(Qt::AlignCenter);     // 主要将是消除布局中的空隙，让两个控件紧紧挨在一起
    dock3->setStyleSheet("border:none");    // 无边框
    addDockWidget(Qt::RightDockWidgetArea, dock3);
}

/**
 * 创建菜单栏和工具栏
 * */ 
void MainWindow::createMenuBar()
{
    QMenuBar *menuBar = new QMenuBar(this);
    // 将菜单栏添加到主窗口
    this->setMenuBar(menuBar);
    QMenu *fileMenu = menuBar->addMenu(tr("文件"));
    // 定义菜单项
    QAction *newItem = new QAction(tr("新建"), this);
    QAction *saveItem = new QAction(tr("保存"), this);
    // const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
    // QAction *newLetterAct = new QAction(newIcon, tr("&New Letter"), this);//增加图标
    newItem->setIcon(newIcon);
    // const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/images/save.png"));
    saveItem->setIcon(saveIcon);

    //将菜单项加入菜单
    fileMenu->addAction(newItem);
    fileMenu->addAction(saveItem);

    //设置快捷键
    newItem->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_N));
    //插入一个华丽的分割线
    fileMenu->addSeparator();

    QAction *exitAct = new QAction(tr("退出"), this);
    exitAct->setStatusTip(tr("退出主程序"));  // 鼠标移到退出选项时会在状态栏提示
    //信号和槽连接
    connect(exitAct, &QAction::triggered, this, &MainWindow::close);//退出
    fileMenu->addAction(exitAct);

    
    QMenu *editMenu = menuBar->addMenu(tr("编辑"));
    editMenu->addAction(tr("开始编辑"));
}

void MainWindow::createToolBar(){
    QToolBar *toolBar = new QToolBar(this);
    this->addToolBar(toolBar);//可以拖动到上面，左边右边或悬浮

    // 将菜单项放到工具栏中
    QAction *newItem = new QAction(tr("新建"), this);
    QAction *saveItem = new QAction(tr("保存"), this);
    // const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
    // QAction *newLetterAct = new QAction(newIcon, tr("&New Letter"), this);//增加图标
    newItem->setIcon(newIcon);
    saveItem->setIcon(saveIcon);
    toolBar->addAction(newItem);
    toolBar->addSeparator();
    toolBar->addAction(saveItem);
    // 设置不允许浮动
    toolBar->setFloatable(false);
    // 设置工具栏允许的位置
    toolBar->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea | Qt::TopToolBarArea);
}

/**
 * 状态栏
 * */ 
void MainWindow::createStatusBar()
{
    QLabel *locationLabel;
    locationLabel = new QLabel(tr("July"));
    locationLabel->setAlignment(Qt::AlignCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    QLabel *aixLabel;
    aixLabel = new QLabel(tr("\"CTRL + H\" for help"));

    statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}")); // 设置不显示label的边框
    statusBar()->setSizeGripEnabled(false); //设置是否显示右边的大小控制点
    statusBar()->addWidget(locationLabel);
    statusBar()->addWidget(aixLabel, 1);

    QLabel *per1 = new QLabel(tr("Ready1"), this);
    QLabel *per2 = new QLabel(tr("Ready2"), this);
    QLabel *per3 = new QLabel(tr("Ready3"), this);
    statusBar()->addPermanentWidget(per1); //显示永久信息
    statusBar()->addPermanentWidget(per2); //显示永久信息
    statusBar()->insertPermanentWidget(2, per3);//显示永久信息，在第二个插入

    statusBar()->showMessage(tr("Status is here..."), 3000); // 显示临时信息，时间3秒钟.
    // statusBar()->showMessage(tr("Ready"));
}
