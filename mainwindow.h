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
    void createMenuBar();
    void createStatusBar();
    void createToolBar();

    void createMainContents();
    void createQDockWidgets();
    void createQTabWidget();
    
    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
    const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/images/save.png"));
};

#endif // MAINWINDOW_H
