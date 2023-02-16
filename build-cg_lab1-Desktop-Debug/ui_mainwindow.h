/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <glscene.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    GLScene *glWindow;
    QVBoxLayout *verticalLayout;
    QLabel *primitiveLabel;
    QComboBox *primitivePicker;
    QFrame *line;
    QLabel *alphaLabel;
    QComboBox *alphaPicker;
    QSlider *alphaSlider;
    QFrame *line_2;
    QLabel *blendLabel;
    QLabel *sfactorLabel;
    QComboBox *sfactorPicker;
    QLabel *dfactorLabel;
    QComboBox *dfactorPicker;
    QFrame *line_3;
    QLabel *scissorLabel;
    QLabel *scissorXLabel;
    QSlider *scissorXSlider;
    QLabel *scissorYLabel;
    QSlider *scissorYSlider;
    QLabel *scissorWLabel;
    QSlider *scissorWSlider;
    QLabel *scissorHLabel;
    QSlider *scissorHSlider;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        glWindow = new GLScene(centralwidget);
        glWindow->setObjectName("glWindow");
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(glWindow->sizePolicy().hasHeightForWidth());
        glWindow->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(glWindow);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        primitiveLabel = new QLabel(centralwidget);
        primitiveLabel->setObjectName("primitiveLabel");
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(primitiveLabel->sizePolicy().hasHeightForWidth());
        primitiveLabel->setSizePolicy(sizePolicy1);
        primitiveLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(primitiveLabel);

        primitivePicker = new QComboBox(centralwidget);
        primitivePicker->setObjectName("primitivePicker");

        verticalLayout->addWidget(primitivePicker);

        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        alphaLabel = new QLabel(centralwidget);
        alphaLabel->setObjectName("alphaLabel");
        sizePolicy1.setHeightForWidth(alphaLabel->sizePolicy().hasHeightForWidth());
        alphaLabel->setSizePolicy(sizePolicy1);
        alphaLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(alphaLabel);

        alphaPicker = new QComboBox(centralwidget);
        alphaPicker->setObjectName("alphaPicker");

        verticalLayout->addWidget(alphaPicker);

        alphaSlider = new QSlider(centralwidget);
        alphaSlider->setObjectName("alphaSlider");
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(alphaSlider->sizePolicy().hasHeightForWidth());
        alphaSlider->setSizePolicy(sizePolicy2);
        alphaSlider->setMaximum(100);
        alphaSlider->setValue(50);
        alphaSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(alphaSlider);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        blendLabel = new QLabel(centralwidget);
        blendLabel->setObjectName("blendLabel");
        sizePolicy1.setHeightForWidth(blendLabel->sizePolicy().hasHeightForWidth());
        blendLabel->setSizePolicy(sizePolicy1);
        blendLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(blendLabel);

        sfactorLabel = new QLabel(centralwidget);
        sfactorLabel->setObjectName("sfactorLabel");
        sizePolicy1.setHeightForWidth(sfactorLabel->sizePolicy().hasHeightForWidth());
        sfactorLabel->setSizePolicy(sizePolicy1);
        sfactorLabel->setLayoutDirection(Qt::LeftToRight);
        sfactorLabel->setAutoFillBackground(false);
        sfactorLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(sfactorLabel);

        sfactorPicker = new QComboBox(centralwidget);
        sfactorPicker->setObjectName("sfactorPicker");

        verticalLayout->addWidget(sfactorPicker);

        dfactorLabel = new QLabel(centralwidget);
        dfactorLabel->setObjectName("dfactorLabel");
        sizePolicy1.setHeightForWidth(dfactorLabel->sizePolicy().hasHeightForWidth());
        dfactorLabel->setSizePolicy(sizePolicy1);
        dfactorLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(dfactorLabel);

        dfactorPicker = new QComboBox(centralwidget);
        dfactorPicker->setObjectName("dfactorPicker");

        verticalLayout->addWidget(dfactorPicker);

        line_3 = new QFrame(centralwidget);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        scissorLabel = new QLabel(centralwidget);
        scissorLabel->setObjectName("scissorLabel");
        sizePolicy1.setHeightForWidth(scissorLabel->sizePolicy().hasHeightForWidth());
        scissorLabel->setSizePolicy(sizePolicy1);
        scissorLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(scissorLabel);

        scissorXLabel = new QLabel(centralwidget);
        scissorXLabel->setObjectName("scissorXLabel");
        sizePolicy1.setHeightForWidth(scissorXLabel->sizePolicy().hasHeightForWidth());
        scissorXLabel->setSizePolicy(sizePolicy1);
        scissorXLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(scissorXLabel);

        scissorXSlider = new QSlider(centralwidget);
        scissorXSlider->setObjectName("scissorXSlider");
        sizePolicy2.setHeightForWidth(scissorXSlider->sizePolicy().hasHeightForWidth());
        scissorXSlider->setSizePolicy(sizePolicy2);
        scissorXSlider->setMaximum(100);
        scissorXSlider->setSingleStep(0);
        scissorXSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(scissorXSlider);

        scissorYLabel = new QLabel(centralwidget);
        scissorYLabel->setObjectName("scissorYLabel");
        sizePolicy1.setHeightForWidth(scissorYLabel->sizePolicy().hasHeightForWidth());
        scissorYLabel->setSizePolicy(sizePolicy1);
        scissorYLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(scissorYLabel);

        scissorYSlider = new QSlider(centralwidget);
        scissorYSlider->setObjectName("scissorYSlider");
        sizePolicy2.setHeightForWidth(scissorYSlider->sizePolicy().hasHeightForWidth());
        scissorYSlider->setSizePolicy(sizePolicy2);
        scissorYSlider->setMaximum(100);
        scissorYSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(scissorYSlider);

        scissorWLabel = new QLabel(centralwidget);
        scissorWLabel->setObjectName("scissorWLabel");
        sizePolicy1.setHeightForWidth(scissorWLabel->sizePolicy().hasHeightForWidth());
        scissorWLabel->setSizePolicy(sizePolicy1);
        scissorWLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(scissorWLabel);

        scissorWSlider = new QSlider(centralwidget);
        scissorWSlider->setObjectName("scissorWSlider");
        sizePolicy2.setHeightForWidth(scissorWSlider->sizePolicy().hasHeightForWidth());
        scissorWSlider->setSizePolicy(sizePolicy2);
        scissorWSlider->setMaximum(100);
        scissorWSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(scissorWSlider);

        scissorHLabel = new QLabel(centralwidget);
        scissorHLabel->setObjectName("scissorHLabel");
        sizePolicy1.setHeightForWidth(scissorHLabel->sizePolicy().hasHeightForWidth());
        scissorHLabel->setSizePolicy(sizePolicy1);
        scissorHLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(scissorHLabel);

        scissorHSlider = new QSlider(centralwidget);
        scissorHSlider->setObjectName("scissorHSlider");
        sizePolicy2.setHeightForWidth(scissorHSlider->sizePolicy().hasHeightForWidth());
        scissorHSlider->setSizePolicy(sizePolicy2);
        scissorHSlider->setMaximum(100);
        scissorHSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(scissorHSlider);


        horizontalLayout->addLayout(verticalLayout);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        primitiveLabel->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\270\320\274\320\270\321\202\320\270\320\262", nullptr));
        alphaLabel->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\321\201\321\202 \320\260\320\273\321\214\321\204\320\260-\320\272\320\260\320\275\320\260\320\273\320\260", nullptr));
        blendLabel->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\321\201\321\202 \321\201\320\274\320\265\321\210\320\265\320\275\320\270\321\217 \321\206\320\262\320\265\321\202\320\276\320\262", nullptr));
        sfactorLabel->setText(QCoreApplication::translate("MainWindow", "sFactor", nullptr));
        dfactorLabel->setText(QCoreApplication::translate("MainWindow", "dFactor", nullptr));
        scissorLabel->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\321\201\321\202 \320\276\321\202\321\201\320\265\321\207\320\265\320\275\320\270\321\217", nullptr));
        scissorXLabel->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        scissorYLabel->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        scissorWLabel->setText(QCoreApplication::translate("MainWindow", "W", nullptr));
        scissorHLabel->setText(QCoreApplication::translate("MainWindow", "H", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
