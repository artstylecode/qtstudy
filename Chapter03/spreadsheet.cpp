
#include "cell.h"
#include <QtGui>
#include<QFile>
#include <QDataStream>
#include "spreadsheet.h"
QString Spreadsheet::text(int row, int col)const
{
    Cell *cell = new Cell(row, col);
    if(cell)
    {
       return cell->text();
    }
    else
    {
        return "";
    }

}
Cell *Spreadsheet::cell(int row, int columnn) const
{
    QTableWidgetItem * temp = item(row, columnn);
    return static_cast<Cell*>(temp);
}
QString Spreadsheet::formula(int row, int col)const
{
    Cell *c = cell(row, col);
    if(c)
    {
        return c-> formula();
    }
    else
    {
        return "";
    }

}
void Spreadsheet::setFormula(int row, int col, const QString &text)
{
    Cell *cell = new Cell(row, col);
    if(cell)
    {
        setItem(row, col, cell);
    }
    cell ->setFormula(text);
}

Spreadsheet::Spreadsheet(QWidget *parent)
{

    autoRecalc = true;
    setItemPrototype(new Cell);
    setSelectionMode(ContiguousSelection);
    connect(this, SIGNAL(itemChanged(QTableWidgetItem*)), this,SLOT(somethingChanged()));
    clear();
}
//是否自动公式重新计算
bool Spreadsheet::autoRecalculate()const
{
    return autoRecalc;
}
//获取当前位置信息
QString Spreadsheet::currentLocation()const
{
    return  QChar('A' + currentColumn()) +
            QString::number(currentRow()+1);
}
//获取当前单元格公式
QString Spreadsheet::currentFormula()const
{
    return formula(currentRow(), currentColumn());
}
//获取当前选中区域
QTableWidgetSelectionRange Spreadsheet::selectedRange()const
{
    QList<QTableWidgetSelectionRange> ranges = selectedRanges();
    if(ranges.isEmpty())
    {
        return QTableWidgetSelectionRange();
    }
    return ranges.first();
}
void Spreadsheet::clear()
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
bool Spreadsheet::readFile(const QString & name)
{
    QFile file(name);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, tr("Spread sheet!"), tr("Cannot Read File %1\nerror:%2")
                             .arg(name).arg(file.errorString()));
        return false;
    }else
    {
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_4_8);
        quint32 magic;

        in >> magic;
         qDebug()<<"magic:"<<magic;
        if(magic!=quint32(MagicNumber))
        {
            QMessageBox::warning(this, tr("Spread sheet!"), tr("this is not spreadsheet file\n"));
            return false;
        }
        quint16 row;
        quint16 column;
        QString str;
        QApplication::setOverrideCursor(Qt::WaitCursor);
        while(!in.atEnd())
        {

            in >> row>>column >>str;
            qDebug()<<row<<column<<str;
            setFormula(row, column, str);
        }
        QApplication::restoreOverrideCursor();


    }
}
//保存文件
bool Spreadsheet::writeFile(const QString & name)
{
    QFile file(name);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, tr("Spread sheet!"), tr("Cannot Write File %1\nerror:%2")
                             .arg(name).arg(file.errorString()));
        return false;
    }else
    {
         QDataStream out(&file);
         out.setVersion(QDataStream::Qt_4_8);
         QApplication::setOverrideCursor(Qt::WaitCursor);
         out << quint32(MagicNumber);
         for(int row =0;row < RowCount;row++)
         {
             for(int column=0;column<ColumnCount;column++)
             {
                 QString str = formula(row, column);
                 if(!str.isEmpty())
                 {
                     out << quint16(row) << quint16(column) << str;
                     qDebug()<<quint16(row) << quint16(column) << str;
                 }

             }
         }

         file.close();
         QApplication::restoreOverrideCursor();
         return true;
    }
}
//排序
void Spreadsheet::sort(const SpreadsheetCompare & compare)
{

}

void Spreadsheet::recalculate()
{
    for(int row=0;row <RowCount;row++)
    {
        for(int column =0;column < ColumnCount;column++)
        {
            Cell * c = cell(row, column);
            if(c)
            {
                c ->setDirty();
            }
        }
    }
    viewport() ->update();
}
//slots;

 void Spreadsheet::somethingChanged()
 {
     if(autoRecalc)
     {
         recalculate();
     }
    emit modified();
 }
 void  Spreadsheet::cut()
 {
     copy();
     del();
 }
 void  Spreadsheet::copy()
 {
     QTableWidgetSelectionRange range = selectedRange();
     QString str;
     for(int i =0;i < range.rowCount();i++)
     {
         if(i>0)
            str+="\n";
         for(int j =0;j <range.columnCount();j++)
         {
              if(j>0)
                str+="\t";
             str += formula(range.topRow()+i, range.leftColumn()+j);
         }

     }
     QApplication::clipboard() -> setText(str);
 }
 void  Spreadsheet::del()
 {
     QList<QTableWidgetItem *> items = selectedItems();
     if(!items.isEmpty())
     {
         foreach(QTableWidgetItem *item, items)
             delete item;
         somethingChanged();
     }
    somethingChanged();
 }
 void  Spreadsheet::paste()
 {
    QTableWidgetSelectionRange range = selectedRange();
    QString str = QApplication::clipboard() ->text();
    QStringList rows = str.split("\n");
    int numRows = rows.count();
    int numCols = rows.first().count("\t") + 1;

    if(range.rowCount() * range.columnCount() !=1&&(range.rowCount()!=numRows || range.columnCount() != numCols))
    {
        QMessageBox::information(this, tr("Spread Sheet"), tr("The information can't be pasted because "
                                                              "the copy and paste areas arean't the same size"));
        return;
    }
    for(int i =0;i <numRows;i++)
    {
        QStringList columns = rows[i].split("\t");
        for(int j =0;j < numCols;j++)
        {
            int row = range.topRow()+i;
            int col = range.leftColumn()+j;
            setFormula(row, col, columns[j]);
        }
    }
    somethingChanged();
 }
 void Spreadsheet::selectCurrentRow()
 {
     selectRow(currentRow());
 }
 void Spreadsheet::selectCurrentColumn()
 {
     selectColumn(currentColumn());
 }

 void Spreadsheet::findNext(QString &str, Qt::CaseSensitivity cs)
 {
     qDebug()<<"findnext\n";
     int row = currentRow();
     int col = currentColumn() + 1;
     while(row< RowCount)
     {
         while(col < ColumnCount)
         {
             qDebug()<<"text:"<<text(row, col);
             clearSelection();
            setCurrentCell(row, col);
            activateWindow();
            return;
             if(text(row, col).contains(str,cs))
             {
                 clearSelection();
                setCurrentCell(row, col);
                activateWindow();
                return;
             }
             col++;
         }
         row++;
     }
 }


 void Spreadsheet::findPrevious( QString &str, Qt::CaseSensitivity cs)
 {

     qDebug()<<"findPrevious\n";
     int row = currentRow();
     int col = currentColumn() - 1;

     while(row>0)
     {
         while(col>0)
         {
             if(text(row,col).contains(str,cs))
             {
                 clearSelection();
                 setCurrentCell(row, col);
             }
             col--;
         }
         row--;
     }

 }

 void Spreadsheet::goToCell(QString cellstr)
 {
     /*QChar col = cellstr.at(0);
     int col = col -'A';
     int row = cellstr.mid(1).toInt();
     qDebug()<<"column:"<<col<<"\nrow:"<<row;*/

 }
