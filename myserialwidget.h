#ifndef MYSERIALWIDGET_H
#define MYSERIALWIDGET_H

#include <QWidget>
#include <QSerialPort>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
class MySerialWidget : public QWidget
{
    Q_OBJECT

public:
    MySerialWidget(QWidget *parent = nullptr);
    ~MySerialWidget();

private slots:
    void on_btn_openConsole_clicked();
    void on_btn_send_clicked();
    void on_btn_clearRecv_clicked();
    void on_btn_clearSend_clicked();
    void readData();

private:
    void initSerialUi();
    QSerialPort *serial;
    QComboBox *comIndexCbox;
    QComboBox *baudrateCbox;
    QComboBox *parityBitCbox;
    QComboBox *dataBitCbox;
    QComboBox *stopBitCbox;
    QPushButton *startComBtn;
    QTextEdit *textUp;
    QTextEdit *textBottom;
};

#endif // MYSERIALWIDGET_H
