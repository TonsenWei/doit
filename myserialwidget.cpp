#include "myserialwidget.h"
#include "QSplitter"
#include "QTextEdit"
#include "QDebug"
#include "QHBoxLayout"

MySerialWidget::MySerialWidget(QWidget *parent)
    : QWidget(parent)
{
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
    
    QHBoxLayout *mainLayout =new QHBoxLayout(this);      //使用QHBoxLayout布局
    QSplitter *splitMain = new QSplitter(Qt::Horizontal, this);     //Qt::Horizontal设置为水平分割，0代表为主窗口，无父窗口

    QTextEdit *textLeft = new QTextEdit(QObject::tr("Left"), splitMain);  //为splitMain窗口添加控件
    textLeft->setAlignment(Qt::AlignCenter);
    // textLeft->setStyleSheet("QTextEdit{border-radius:5px;}");

    QSplitter *splitterRight =new QSplitter(Qt::Vertical,splitMain);  //Qt::Vertical设置为竖直分割，splitMain代表为父窗口
    splitterRight->setOpaqueResize(false);                            //为splitterRight设置拖动时是否实时更新，false拖动时只有一个线条

    QTextEdit *textUp =new QTextEdit(QObject::tr("Top"),splitterRight);  //为splitterRight窗口添加控件
    textUp->setAlignment(Qt::AlignCenter);
    QTextEdit *textBottom =new QTextEdit(QObject::tr("Bottom"),splitterRight);
    textBottom->setAlignment(Qt::AlignCenter);

    splitMain->setStretchFactor(1,1); //设置可伸缩控件，第一个参数为控件序号，第二个参数0代表可伸缩，放大整个窗口大小可以发现左边小窗口大小不变
    

    splitMain->setFrameStyle(QFrame::NoFrame);
    splitMain->setHandleWidth(0);           // 设置分界线的宽度
    splitterRight->setFrameStyle(QFrame::NoFrame);
    splitterRight->setHandleWidth(0);       // 设置分界线的宽度
    mainLayout->addWidget(splitMain);
    mainLayout->setMargin(5);   // 跟外部窗口间隔为0,如果设置，默认为10
    mainLayout->setSpacing(0);  //设置layout中各部件的相邻距离，如果不设置，这个距离默认是10
}