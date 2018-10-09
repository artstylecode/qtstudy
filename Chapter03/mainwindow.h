#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class Spreadsheet: public QTabWidget
{
public:
    bool showGrid(){return true;};
};
class QLabel;
class Finddialog;
class GoToCellDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    virtual void closeEvent(QCloseEvent *);
signals:

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void find();
    void gotoCell();
    void sort();
    void about();
    void openRecentFile();
    void updateStatusBar();
    void spreadsheetModified();
private:
    //数据成员
    Spreadsheet *spreadsheet;
    Finddialog *findDialog;
    GoToCellDialog * gotocellDialog;
    QLabel *locationLabel;
    QLabel * formualLabel;
    QStringList recentFiles;
    QString currentFile;
    enum {MAXRECENTFILES=5};
    QAction *recentActions[MAXRECENTFILES];
    QAction *separatorAction;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;
    QMenu *selectSubMenu;
    QToolBar * fileToolBar;
    QToolBar * editToolBar;
    //file 菜单;
    QAction * newAction;
    QAction * openAction;
    QAction * saveAction;
    QAction * saveAsAction;
    QAction * aboutAction;
    QAction * exitAction;
    //edit 菜单;
    QAction * cutAction;
    QAction * copyAction;
    QAction * pasteAction;
    QAction * deleteAction;    
    QAction * selectRowAction;
    QAction * selectColumnAction;
    QAction * selectAllAction;
    QAction * findAction;
    QAction * gotocellAction;
    //options
    QAction * showGridAction;
    QAction * autoRecalcAction;
    void createActions();
    void createMenu();
    void createContextMenu();
    void createToolBar();
    void createStatuBar();
    void readSettings();
    void writeSettings();
    bool okToContinue();
    bool loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    void updateRecentFileActions();
    QString strippedName(const QString &fullFileName);
};

#endif // MAINWINDOW_H
