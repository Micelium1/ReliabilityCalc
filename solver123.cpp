#include "solver123.h"
#include "ui_solver123.h"
#include "QMessageBox"

Solver123::Solver123(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Solver123)
{
    ui->setupUi(this);
    connect(ui->startingAmountInput,&QLineEdit::textChanged,this,&Solver123::currentAmountChanger);
    connect(ui->addRangeButton,&QPushButton::clicked,this,&Solver123::addRangeButton_clicked);
    connect(ui->deleteRangeButton,&QPushButton::clicked,this,&Solver123::deleteRangeButton_clicked);
}

void Solver123::currentAmountChanger()
{
    starting_amount = ui->startingAmountInput->text().toInt();
}
void Solver123::addRangeButton_clicked()
{
    ui->mainTable->insertRow(ui->mainTable->rowCount());
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
        return;
    }
    for (const QTableWidgetSelectionRange& Iterator:selected)
    {
        for(int bottom_row = Iterator.bottomRow(), top_row = Iterator.topRow();bottom_row >= top_row;--bottom_row)
        {
            ui->mainTable->removeRow(bottom_row);
        }
    }
}

void Solver123::calculator(int row,int column)
{
    float range_start = ui->mainTable->item(row,1)->text().replace(",",".").toFloat();
    float range_end = ui->mainTable->item(row,1)->text().replace(",",".").toFloat();
    float amount_of_failed_products = ui->mainTable->item(row,1)->text().replace(",",".").toFloat();

    ui->mainTable->setItem(row,3,new QTableWidgetItem(QString::number(probabilityCalc(range_start,range_end,amount_of_failed_products))));
    ui->mainTable->setItem(row,4,new QTableWidgetItem(QString::number(2)));
    ui->mainTable->setItem(row,5,new QTableWidgetItem(QString::number(3)));
}

float Solver123::probabilityCalc(float range_start,float range_end,int amount_of_failed_products)
{
    return 1;
}

Solver123::~Solver123()
{
    delete ui;
}
