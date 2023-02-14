#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui/qopengl.h>

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
    void on_primitivePicker_currentTextChanged(const QString &arg1);

private:
    void initPrimitives();

    QMap<QString, GLenum> primitiveTypes;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
