#include "adbwidget.h"
#include "QSplitter"
#include "QTextEdit"
#include "QDebug"
#include "QHBoxLayout"
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QByteArray>
#include <QDateTime>
#include <QProcess>

AdbWidget::AdbWidget(QWidget *parent)
    : QWidget(parent)
{
    // serial = new QSerialPort;
    initAdbUi();
}

/**
 * 析构函数
*/
AdbWidget::~AdbWidget()
{
}

void AdbWidget::initAdbUi()
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);            // 使用QHBoxLayout布局
    QSplitter *splitMain = new QSplitter(Qt::Horizontal, this); // Qt::Horizontal设置为水平分割，0代表为主窗口，无父窗口

    QVBoxLayout *leftLayout = new QVBoxLayout(this); //左侧垂直布局
    leftLayout->setSpacing(0);
    leftLayout->setContentsMargins(0, 0, 0, 0); //与外部控件的距离
    QWidget *widget = new QWidget(this);
    widget->setLayout(leftLayout);
    QGroupBox *gboxComConf = new QGroupBox(tr("ADB设置"), this); //左侧布局放置组容器，用于配置串口波特率等信息
    // 组容器内，使用gridlayout布局
    QGridLayout *glayoutComConf = new QGridLayout(this);
    gboxComConf->setLayout(glayoutComConf);
    // QTextEdit *textLeft = new QTextEdit(QObject::tr("Left"), this);  //为splitMain窗口添加控件
    // textLeft->setAlignment(Qt::AlignCenter);
    QLabel *comIndexLbl = new QLabel(this);
    comIndexLbl->setText(tr("设备："));
    comIndexLbl->setFixedWidth(40);
    comIndexCbox = new QComboBox(this);
    comIndexCbox->setFixedWidth(100);
    comIndexCbox->setEditable(true); // 可编辑，在列出的端口中没有需要的端口可手动输入
    QStringList comList;
    for (int i = 1; i <= 20; i++)
    {
        comList << QString("COM%1").arg(i);
    }
    comIndexCbox->addItems(comList);

    QLabel *baudrateLbl = new QLabel(this);
    baudrateLbl->setText(tr("进程："));
    baudrateLbl->setFixedWidth(40);
    baudrateCbox = new QComboBox(this);
    baudrateCbox->setFixedWidth(100);
    QStringList baudList;
    baudList << "50"
             << "75"
             << "100";
    baudrateCbox->addItems(baudList);
    baudrateCbox->setCurrentIndex(19);

    startComBtn = new QPushButton(this);
    startComBtn->setText(tr("打开"));
    // connect(startComBtn, &QPushButton::clicked, [=]() {
    //     QProcess process;
    //     process.start("adb --help");
    //     bool ret = process.waitForStarted();
    // });execProcessAndReadByLine
    // connect(startComBtn, &QPushButton::clicked, this, &MySerialWidget::on_btn_openConsole_clicked);
    connect(startComBtn, &QPushButton::clicked, this, &AdbWidget::execProcessAndReadByLine);

    glayoutComConf->addWidget(comIndexLbl, 0, 0);
    glayoutComConf->addWidget(comIndexCbox, 0, 1);
    glayoutComConf->addWidget(baudrateLbl, 1, 0);
    glayoutComConf->addWidget(baudrateCbox, 1, 1);
    glayoutComConf->addWidget(startComBtn, 5, 0, 5, 2);  //startComBtn控件放在第五行第0列，第五行跨两个单元格

    QHBoxLayout *comConfLayout = new QHBoxLayout(this);
    comConfLayout->addWidget(gboxComConf);
    comConfLayout->addSpacerItem(new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    // leftLayout->addWidget(gboxComConf);
    leftLayout->addLayout(comConfLayout);
    leftLayout->setContentsMargins(0, 0, 5, 0);
    leftLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding)); //Expanding
    splitMain->addWidget(widget);

    // textLeft->setStyleSheet("QTextEdit{border-radius:5px;}");

    QSplitter *splitterRight = new QSplitter(Qt::Vertical, splitMain); // Qt::Vertical设置为竖直分割，splitMain代表为父窗口
    splitterRight->setOpaqueResize(false);                             // 为splitterRight设置拖动时是否实时更新，false拖动时只有一个线条

    QTabWidget *tabComTabw = new QTabWidget(splitterRight);
    textUp = new QTextEdit(this); //为splitterRight窗口添加控件
    tabComTabw->addTab(textUp, tr("未过滤"));
    // textUp->setAlignment(Qt::AlignCenter);
    textUp->setAlignment(Qt::AlignLeft);
    textUp->setLineWrapMode(QTextEdit::NoWrap);

    QComboBox *inputCmdCbox = new QComboBox(this);
    inputCmdCbox->setFixedHeight(20);
    inputCmdCbox->setEditable(true);
    splitterRight->addWidget(inputCmdCbox);

    // textBottom = new QTextEdit(QObject::tr("Bottom"), splitterRight);
    // textBottom->setAlignment(Qt::AlignCenter);

    splitMain->setStretchFactor(1, 1); //设置可伸缩控件，第一个参数为控件序号，第二个参数0代表可伸缩，放大整个窗口大小可以发现左边小窗口大小不变

    splitMain->setFrameStyle(QFrame::NoFrame);
    splitMain->setHandleWidth(0);      // 设置分界线的宽度
    splitterRight->setFrameStyle(QFrame::NoFrame);
    splitterRight->setHandleWidth(0);  // 设置分界线的宽度
    mainLayout->addWidget(splitMain);
    mainLayout->setMargin(5);  // 跟外部窗口间隔为0,如果设置，默认为10
    mainLayout->setSpacing(0); //设置layout中各部件的相邻距离，如果不设置，这个距离默认是10
}


void AdbWidget::execProcessAndReadByLine()
{
    QProcess process;
    process.start("adb --help");
    bool ret = process.waitForStarted();
    qint64 maxSize = 512;
    char buffer[maxSize];
    qint64 len;
    while(true) {
        /*
         * 一个waitForReadyRead信号可能输出的是多行
         */
        ret = process.waitForReadyRead();
        textUp->append("waitForReadyRead");
        qDebug()<<"waitForReadyRead"<<ret;
        if(!ret) {
            break;
        }
        while(true) {
            len = process.readLine(buffer, maxSize);
            textUp->append("buffer len");
            textUp->append(QString::number(len));
            // qDebug()<<"buffer len"<<len;
            /*
             * 因为每一行至少还有回车换行符，因此读到0，说明waitForReadyRead超时返回false
             */
            if(len <= 0) {
                break;
            }
            QString str = QString::fromLocal8Bit(buffer);
            textUp->append(str);
            // qDebug()<<"qstring len"<<str.length();
            // qDebug()<<str;
            // qDebug()<<"";
        }
    }
}