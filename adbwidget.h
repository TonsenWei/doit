#ifndef ADBWIDGET_H
#define ADBWIDGET_H

#include <QtWidgets>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <QString>
class AdbWidget : public QWidget
{
    Q_OBJECT

public:
    AdbWidget(QWidget *parent = nullptr);
    ~AdbWidget();

private slots:

private:
    void initAdbUi();
    void execProcessAndReadByLine();
    QComboBox *comIndexCbox;
    QComboBox *baudrateCbox;
    QComboBox *parityBitCbox;
    QComboBox *dataBitCbox;
    QComboBox *stopBitCbox;
    QPushButton *startComBtn;
    QTextEdit *textUp;
    QTextEdit *textBottom;
};

#endif // ADBWIDGET_H
