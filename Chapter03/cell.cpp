#include "cell.h"
#include <QDebug>

Cell::Cell(QWidget *parent)
{

}
Cell::Cell(int row, int col, QWidget *parent)
{

}

void Cell::setDirty()
{
    qDebug()<<"setDirty\n";
}
QString Cell::formula()
{
    return "formulaText";
}

void Cell::setFormula(const QString &text)
{
    formulaText = text;
    setText(text);
}
