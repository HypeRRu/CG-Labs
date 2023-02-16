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
    void on_alphaPicker_currentTextChanged(const QString &arg1);
    void on_alphaSlider_valueChanged(int value);
    void on_sfactorPicker_currentTextChanged(const QString &arg1);
    void on_dfactorPicker_currentTextChanged(const QString &arg1);
    void on_scissorXSlider_valueChanged(int value);
    void on_scissorYSlider_valueChanged(int value);
    void on_scissorWSlider_valueChanged(int value);
    void on_scissorHSlider_valueChanged(int value);
private:
    void initPrimitives();
    void initAlphaTest();
    void initBlendTest();
    void initScissorTest();

    QMap<QString, GLenum> primitiveTypes;
    QMap<QString, GLenum> alphaTestModes;
    QMap<QString, GLenum> sblendTestModes;
    QMap<QString, GLenum> dblendTestModes;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
