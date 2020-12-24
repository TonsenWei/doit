# 简介

学习qt5过程中的源码。
使用CMake构建。
验证环境为win10 64位。


## 最近更新

    V1.1.7 
        1、QSerialPort(串口)组件的使用，串口数据接收功能测试。
        2、QTextEdit（文本框）使用，设置文字对齐，横向滚动条。
        3、QComboBox默认不可编辑，通过setEditable(true)设置为可编辑当前文字。
        4、QStringList使用。
        5、QGridLayout布局使用。

    V1.1.6 
        1、自定义对话框使用。
        2、QChart折线图清除和添加曲线操作，曲线的显示和隐藏。
        3、尝试打包exe,精简最小的dll依赖，打包后的文件解压到没有安装qt的环境上可以正常运行。

    V1.1.5 
        1、QTableView配合StandardItemModel的使用。

    V1.1.4 
        1、信号和槽的使用，QComboBox下拉框的使用
        2、QSpacerItem（弹簧控件）的使用

    V1.1.3 
        1、QtCharts(图表)使用，绘制折线图

    V1.1.2 
        1、QHBoxLayout（布局），QSplitter(分割窗)使用

    V1.1.1 
        1、同步时忽略.vscode文件夹。
		2、发现使用windeployqt打包的dll仍可以精简，需要自己尝试。
		
    V1.1.0 
        1.win10下配置环境，使用VSCode + CMake + mingw编译构建调试。

    V1.0.0 
        1.使用QtCreater创建CMake工程后，使用VSCode打开进行编辑和调试。
        2.创建主窗口，主要学习菜单栏，QDockWidget，状态栏的添加。