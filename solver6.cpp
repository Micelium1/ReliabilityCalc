#include "solver6.h"
#include "ui_solver6.h"
#include "validatedcellwidget.h"

#include <QMessageBox>
Solver6::Solver6(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Solver6)
{
    ui->setupUi(this);
    ui->mainTable->setItemDelegateForColumn(0,new ValidatedCellWidget(ui->mainTable,true));
    ui->mainTable->setItemDelegateForColumn(1,new ValidatedCellWidget(ui->mainTable,true));
    ui->mainTable->setItemDelegateForColumn(2,new ValidatedCellWidget(ui->mainTable,true));
    connect(ui->addRangeButton,&QPushButton::clicked,this,&Solver6::addRangeButton_clicked);
    connect(ui->deleteRangeButton,&QPushButton::clicked,this,&Solver6::deleteRangeButton_clicked);
    connect(ui->mainTable,&QTableWidget::cellChanged,this,&Solver6::calculator);
}
void Solver6::addRangeButton_clicked()
{

    Average.append(0);
    Amounts.append(0);
    if (ui->mainTable->rowCount() == 0)
    {
        ui->mainTable->insertRow(0);
        ui->mainTable->setItem(0,0,new QTableWidgetItem("0"));
        ui->mainTable->setItem(0,1,new QTableWidgetItem("0"));

    }
    else
    {
        if (!ui->mainTable->item(ui->mainTable->rowCount()-1,1))
        {
            QMessageBox::warning(this,"Ошибка","Пожалуйста, заполните конец диапазона");
            return;
        }
        else
        {
            ui->mainTable->insertRow(ui->mainTable->rowCount());
            ui->mainTable->setItem(ui->mainTable->rowCount()-1,0,new QTableWidgetItem(*ui->mainTable->item(ui->mainTable->rowCount()-2,1)));
            ui->mainTable->setItem(ui->mainTable->rowCount()-1,1,new QTableWidgetItem(*ui->mainTable->item(ui->mainTable->rowCount()-2,1)));
        }
    }

}

void Solver6::deleteRangeButton_clicked()
{
    if (ui->mainTable->rowCount() == 0)
    {
        QMessageBox::warning(this,"Ошибка","Нечего удалять");
        return;
    }
    QList<QTableWidgetSelectionRange> selected = ui->mainTable->selectedRanges();
    if (selected.isEmpty() or selected[0].topRow() == ui->mainTable->rowCount()-1)
    {
        ui->mainTable->removeRow(ui->mainTable->rowCount()-1);
        Average.pop_back();
        Amounts.pop_back();
        return;
    }
    for (const QTableWidgetSelectionRange& Iterator:selected)
    {

        int top_row = Iterator.topRow();
        int bottom_row = Iterator.bottomRow();
        Average.remove(top_row,bottom_row-top_row+1);
        Amounts.remove(top_row,bottom_row-top_row+1);
        for(;bottom_row >= top_row;--bottom_row)
        {
            ui->mainTable->removeRow(bottom_row);

        }
        if(ui->mainTable->item(top_row,0)) ui->mainTable->item(top_row,0)->setText(ui->mainTable->item(top_row-1,1)->text());
        int row_count = ui->mainTable->rowCount();
        for(;top_row < row_count;++top_row)
        {
            calculator(top_row,-1);
        }
    }
}

void Solver6::calculator(int row,int column)
{
    if (column >2) return;
    if (column == 0)
    {
        if (ui->mainTable->item(row-1,1))
        {
            if (ui->mainTable->item(row,0) != ui->mainTable->item(row-1,1))
            {
                ui->mainTable->item(row-1,1)->setText(ui->mainTable->item(row,0)->text());
            }
        }
        if (ui->mainTable->item(row,1))
        {
            if (ui->mainTable->item(row,0)->text().replace(",",".").toFloat() > ui->mainTable->item(row,1)->text().replace(",",".").toFloat())
            {
                ui->mainTable->item(row,1)->setText(ui->mainTable->item(row,0)->text());
            }
        }
    }
    if (column == 1)
    {
        if (ui->mainTable->item(row,column)->text().replace(",",".").toFloat() < ui->mainTable->item(row,column-1)->text().replace(",",".").toFloat())
        {
            QMessageBox::warning(this,"Ошибка","Конец диапазона не может быть меньше начала");
            ui->mainTable->item(row,column)->setText(ui->mainTable->item(row,column-1)->text());

        }
        if(ui->mainTable->rowCount() > row + 1)
        {
            if (ui->mainTable->item(row+1,0)) ui->mainTable->setItem(row+1,0,new QTableWidgetItem(*ui->mainTable->item(row,1))); //item(row+1,0)->setText(ui->mainTable->item(row,column)->text());
            if (ui->mainTable->item(row+1,0)->text().replace(",",".").toFloat() < ui->mainTable->item(row+1,1)->text().replace(",",".").toFloat())
            {
                ui->mainTable->item(row+1,1)->setText(ui->mainTable->item(row+1,0)->text());
            }
        }
    }
    if (column == 2) Amounts[row] = ui->mainTable->item(row,2)->text().replace(",",".").toFloat();
    if(ui->mainTable->item(row,1) and ui->mainTable->item(row,0))Average[row] = Amounts[row]  * (ui->mainTable->item(row,1)->text().replace(",",".").toFloat() + ui->mainTable->item(row,0)->text().replace(",",".").toFloat())/2;

    float answer = 0;
    float amount = 0;
    for(const float& iterator:Average)
    {
        answer += iterator;
    }
    for(const float& iterator:Amounts)
    {
        amount += iterator;
    }
    if (amount == 0)
    {
        ui->answer->setText(QString("Ответ: "));
    }
    else
    {
        answer = answer / amount;
        ui->answer->setText(QString("Ответ: ") + QString::number(answer));
    }
}

Solver6::~Solver6()
{
    delete ui;
}
