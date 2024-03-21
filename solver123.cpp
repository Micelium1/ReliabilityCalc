#include "solver123.h"
#include "ui_solver123.h"
#include "QMessageBox"
#include "validatedcellwidget.h"

Solver123::Solver123(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Solver123)
{
    ui->setupUi(this);
    ui->startingAmountInput->setValidator(new QDoubleValidator(0,INFINITY,-1,ui->startingAmountInput));
    ui->mainTable->setItemDelegateForColumn(0,new ValidatedCellWidget(ui->mainTable,true));
    ui->mainTable->setItemDelegateForColumn(1,new ValidatedCellWidget(ui->mainTable,true));
    ui->mainTable->setItemDelegateForColumn(2,new ValidatedCellWidget(ui->mainTable,true));
    ui->mainTable->setItemDelegateForColumn(3,new ValidatedCellWidget(ui->mainTable));
    ui->mainTable->setItemDelegateForColumn(4,new ValidatedCellWidget(ui->mainTable));
    ui->mainTable->setItemDelegateForColumn(5,new ValidatedCellWidget(ui->mainTable));
    connect(ui->startingAmountInput,&QLineEdit::textChanged,this,&Solver123::startingAmountChanger);
    connect(ui->addRangeButton,&QPushButton::clicked,this,&Solver123::addRangeButton_clicked);
    connect(ui->deleteRangeButton,&QPushButton::clicked,this,&Solver123::deleteRangeButton_clicked);
    connect(ui->mainTable,&QTableWidget::cellChanged,this,&Solver123::calculator);
}

void Solver123::startingAmountChanger()
{
    starting_amount = ui->startingAmountInput->text().toFloat();
    for (int i = ui->mainTable->rowCount()-1;i >= 0;--i)
    {
        calculator(i,-1);
    }
}
void Solver123::addRangeButton_clicked()
{


    if (ui->mainTable->rowCount() == 0)
    {
        ui->mainTable->insertRow(0);
        failedProducts.append(0);
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
            failedProducts.append(0);
            ui->mainTable->setItem(ui->mainTable->rowCount()-1,0,new QTableWidgetItem(*ui->mainTable->item(ui->mainTable->rowCount()-2,1)));
            ui->mainTable->setItem(ui->mainTable->rowCount()-1,1,new QTableWidgetItem(*ui->mainTable->item(ui->mainTable->rowCount()-2,1)));
        }
    }

}

void Solver123::deleteRangeButton_clicked()
{
    if (ui->mainTable->rowCount() == 0)
    {
        QMessageBox::warning(this,"Ошибка","Нечего удалять");
        return;
    }
    QList<QTableWidgetSelectionRange> selected = ui->mainTable->selectedRanges();
    if (selected.isEmpty())
    {
        ui->mainTable->removeRow(ui->mainTable->rowCount()-1);
        failedProducts.pop_back();
        return;
    }
    for (const QTableWidgetSelectionRange& Iterator:selected)
    {

        int top_row = Iterator.topRow();
        int bottom_row = Iterator.bottomRow();
        failedProducts.remove(top_row,bottom_row-top_row+1);

        for(;bottom_row >= top_row;--bottom_row)
        {
            ui->mainTable->removeRow(bottom_row);
        }
        ui->mainTable->item(top_row,0)->setText(ui->mainTable->item(top_row-1,1)->text());
        int row_count = ui->mainTable->rowCount();
        for(;top_row < row_count;++top_row)
        {
            calculator(top_row,-1);
        }
    }
}

void Solver123::calculator(int row,int column)
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
    if (column == 2) failedProducts[row] = ui->mainTable->item(row,2)->text().replace(",",".").toFloat();
    QTableWidgetItem* item = new QTableWidgetItem(QString::number(probabilityCalc(row)));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    QBrush brush =QBrush(QColor(240,240,240));
    item->setBackground(brush);
    ui->mainTable->setItem(row,3,item);
    item = new QTableWidgetItem(QString::number(frequencyEstimation(row)));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    item->setBackground(brush);
    ui->mainTable->setItem(row,4,item);
    item = new QTableWidgetItem(QString::number(failureRateCalc(row)));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    item->setBackground(brush);
    ui->mainTable->setItem(row,5,item);
}

float Solver123::probabilityCalc(int row)
{
    float failed_sum = 0;
    for(int i = 0;i <= row;++i)
    {
        failed_sum += failedProducts[i];
    }
    return (starting_amount - failed_sum)/starting_amount;
}
float Solver123::failureRateCalc(int row)
{
    float failed_sum = 0;
    for(int i = 0;i < row;++i)
    {
        failed_sum += failedProducts[i];
    }
    float n = starting_amount - failed_sum;
    float delta = failedProducts[row];
    if (ui->mainTable->item(row,1) == nullptr or ui->mainTable->item(row,0) == nullptr)
    {
        return 0;
    }
    float range = ui->mainTable->item(row,1)->text().replace(",",".").toFloat() - ui->mainTable->item(row,0)->text().replace(",",".").toFloat();
    return delta/(range * n);
}
float Solver123::frequencyEstimation(int row)
{
    if (ui->mainTable->item(row,1) == nullptr or ui->mainTable->item(row,0) == nullptr) return 0;
    float range =ui->mainTable->item(row,1)->text().replace(",",".").toFloat() - ui->mainTable->item(row,0)->text().replace(",",".").toFloat();
    return failedProducts[row] / (starting_amount * range);
}
Solver123::~Solver123()
{
    delete ui;
}
