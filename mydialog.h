//定义宏变量，确保该头文件只被包含一次，防止头文件被多次包含
#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QVBoxLayout>


 
class CLoginDlg:public QDialog
{
    Q_OBJECT
public:
    //构造函数，表示自定义的对话框没有父窗口部件
    CLoginDlg(QWidget *parent=0);
    QString getKvalueStr();
    QString getTmValueStr();
    QString getTValueStr();

public slots:
    virtual void accept();
private:
    QLabel *kValueLbl;
    QLabel *tmValueLbl;
    QLabel *tValueLbl;
 
    QLineEdit* kValueLineEdit;
    QLineEdit* tmValueLineEdit;
    QLineEdit* tValueLineEdit;
 
    QPushButton *okBtn;
    QPushButton *cancelBtn;
 
    QHBoxLayout *btnLayout;
    QGridLayout *gridLayout;
    QVBoxLayout *dlgLayout;
};
 
#endif // MYDIALOG_H