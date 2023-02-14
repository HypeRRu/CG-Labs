#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initPrimitives();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initPrimitives()
{
    primitiveTypes.insert("GL_POINTS", GL_POINTS);
    primitiveTypes.insert("GL_LINES", GL_LINES);
    primitiveTypes.insert("GL_LINE_STRIP", GL_LINE_STRIP);
    primitiveTypes.insert("GL_LINE_LOOP", GL_LINE_LOOP);
    primitiveTypes.insert("GL_TRIANGLES", GL_TRIANGLES);
    primitiveTypes.insert("GL_TRIANGLE_STRIP", GL_TRIANGLE_STRIP);
    primitiveTypes.insert("GL_TRIANGLE_FAN", GL_TRIANGLE_FAN);
    primitiveTypes.insert("GL_QUADS", GL_QUADS);
    primitiveTypes.insert("GL_QUAD_STRIP", GL_QUAD_STRIP);
    primitiveTypes.insert("GL_POLYGON", GL_POLYGON);

    ui->primitivePicker->addItems(primitiveTypes.keys());
    ui->primitivePicker->setCurrentText("GL_POINTS");
}

void MainWindow::on_primitivePicker_currentTextChanged(const QString &arg1)
{
    ui->glWindow->setPrimitiveMode(primitiveTypes.value(arg1));
}
