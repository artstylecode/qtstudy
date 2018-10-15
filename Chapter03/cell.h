#ifndef CELL_H
#define CELL_H

#include <QTableWidgetItem>
class Cell : public QTableWidgetItem
{
public:
    Cell(QWidget *parent=0);
    Cell(int row, int col, QWidget *parent=0);
    QString formulaText;
    void setDirty();
    QString formula();
    void setFormula(const QString &text);
};

#endif // CELL_H
