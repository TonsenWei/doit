#include "myserialwidget.h"
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

MySerialWidget::MySerialWidget(QWidget *parent)
    : QWidget(parent)
{
    serial = new QSerialPort;
    initSerialUi();
}

/**
 * 析构函数
*/
MySerialWidget::~MySerialWidget()
{
}

void MySerialWidget::initSerialUi()
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);            // 使用QHBoxLayout布局
    QSplitter *splitMain = new QSplitter(Qt::Horizontal, this); // Qt::Horizontal设置为水平分割，0代表为主窗口，无父窗口

    QVBoxLayout *leftLayout = new QVBoxLayout(this); //左侧垂直布局
    leftLayout->setSpacing(0);
    leftLayout->setContentsMargins(0, 0, 0, 0); //与外部控件的距离
    QWidget *widget = new QWidget(this);
    widget->setLayout(leftLayout);
    QGroupBox *gboxComConf = new QGroupBox(tr("串口设置"), this); //左侧布局放置组容器，用于配置串口波特率等信息
    // 组容器内，使用gridlayout布局
    QGridLayout *glayoutComConf = new QGridLayout(this);
    gboxComConf->setLayout(glayoutComConf);
    // QTextEdit *textLeft = new QTextEdit(QObject::tr("Left"), this);  //为splitMain窗口添加控件
    // textLeft->setAlignment(Qt::AlignCenter);
    QLabel *comIndexLbl = new QLabel(this);
    comIndexLbl->setText(tr("端口号："));
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
    baudrateLbl->setText(tr("波特率："));
    baudrateLbl->setFixedWidth(40);
    baudrateCbox = new QComboBox(this);
    baudrateCbox->setFixedWidth(100);
    QStringList baudList;
    baudList << "50"
             << "75"
             << "100"
             << "134"
             << "150"
             << "200"
             << "300"
             << "600"
             << "1200"
             << "1800"
             << "2400"
             << "4800"
             << "9600"
             << "14400"
             << "19200"
             << "38400"
             << "56000"
             << "57600"
             << "76800"
             << "115200"
             << "128000"
             << "256000";
    baudrateCbox->addItems(baudList);
    baudrateCbox->setCurrentIndex(19);

    QLabel *parityBitLbl = new QLabel(this);
    parityBitLbl->setText(tr("校验位："));
    parityBitLbl->setFixedWidth(40);
    parityBitCbox = new QComboBox(this);
    parityBitCbox->setFixedWidth(100);
    QStringList parityList;
    parityList << "无"
               << "奇"
               << "偶";
#ifdef Q_OS_WIN
    parityList << "标志";
#endif
    parityList << "空格";
    parityBitCbox->addItems(parityList);

    QLabel *dataBitLbl = new QLabel(this);
    dataBitLbl->setText(tr("数据位："));
    dataBitLbl->setFixedWidth(40);
    dataBitCbox = new QComboBox(this);
    dataBitCbox->setFixedWidth(100);
    QStringList dataBitsList;
    dataBitsList << "5"
                 << "6"
                 << "7"
                 << "8";
    dataBitCbox->addItems(dataBitsList);
    dataBitCbox->setCurrentIndex(3);

    QLabel *stopBitLbl = new QLabel(this);
    stopBitLbl->setText(tr("停止位："));
    stopBitLbl->setFixedWidth(40);
    stopBitCbox = new QComboBox(this);
    stopBitCbox->setFixedWidth(100);
    QStringList stopBitsList;
    stopBitsList << "1";
#ifdef Q_OS_WIN
    stopBitsList << "1.5";
#endif
    stopBitsList << "2";
    stopBitCbox->addItems(stopBitsList);

    startComBtn = new QPushButton(this);
    startComBtn->setText(tr("打开"));
    connect(startComBtn, &QPushButton::clicked, this, &MySerialWidget::on_btn_openConsole_clicked);

    glayoutComConf->addWidget(comIndexLbl, 0, 0);
    glayoutComConf->addWidget(comIndexCbox, 0, 1);
    glayoutComConf->addWidget(baudrateLbl, 1, 0);
    glayoutComConf->addWidget(baudrateCbox, 1, 1);
    glayoutComConf->addWidget(parityBitLbl, 2, 0);
    glayoutComConf->addWidget(parityBitCbox, 2, 1);
    glayoutComConf->addWidget(dataBitLbl, 3, 0);
    glayoutComConf->addWidget(dataBitCbox, 3, 1);
    glayoutComConf->addWidget(stopBitLbl, 4, 0);
    glayoutComConf->addWidget(stopBitCbox, 4, 1);
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

    QSplitter *splitterRight = new QSplitter(Qt::Vertical, splitMain); //Qt::Vertical设置为竖直分割，splitMain代表为父窗口
    splitterRight->setOpaqueResize(false);                             //为splitterRight设置拖动时是否实时更新，false拖动时只有一个线条

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

void MySerialWidget::on_btn_openConsole_clicked()
{
    if (startComBtn->text() == tr("打开"))
    {
        //设置串口名字
        serial->setPortName(comIndexCbox->currentText());
        //设置波特率
        serial->setBaudRate(baudrateCbox->currentText().toInt());
        //设置数据位
        serial->setDataBits(QSerialPort::Data8);
        //设置奇偶校验位
        serial->setParity(QSerialPort::NoParity);
        //设置停止位
        serial->setStopBits(QSerialPort::OneStop);
        //设置流控
        serial->setFlowControl(QSerialPort::NoFlowControl);
        //打开串口
        if (serial->open(QIODevice::ReadWrite))
        {
            baudrateCbox->setEnabled(false);
            dataBitCbox->setEnabled(false);
            // ui->comboBox_flowBit->setEnabled(false);
            parityBitCbox->setEnabled(false);
            comIndexCbox->setEnabled(false);
            stopBitCbox->setEnabled(false);
            // ui->btn_send->setEnabled(true);
            startComBtn->setText(tr("关闭"));
            //信号与槽函数关联
            connect(serial, &QSerialPort::readyRead, this, &MySerialWidget::readData);
        }
    }
    else
    {
        //关闭串口
        //serial->clear();
        serial->close();
        //serial->deleteLater();
        //恢复设置功能
        baudrateCbox->setEnabled(true);
        dataBitCbox->setEnabled(true);
        // ui->comboBox_flowBit->setEnabled(false);
        parityBitCbox->setEnabled(true);
        comIndexCbox->setEnabled(true);
        stopBitCbox->setEnabled(true);
        // ui->btn_send->setEnabled(true);
        startComBtn->setText(tr("打开"));
    }
}

void MySerialWidget::on_btn_send_clicked()
{
}

void MySerialWidget::on_btn_clearRecv_clicked()
{
}

void MySerialWidget::on_btn_clearSend_clicked()
{
}

void MySerialWidget::readData()
{
    QByteArray buf;
    buf = serial->readAll();
    if (!buf.isEmpty())
    {
        QString str = textUp->toPlainText();
        
        QDateTime now = QDateTime::currentDateTime();
        QString name = now.toString("yyyy-MM-dd_HH:mm:ss.zzz");
        str += name;
        str += tr("> ");
        //过滤回车换行符
        QString strData = QString::fromLocal8Bit(buf);
        strData = strData.replace("\r", "");
        strData = strData.replace("\n", "");
        // str += tr(buf);
        str += strData;
        str += tr("\r\n");
        textUp->clear();
        textUp->append(str);
    }
}
