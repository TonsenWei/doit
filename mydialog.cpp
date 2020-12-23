#include"mydialog.h"
#include <QMessageBox>
 
CLoginDlg::CLoginDlg(QWidget* parent):QDialog(parent)
{
    kValueLbl=new QLabel(tr("K值："));
    tmValueLbl=new QLabel(tr("Tm值："));
    tValueLbl = new QLabel(tr("T值"));
    kValueLineEdit=new QLineEdit;
    tmValueLineEdit=new QLineEdit;
    tValueLineEdit = new QLineEdit;
    //设置密码编辑框对象pwdLineEdit的内容显示方式为采用星号“*”代替用户输入的字符
    // tmValueLineEdit->setEchoMode(QLineEdit::Password);
 
    //创建一个网格布局管理器对象，并将窗口部件添加到该布局管理器中
    gridLayout=new QGridLayout;
    gridLayout->addWidget(kValueLbl,0,0,1,1);
    gridLayout->addWidget(kValueLineEdit,0,1,1,3);
    gridLayout->addWidget(tmValueLbl,1,0,1,1);
    gridLayout->addWidget(tmValueLineEdit,1,1,1,3);
    gridLayout->addWidget(tValueLbl,2,0,1,1);
    gridLayout->addWidget(tValueLineEdit,2,1,1,3);
 
    //创建两个按钮对象和一个水平布局管理器对象，并将按钮对象添加到该布局管理器中
    okBtn=new QPushButton(tr("确定"));
    cancelBtn=new QPushButton(tr("取消"));
    btnLayout=new QHBoxLayout;
    btnLayout->setSpacing(60);
    btnLayout->addWidget(okBtn);
    btnLayout->addWidget(cancelBtn);
 
    //创建一个垂直布局管理器对象，并将水平和网格布局管理器添加到该管理器中
    dlgLayout=new QVBoxLayout;
    dlgLayout->setMargin(40);
    dlgLayout->addLayout(gridLayout);
    dlgLayout->addStretch(40);
    dlgLayout->addLayout(btnLayout);
    setLayout(dlgLayout);
 
    //将两个按钮的信号与槽关联起来
    connect(okBtn,SIGNAL(clicked()),this,SLOT(accept()));
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT(reject()));
 
    //设置对话框的标题和大小
    setWindowTitle(tr("增加曲线"));
    resize(300,200);
}
 
void CLoginDlg::accept()
{
    if(kValueLineEdit->text().trimmed()!=tr("") &&
        tmValueLineEdit->text().trimmed()!=tr("") &&
        tValueLineEdit->text().trimmed()!=tr(""))
    {
        QDialog::accept();
    }
    else
        QMessageBox::warning(this,tr("警告"),
                             tr("请输入完整参数！"),
                             QMessageBox::Yes);
        kValueLineEdit->setFocus();
}

QString CLoginDlg::getKvalueStr()
{
    return kValueLineEdit->text().trimmed();
}

QString CLoginDlg::getTmValueStr()
{
    return tmValueLineEdit->text().trimmed();
}

QString CLoginDlg::getTValueStr()
{
    return tValueLineEdit->text().trimmed();
}