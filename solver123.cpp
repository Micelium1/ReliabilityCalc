#include "solver123.h"
#include "ui_solver123.h"

Solver123::Solver123(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Solver123)
{
    ui->setupUi(this);
    connect(ui->startingAmountInput,&QLineEdit::textChanged,this,&Solver123::currentAmountChanger);
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
    ui->mainTable->removeRow(ui->mainTable->rowCount());
}

Solver123::~Solver123()
{
    delete ui;
}
