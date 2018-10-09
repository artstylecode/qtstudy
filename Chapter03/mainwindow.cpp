#include <QtGui>
#include "mainwindow.h"
#include "finddialog.h"
#include "gotocelldialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    spreadsheet = new Spreadsheet;
    setCentralWidget(spreadsheet);
    createActions();
    createMenu();
    createContextMenu();
    createToolBar();
    createStatuBar();
    readSettings();
    findDialog = 0;

    setWindowIcon(QIcon(":/images/spreadsheet.ico"));
    setCurrentFile("");
}
void MainWindow::closeEvent(QCloseEvent * event)
{

}
/**
 * 创建action
 * @brief MainWindow::createActions
 */
void MainWindow::createActions()
{
    //初始化菜单项
    newAction =new QAction(tr("&new"), this);
    newAction ->setShortcut(QKeySequence::New);
    newAction ->setStatusTip("create a new spreedsheet file.");
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

    openAction = new QAction(tr("&open"), this);
    openAction ->setShortcut(QKeySequence::Open);
    openAction ->setStatusTip("open an spreedsheet file.");
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    saveAction = new QAction(tr("&save"), this);
    saveAction ->setShortcut(QKeySequence::Save);
    saveAction ->setStatusTip("save the spreedsheet file.");
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAction = new QAction(tr("&save as"), this);
    saveAsAction ->setShortcut(QKeySequence::SaveAs);
    saveAsAction ->setStatusTip("save as the spreedsheet file.");
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    aboutAction = new QAction(tr("&about"), this);
    aboutAction ->setStatusTip("about spreedsheet.");
    connect(aboutAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    exitAction = new QAction(tr("e&xit"), this);
    exitAction ->setShortcut(tr("Ctrl+q"));
    exitAction ->setStatusTip("exit the spreedsheet application!");
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    findAction = new QAction(tr("&find"), this);
    findAction ->setShortcut(QKeySequence::Find);
    findAction ->setStatusTip("find the content.");
    connect(findAction, SIGNAL(triggered()), this, SLOT(find()));
    gotocellAction = new QAction(tr("&go to"), this);
    gotocellAction ->setShortcut(tr("Ctrl + g"));
    gotocellAction ->setStatusTip("go to cell.");
    connect(gotocellAction, SIGNAL(triggered()), this, SLOT(gotoCell()));

    selectAllAction = new QAction(tr("select all"), this);
    selectAllAction ->setShortcut(QKeySequence::SelectAll);
    selectAllAction ->setStatusTip("select all content.");
    connect(selectAllAction, SIGNAL(triggered()), spreadsheet, SLOT(selectAll()));

    showGridAction = new QAction(tr("show grid"), this);
    showGridAction ->setCheckable(true);
    showGridAction ->setChecked(spreadsheet->showGrid());
    showGridAction ->setStatusTip("show or hide spreedsheet's grid");
    connect(showGridAction, SIGNAL(triggered(bool)), spreadsheet, SLOT(setShowGrid(bool)));

    //动态生成最近文件action列表
    for(int i =0;i < MAXRECENTFILES;i++)
    {
        recentActions[i] = new QAction(this);
        recentActions[i]->setVisible(false);
        connect(recentActions[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));
    }

}
/**
 *
 *
 * 创建窗口菜单
 * @brief MainWindow::createMenu
 */
void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu("&File");
    fileMenu ->addAction(newAction);
    fileMenu ->addAction(openAction);
    fileMenu ->addAction(saveAction);
    fileMenu ->addAction(saveAsAction);
    fileMenu ->addAction(saveAsAction);
     fileMenu->addSeparator();
    for(int i =0;i < MAXRECENTFILES;i++)
    {
        fileMenu ->addAction(recentActions[i]);
    }
    fileMenu->addSeparator();
    fileMenu ->addAction(exitAction);
    editMenu = menuBar() ->addMenu("&Edit");
    editMenu -> addAction(findAction);
    editMenu -> addAction(gotocellAction);
    editMenu ->addAction(selectAllAction);
    editMenu ->addAction(showGridAction);

    helpMenu = menuBar()->addMenu("&Help");
    helpMenu ->addAction(aboutAction);

}
/**
 * 创建右键菜单
 * @brief MainWindow::createContextMenu
 */
void MainWindow::createContextMenu()
{

}
/**
 * 创建工具栏
 * @brief MainWindow::createToolBar
 */
void MainWindow::createToolBar()
{

}
/**
 * 创建状态栏
 * @brief MainWindow::createStatuBar
 */
void MainWindow::createStatuBar()
{

}
/**
 * 读取用户配置文件
 * @brief MainWindow::readSettings
 */
void MainWindow::readSettings()
{

}
/**
 * 设置当前读取的文件
 * @brief MainWindow::setCurrentFile
 * @param fileName 文件路径
 */
void MainWindow::setCurrentFile(const QString &fileName)
{

}
//插槽
/**
 *新建文件
 * @brief MainWindow::newFile
 */
void MainWindow::newFile()
{

}
/**
 *打开文件
 * @brief MainWindow::open
 */
void MainWindow::open()
{

}
/**
 *保存文件
 * @brief MainWindow::save
 * @return
 */
bool MainWindow::save()
{

}
/**
 *文件另存为
 * @brief MainWindow::saveAs
 * @return
 */
bool MainWindow::saveAs()
{

}
/**
 *查找当前文件内容
 * @brief MainWindow::find
 */
void MainWindow::find()
{

}
/**
 *跳转到指定单元格
 * @brief MainWindow::gotoCell
 */
void MainWindow::gotoCell()
{

}
/**
 *排序内容
 * @brief MainWindow::sort
 */
void MainWindow::sort()
{

}
/**
 * 显示关于
 * @brief MainWindow::about
 */
void MainWindow::about()
{

}
/**
 *打开最近文档
 * @brief MainWindow::openRecentFile
 */
void MainWindow::openRecentFile()
{

}
/**
 *更新状态栏
 * @brief MainWindow::updateStatusBar
 */
void MainWindow::updateStatusBar()
{

}
/**
 *表格修改
 * @brief MainWindow::spreadsheetModified
 */
void MainWindow::spreadsheetModified()
{

}


