#include "solver6.h"
#include "ui_solver6.h"

Solver6::Solver6(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Solver6)
{
    ui->setupUi(this);
}

Solver6::~Solver6()
{
    delete ui;
}
