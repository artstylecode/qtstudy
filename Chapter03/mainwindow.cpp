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
    gotocellDialog =0;

    setWindowIcon(QIcon(":/images/spreadsheet.ico"));
    setCurrentFile("");
}
MainWindow::~MainWindow()
{
        delete findDialog;

        delete gotocellDialog;
}
void MainWindow::closeEvent(QCloseEvent * event)
{
    if(okToContinue())
    {
        writeSettings();
        event->accept();
    }else
    {
        event ->ignore();
    }
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
    aboutAction ->setStatusTip("about application.");
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    aboutQtAction = new QAction(tr("&aboutQT"), this);
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    aboutQtAction ->setStatusTip("About QT!");
    closeAction = new QAction(tr("&close"), this);
    closeAction ->setStatusTip("close current Widnow.");
    connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));
    exitAction = new QAction(tr("e&xit"), this);
    exitAction ->setShortcut(tr("Ctrl+q"));
    exitAction ->setStatusTip("exit the spreedsheet application!");
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

    cutAction = new QAction(tr("cut"),this);
    cutAction ->setShortcut(QKeySequence::Cut);
    cutAction ->setStatusTip("cut selected content");
    connect(cutAction, SIGNAL(triggered()), spreadsheet, SLOT(cut()));
    copyAction = new QAction(tr("copy"), this);
    copyAction ->setShortcut(QKeySequence::Copy);
    copyAction ->setStatusTip("copy selected content");
    connect(copyAction, SIGNAL(triggered()), spreadsheet, SLOT(copy()));
    pasteAction = new QAction(tr("paste"), this);
    pasteAction ->setShortcut(QKeySequence::Paste);
    pasteAction -> setStatusTip("past conent");
    connect(pasteAction, SIGNAL(triggered()), spreadsheet, SLOT(paste()));

    deleteAction = new QAction(tr("del"), this);
    deleteAction -> setShortcut(QKeySequence::Delete);
    deleteAction -> setStatusTip("delete selected content.");
    connect(deleteAction, SIGNAL(triggered()), spreadsheet, SLOT(del()));

    selectRowAction = new QAction(tr("select a row"), this);
    selectRowAction -> setShortcut(tr("Shift+r"));
    selectRowAction -> setStatusTip("select current row.");
    connect(selectRowAction, SIGNAL(triggered()), spreadsheet, SLOT(selectCurrentRow()));

    selectColumnAction = new QAction(tr("select a &column"), this);
    selectColumnAction -> setShortcut(tr("Shift+c"));
    selectColumnAction -> setStatusTip("select current column.");
    connect(selectColumnAction, SIGNAL(triggered()), spreadsheet, SLOT(selectCurrentColumn()));

    findAction = new QAction(tr("&find"), this);
    findAction ->setShortcut(QKeySequence::Find);
    findAction ->setStatusTip("find the content.");
    connect(findAction, SIGNAL(triggered()), this, SLOT(find()));
    gotocellAction = new QAction(tr("&go to"), this);
    gotocellAction ->setShortcut(tr("Ctrl+g"));
    gotocellAction ->setStatusTip("go to cell.");
    connect(gotocellAction, SIGNAL(triggered()), this, SLOT(gotoCell()));

    selectAllAction = new QAction(tr("select all"), this);
    selectAllAction ->setShortcut(QKeySequence::SelectAll);
    selectAllAction ->setStatusTip("select all content.");
    connect(selectAllAction, SIGNAL(triggered()), spreadsheet, SLOT(selectAll()));

    autoRecalcAction = new QAction(tr("auto recalc"), this);
    autoRecalcAction ->setCheckable(true);
    autoRecalcAction -> setChecked(false);
    autoRecalcAction -> setStatusTip("auto recalc.");

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
    //this->setSizePolicy(QSizePolicy::Maximum);

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
    fileMenu ->addAction(closeAction);
    fileMenu->addSeparator();
    fileMenu ->addAction(exitAction);

    editMenu = menuBar() ->addMenu("&Edit");
    editMenu -> addAction(cutAction);
    editMenu -> addAction(copyAction);
    editMenu -> addAction(pasteAction);
    editMenu -> addAction(deleteAction);
    selectSubMenu  = editMenu -> addMenu("&Select");
    selectSubMenu -> addAction(selectRowAction);
    selectSubMenu -> addAction(selectColumnAction);
    selectSubMenu -> addAction(selectAllAction);

    editMenu ->addSeparator();
    editMenu -> addAction(findAction);
    editMenu -> addAction(gotocellAction);

    optionMenu = menuBar()->addMenu("&Options");
    optionMenu ->addAction(showGridAction);
    optionMenu -> addAction(autoRecalcAction);



    helpMenu = menuBar()->addMenu("&Help");
    helpMenu ->addAction(aboutAction);
    helpMenu ->addAction(aboutQtAction);
}
/**
 * 创建右键菜单
 * @brief MainWindow::createContextMenu
 */
void MainWindow::createContextMenu()
{
    spreadsheet -> addAction(cutAction);
    spreadsheet -> addAction(copyAction);
    spreadsheet -> addAction(deleteAction);
    spreadsheet -> addAction(selectRowAction);
    spreadsheet -> addAction(selectColumnAction);
    spreadsheet -> addAction(selectAllAction);
    spreadsheet -> setContextMenuPolicy(Qt::ActionsContextMenu);
}
/**
 * 创建工具栏
 * @brief MainWindow::createToolBar
 */
void MainWindow::createToolBar()
{
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar -> addAction(newAction);
    fileToolBar -> addAction(openAction);
    fileToolBar -> addAction(saveAction);
    fileToolBar -> addAction(saveAsAction);

    editToolBar = addToolBar(tr("&Edit"));
    editToolBar -> addAction(cutAction);
    editToolBar -> addAction(pasteAction);
    editToolBar -> addAction(deleteAction);
    editToolBar -> addSeparator();
    editToolBar -> addAction(findAction);
    editToolBar -> addAction(gotocellAction);
}
/**
 * 创建状态栏
 * @brief MainWindow::createStatuBar
 */
void MainWindow::createStatuBar()
{
    locationLabel = new QLabel("w999");
    locationLabel -> setAlignment(Qt::AlignCenter);
    locationLabel -> setMinimumSize(locationLabel -> sizeHint());

    formualLabel = new QLabel("3");
    formualLabel -> setIndent(3);

    statusBar()->addWidget(locationLabel);
    statusBar() -> addWidget(formualLabel,1);

    connect(spreadsheet, SIGNAL(currentCellChanged(int , int, int, int)), this, SLOT(updateStatusBar()));
    //connect(spreadsheet, SIGNAL(modified()), this , SLOT(spreadsheetModified()));
}
void MainWindow::updateRecentFileActions()
{

}
 QString MainWindow::strippedName(const QString &fullFileName)
 {
     return QFileInfo(fullFileName).fileName();
 }
/**
 * 读取用户配置文件
 * @brief MainWindow::readSettings
 */
void MainWindow::readSettings()
{
    QSettings settings("Software Inc", "SpreadSheet");
    restoreGeometry(settings.value("geometry").toByteArray());
    recentFiles = settings.value("recentFiles").toStringList();
    updateRecentFileActions();
    showGridAction ->setChecked(settings.value("showGrid").toBool());
    autoRecalcAction ->setChecked(settings.value("autoRecalc").toBool());

}
void MainWindow::writeSettings()
{
    QSettings settings("Software Inc", "SpreadSheet");
    //保存窗口信息
    settings.setValue("geometry", saveGeometry());
    settings.setValue("recentFiles", recentFiles);
    settings.setValue("showGrid", showGridAction -> isChecked());
    settings.setValue("autoRecalc", autoRecalcAction -> isChecked());
}
/**
 * 设置当前读取的文件
 * @brief MainWindow::setCurrentFile
 * @param fileName 文件路径
 */
void MainWindow::setCurrentFile(const QString &fileName)
{
    currentFile = fileName;
    setWindowModified(false);
    QString showname = tr("Untitled");
    if(!currentFile.isEmpty())
    {
        showname = strippedName(currentFile);
        recentFiles.removeAll(showname);
        recentFiles.prepend(showname);
        updateRecentFileActions();
        spreadsheet->readFile(currentFile);
    }
    setWindowTitle(tr("%1 - %2").arg(showname).arg(tr("spreadsheet")));

}
//插槽
/**
 *新建文件
 * @brief MainWindow::newFile
 */
void MainWindow::newFile()
{
    if(okToContinue())
    {
        MainWindow *newWindow  =new MainWindow();
        newWindow->show();
        spreadsheet ->clear();
        setCurrentFile("");
    }
}
/**
 *打开文件
 * @brief MainWindow::open
 */
void MainWindow::open()
{
    if(okToContinue())
    {
        QString filename = QFileDialog::getOpenFileName(this,tr("Open SpreadSheet"),
                                                                ".", tr("SpreadSheet files(*.sp)"));
        qDebug()<< "filename:"<< filename;

        if(!filename.isEmpty())
        {
            loadFile(filename);
        }


    }
}
bool MainWindow::loadFile(const QString &fileName)
{

    if(spreadsheet->readFile(fileName))
    {
        setCurrentFile(fileName);
        return true;
    }
    return false;
}
/**
 *保存文件
 * @brief MainWindow::save
 * @return
 */
bool MainWindow::save()
{
    if(currentFile.isEmpty())
    {
        return saveAs();
    }else
    {
        return saveFile(currentFile);
    }
}
/**
 *文件另存为
 * @brief MainWindow::saveAs
 * @return
 */
bool MainWindow::saveAs()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("save spreadsheets"), ".",
                                                    tr("SpreadSheet files(*.sp)"));
    if(filename.isEmpty())
        return false;
    return saveFile(filename);
}

bool MainWindow::saveFile(const QString &fileName)
{
    return spreadsheet->writeFile(fileName);
}
/**
 *查找当前文件内容
 * @brief MainWindow::find
 */
void MainWindow::find()
{
    if(findDialog==0)
    {
        findDialog = new Finddialog();
        connect(findDialog, SIGNAL(findNext(QString&,Qt::CaseSensitivity)),
                spreadsheet, SLOT(findNext(QString & ,Qt::CaseSensitivity)));
        connect(findDialog, SIGNAL(findPrevious(QString&,Qt::CaseSensitivity)),
                spreadsheet, SLOT(findPrevious(QString &,Qt::CaseSensitivity)));

    }
    findDialog->show();
    findDialog ->raise();
    findDialog ->activateWindow();
}
/**
 *跳转到指定单元格
 * @brief MainWindow::gotoCell
 */
void MainWindow::gotoCell()
{
    if(gotocellDialog==0)
    {
        gotocellDialog = new GoToCellDialog();
        connect(gotocellDialog, SIGNAL(goToClicked(QString)),
                spreadsheet, SLOT(goToCell(QString)));

    }
    gotocellDialog ->show();
    gotocellDialog ->raise();
    gotocellDialog ->activateWindow();
}
bool MainWindow::okToContinue()
{
    if(isWindowModified())
    {
        int r =QMessageBox::warning(this, "has save spreadsheet?", "The document has been modified.\n Do you want to save your changes",
                             QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if(r == QMessageBox::Yes)
        {
            return save();
        }else if(r==QMessageBox::Cancel)
        {
            return false;
        }
    }
    return true;
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
    QMessageBox::about(this , tr("About spreadSheet"),
                       tr("<h1>SpreadSheet1.0</h1>"
                          "<p>CopyRight &copy;2008 SoftWare Inc.</p>"
                          "<p>SpreadSheet is a small Application that</p>")
                       );
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
    locationLabel ->setText(spreadsheet -> currentLocation());
    formualLabel -> setText(spreadsheet -> currentFormula());
}
/**
 *表格修改
 * @brief MainWindow::spreadsheetModified
 */
void MainWindow::spreadsheetModified()
{
    setWindowModified(true);
    updateStatusBar();
}


