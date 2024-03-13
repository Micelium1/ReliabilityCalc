#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "solver123.h"
#include "solver45.h"
#include "solver6.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Solver123Button,&QPushButton::clicked,this,&MainWindow::on_Solver123Button_press);
    connect(ui->Solver45Button,&QPushButton::clicked,this,&MainWindow::on_Solver45Button_press);
    connect(ui->Solver6Button,&QPushButton::clicked,this,&MainWindow::on_Solver6Button_press);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_Solver123Button_press()
{
    hide();
    Solver123 Window;
    Window.exec();
    show();
}
void MainWindow::on_Solver45Button_press()
{
    hide();
    Solver45 Window;
    Window.exec();
    show();
}
void MainWindow::on_Solver6Button_press()
{
    hide();
    Solver6 Window;
    Window.exec();
    show();
}

