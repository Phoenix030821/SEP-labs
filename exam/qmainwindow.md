（详细的后续会讲到，这里重在理解过程）
Qt中的顶层窗口称为MainWindow，属于类QMainWindow，QMainWindow也是继承于QWidget。通过子类化QMainWindow可以创建一个应用程序的窗口。

MainWindow的结构分为五个部分：菜单栏（Menu Bar）、工具栏（Toolbars）、停靠窗口（Dock Widgets）、状态栏（Status Bar）和中央窗口（Central Widget）。可以用下面的图形表示之。



其中，中央窗口可以使用任何形式的widget来填充。一般不建议使中央窗口为空。可以使用setCentralWidget()函数来填充中央窗口。

一、Menu Bar

首先要区分好菜单与菜单栏。菜单是QMenu对象，然后将多个QMenu对象放置在一个QMenuBar(菜单栏)对象中。对于每个菜单，我们再为其添置动作列表，即QAction对象。步骤如下

mainwindow.h

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

class QAction;
class QMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    QAction *openAction;  //定义一个动作
    QMenu *fileMenu;  //定义一个菜单
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
mainwindow.cpp
<pre name="code" class="cpp"><pre name="code" class="cpp">#include "mainwindow.h"

#include <QMenu>
#include <QMenuBar>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    openAction = new QAction(tr("Open"),this);  //初始化动作
    fileMenu = new QMenu;  //创建一个菜单
    fileMenu = menuBar()->addMenu(tr("File"));  //将菜单添加到菜单栏上
    fileMenu->addAction(openAction);  //将动作添加到菜单上
}

MainWindow::~MainWindow()
{
    
}


运行结果如下：

思路已经很清晰了，首先创建一个菜单File，将它添加到菜单栏上，然后再将动作Open添加到此菜单下。其中，注意到菜单栏是单数，即Menu Bar中的Bar是单数（这里跟工具栏要区分开），QMainWindw类中有一个叫MenuBar()的函数，用来返回MainWindow的菜单栏（一个QMenuBar对象），然后QMenuBar类中有一个addMenu()函数用来添加一个菜单到菜单栏中。

二、ToolBars

为什么我要强调菜单栏中是单数而工具栏中是复数，这是为了理解两种Bar的不同用法。

首先，在MainWindw中菜单栏并不止一个，可以自己创建，所以并不是从QMainWindow中的哪个函数来返回哪个工具栏。因此，第一步要创建一个工具栏。在QMainWindow类中有addToolBar()函数来添加工具栏，然后根据QToolBar类中的addAction()函数来为新建的工具栏添加动作。具体示例代码如下：

mainwindow.h

```c++
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

class QAction;
class QToolBar;

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    QAction *openAction;  //定义一个动作
    QToolBar *fileToolBar;  //定义一个工具栏
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
```

mainwindow.cpp

```c++
#include "mainwindow.h"

#include <QToolBar>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    openAction = new QAction(tr("Open"),this);  //初始化动作
    fileToolBar = new QToolBar;  //创建一个工具栏
    fileToolBar = addToolBar(tr("File"));  //添加工具栏到顶层窗口中
    fileToolBar->addAction(openAction);  //为新建的工具栏添加动作
}

MainWindow::~MainWindow()
{
    
}
```




这个过程很清晰了。
总结一下：

菜单栏是MainWindow中已经有的，需要是就使用menuBar()函数来返回；工具栏需要自己新建，然后在通过addToolBar()函数添加到窗口中。

其它的部分会在其它的博客中给出。
————————————————
版权声明：本文为CSDN博主「芳草源」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/hulifangjiayou/article/details/44220991