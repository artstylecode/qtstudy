#ifndef SPREADSHEET_H
#define SPREADSHEET_H
#include <QTableWidget>
class Cell;
class SpreadsheetCompare;
class SpreadSheet :public QTableWidget
{
private slots:
    void somethingChanged();
private:
    enum {MagicNumber=0x7F51C883,RowCount=999,ColumnCount=26};
    Cell *cell;
    QString text(int row, int col)const;
    QString formula(int row, int col)const;
    void setFormula(int row, int col);
    bool autoRecalc;

    Q_OBJECT
public:
    SpreadSheet(QWidget * parent =0);
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
    bool readFile(QString * name);
    //保存文件
    bool writeFile(QString * name);

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
