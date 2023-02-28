#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui/qopengl.h>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_recursionSelect_valueChanged(int arg1);

    void on_angleSelect_valueChanged(double arg1);

    void on_cangleSelect_valueChanged(double arg1);

    void on_lengthSelect_valueChanged(double arg1);

    void on_clengthSelect_valueChanged(double arg1);

    void on_widthSelect_valueChanged(double arg1);

    void on_cwidthSelect_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
