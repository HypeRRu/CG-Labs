#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->verticalLayout->setAlignment(Qt::AlignTop);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_recursionSelect_valueChanged(int arg1)
{
    ui->glWindow->setRecursionDepth(arg1);
}

void MainWindow::on_angleSelect_valueChanged(double arg1)
{
    ui->glWindow->setStartAngle(arg1);
}

void MainWindow::on_cangleSelect_valueChanged(double arg1)
{
    ui->glWindow->setAngleChangeCoefficient(arg1);
}


void MainWindow::on_lengthSelect_valueChanged(double arg1)
{
    ui->glWindow->setStartLength(arg1);
}


void MainWindow::on_clengthSelect_valueChanged(double arg1)
{
    ui->glWindow->setLengthChangeCoefficient(arg1);
}


void MainWindow::on_widthSelect_valueChanged(double arg1)
{
    ui->glWindow->setStartWidth(arg1);
}


void MainWindow::on_cwidthSelect_valueChanged(double arg1)
{
    ui->glWindow->setWidthChangeCoefficient(arg1);
}

