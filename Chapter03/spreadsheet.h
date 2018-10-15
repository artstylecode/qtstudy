#ifndef SPREADSHEET_H
#define SPREADSHEET_H
#include <QTableWidget>

class Cell;
class SpreadsheetCompare;
class Spreadsheet :public QTableWidget
{
    Q_OBJECT
private slots:
    void somethingChanged();

    void cut();
    void copy();
    void del();
    void paste();
    void selectCurrentRow();
    void selectCurrentColumn();
    void findNext( QString & str, Qt::CaseSensitivity cs);
    void findPrevious(QString &str, Qt::CaseSensitivity cs);
    void goToCell(QString cellstr);
    void recalculate();

private:
    enum {MagicNumber=0x7F51C883,RowCount=999,ColumnCount=26};
    QString text(int row, int col)const;
    QString formula(int row, int col)const;
    void setFormula(int row, int col, const QString & text);
    bool autoRecalc;

    Cell *cell(int row, int columnn)const;

signals:
    void modified();
public:
    Spreadsheet(QWidget * parent =0);
    //自动公式重新计算
    bool autoRecalculate()const;
    //获取当前位置信息
    QString currentLocation()const;
    //获取当前单元格公式
    QString currentFormula()const;
    //获取当前选中区域
    QTableWidgetSelectionRange selectedRange()const;
    void clear();
    //读取文件
    bool readFile(const QString & name);
    //保存文件
    bool writeFile(const QString & name);

    void sort(const SpreadsheetCompare & compare);
};
class SpreadsheetCompare
{
public:
    bool operator()(const QStringList &list1, const QStringList &list2)const;
    enum{KeyCount=3};
    int keys[KeyCount];
    bool ascending[KeyCount];
};
#endif // SPREADSHEET_H
