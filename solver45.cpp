#include "solver45.h"
#include "ui_solver45.h"

Solver45::Solver45(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Solver45)
{
    ui->setupUi(this);
}

Solver45::~Solver45()
{
    delete ui;
}
