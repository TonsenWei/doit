#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initWindow();
    void createActions();
    void createStatusBar();
    void createMainContents();
    void createQDockWidgets();
    
    void createQTabWidget();
};

#endif // MAINWINDOW_H
