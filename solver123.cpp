#include "solver123.h"
#include "ui_solver123.h"

Solver123::Solver123(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Solver123)
{
    ui->setupUi(this);
}

Solver123::~Solver123()
{
    delete ui;
}
