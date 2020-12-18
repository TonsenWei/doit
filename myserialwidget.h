#ifndef MYSERIALWIDGET_H
#define MYSERIALWIDGET_H

#include <QWidget>

class MySerialWidget : public QWidget
{
    Q_OBJECT

public:
    MySerialWidget(QWidget *parent = nullptr);
    ~MySerialWidget();

private:
    void initSerialUi();

};

#endif // MYSERIALWIDGET_H
