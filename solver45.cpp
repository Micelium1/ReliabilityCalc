#include "solver45.h"
#include "ui_solver45.h"
#include "validatedcellwidget.h"

#include <QMessageBox>

Solver45::Solver45(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Solver45)
{
    ui->setupUi(this);
    ui->mainTable->setItemDelegateForColumn(0,new ValidatedCellWidget(ui->mainTable,true));
    connect(ui->addButton,&QPushButton::clicked,this,&Solver45::addRangeButton_clicked);
    connect(ui->deleteButton,&QPushButton::clicked,this,&Solver45::deleteRangeButton_clicked);
    connect(ui->mainTable,&QTableWidget::cellChanged,this,&Solver45::calculator);
}
void Solver45::addRangeButton_clicked()
{
    ui->mainTable->insertRow(ui->mainTable->rowCount());
}

void Solver45::deleteRangeButton_clicked()
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
        return;
    }
    for (const QTableWidgetSelectionRange& Iterator:selected)
    {

        int top_row = Iterator.topRow();
        int bottom_row = Iterator.bottomRow();
        for(;bottom_row >= top_row;--bottom_row)
        {
            ui->mainTable->removeRow(bottom_row);

        }
    }
}

void Solver45::calculator(int row,int column)
{
    float total = 0;
    int rowCount = ui->mainTable->rowCount();
    int empty = 0;
    for(int i = 0;i < rowCount;++i)
    {
        if (ui->mainTable->item(i,0)) total += ui->mainTable->item(i,0)->text().replace(",",".").toFloat();
        else ++empty;
    }
    ui->answer->setText(QString("Ответ: ") + QString::number(total/(rowCount-empty)));
}

Solver45::~Solver45()
{
    delete ui;
}
