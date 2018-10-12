#include "spreadsheet.h"
#include "cell.h"
#include <QtGui>

QString SpreadSheet::text(int row, int col)const
{

}
QString SpreadSheet::formula(int row, int col)const
{

}
void SpreadSheet::setFormula(int row, int col)
{

}

SpreadSheet::SpreadSheet(QWidget *parent)
{
    autoRecalc = true;
    setItemPrototype(new Cell);
    setSelectionMode(ContiguousSelection);
    connect(this, SIGNAL(itemChanged(QTableWidgetItem*)), this,SLOT(somethingChanged()));
    clear();
}
//是否自动公式重新计算
bool SpreadSheet::autoRecalculate()const
{
    return autoRecalc;
}
//获取当前位置信息
QString SpreadSheet::currentLocation()const
{
    return "";
}
//获取当前单元格公式
QString SpreadSheet::currentFormula()const
{
    return "";
}
//获取当前选中区域
QTableWidgetSelectionRange SpreadSheet::selectedRange()const
{

}
void SpreadSheet::clear()
{
    setRowCount(0);
    setColumnCount(0);
    setRowCount(RowCount);
    setColumnCount(ColumnCount);
    for(int i =0;i < ColumnCount;i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        item -> setText(QString(QChar('A' + i)));
        //设置第一行项
        setHorizontalHeaderItem(i,item);
    }
    setCurrentCell(0,0);
}
//读取文件
bool SpreadSheet::readFile(QString * name)
{

}
//保存文件
bool SpreadSheet::writeFile(QString * name)
{

}
//排序
void sort(const SpreadsheetCompare & compare)
{

}
//slots;

 void SpreadSheet::somethingChanged()
 {

 }


