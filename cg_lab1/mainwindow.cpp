#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->verticalLayout->setAlignment(Qt::AlignTop);

    initPrimitives();
    initAlphaTest();
    initBlendTest();
    initScissorTest();
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

void MainWindow::initAlphaTest()
{
    alphaTestModes.insert("GL_NEVER", GL_NEVER);
    alphaTestModes.insert("GL_LESS", GL_LESS);
    alphaTestModes.insert("GL_EQUAL", GL_EQUAL);
    alphaTestModes.insert("GL_LEQUAL", GL_LEQUAL);
    alphaTestModes.insert("GL_GREATER", GL_GREATER);
    alphaTestModes.insert("GL_NOTEQUAL", GL_NOTEQUAL);
    alphaTestModes.insert("GL_GEQUAL", GL_GEQUAL);
    alphaTestModes.insert("GL_ALWAYS", GL_ALWAYS);

    ui->alphaPicker->addItems(alphaTestModes.keys());
    ui->alphaPicker->setCurrentText("GL_ALWAYS");
    ui->alphaSlider->setSliderPosition(50);
}

void MainWindow::initBlendTest()
{
    sblendTestModes.insert("GL_ZERO", GL_ZERO);
    sblendTestModes.insert("GL_ONE", GL_ONE);
    sblendTestModes.insert("GL_DST_COLOR", GL_DST_COLOR);
    sblendTestModes.insert("GL_ONE_MINUS_DST_COLOR", GL_ONE_MINUS_DST_COLOR);
    sblendTestModes.insert("GL_SRC_ALPHA", GL_SRC_ALPHA);
    sblendTestModes.insert("GL_ONE_MINUS_SRC_ALPHA", GL_ONE_MINUS_SRC_ALPHA);
    sblendTestModes.insert("GL_DST_ALPHA", GL_DST_ALPHA);
    sblendTestModes.insert("GL_ONE_MINUS_DST_ALPHA", GL_ONE_MINUS_DST_ALPHA);
    sblendTestModes.insert("GL_SRC_ALPHA_SATURATE", GL_SRC_ALPHA_SATURATE);

    dblendTestModes.insert("GL_ZERO", GL_ZERO);
    dblendTestModes.insert("GL_ONE", GL_ONE);
    dblendTestModes.insert("GL_SRC_COLOR", GL_SRC_COLOR);
    dblendTestModes.insert("GL_ONE_MINUS_SRC_COLOR", GL_ONE_MINUS_SRC_COLOR);
    dblendTestModes.insert("GL_SRC_ALPHA", GL_SRC_ALPHA);
    dblendTestModes.insert("GL_ONE_MINUS_SRC_ALPHA", GL_ONE_MINUS_SRC_ALPHA);
    dblendTestModes.insert("GL_DST_ALPHA", GL_DST_ALPHA);
    dblendTestModes.insert("GL_ONE_MINUS_DST_ALPHA", GL_ONE_MINUS_DST_ALPHA);

    ui->sfactorPicker->addItems(sblendTestModes.keys());
    ui->sfactorPicker->setCurrentText("GL_ONE");

    ui->dfactorPicker->addItems(dblendTestModes.keys());
    ui->dfactorPicker->setCurrentText("GL_ZERO");
}

void MainWindow::initScissorTest()
{
    ui->scissorXSlider->setSliderPosition(0);
    ui->scissorYSlider->setSliderPosition(0);
    ui->scissorHSlider->setSliderPosition(100);
    ui->scissorWSlider->setSliderPosition(100);
}

void MainWindow::on_primitivePicker_currentTextChanged(const QString &arg1)
{
    ui->glWindow->setPrimitiveMode(primitiveTypes.value(arg1));
}

void MainWindow::on_alphaPicker_currentTextChanged(const QString &arg1)
{
    ui->glWindow->setAlphaTestMode(alphaTestModes.value(arg1));
}

void MainWindow::on_alphaSlider_valueChanged(int value)
{
    ui->glWindow->setAlphaRef(value / 100.f);
}

void MainWindow::on_sfactorPicker_currentTextChanged(const QString &arg1)
{
    ui->glWindow->setBlendSFactor(sblendTestModes.value(arg1));
}

void MainWindow::on_dfactorPicker_currentTextChanged(const QString &arg1)
{
    ui->glWindow->setBlendDFactor(dblendTestModes.value(arg1));
}

void MainWindow::on_scissorXSlider_valueChanged(int value)
{
    ui->glWindow->setScissorXRate(value / 100.f);
}

void MainWindow::on_scissorYSlider_valueChanged(int value)
{
    ui->glWindow->setScissorYRate(value / 100.f);
}

void MainWindow::on_scissorWSlider_valueChanged(int value)
{
    ui->glWindow->setScissorWRate(value / 100.f);
}

void MainWindow::on_scissorHSlider_valueChanged(int value)
{
    ui->glWindow->setScissorHRate(value / 100.f);
}
