/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *Browse;
    QPushButton *train;
    QPushButton *recognize;
    QPushButton *rocCurve;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLabel *faceName;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *input;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(30, 110, 91, 151));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Browse = new QPushButton(layoutWidget);
        Browse->setObjectName("Browse");

        verticalLayout->addWidget(Browse);

        train = new QPushButton(layoutWidget);
        train->setObjectName("train");

        verticalLayout->addWidget(train);

        recognize = new QPushButton(layoutWidget);
        recognize->setObjectName("recognize");

        verticalLayout->addWidget(recognize);

        rocCurve = new QPushButton(layoutWidget);
        rocCurve->setObjectName("rocCurve");

        verticalLayout->addWidget(rocCurve);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(170, 490, 601, 41));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName("label_2");
        label_2->setMaximumSize(QSize(16777215, 50));

        horizontalLayout->addWidget(label_2, 0, Qt::AlignHCenter);

        faceName = new QLabel(layoutWidget1);
        faceName->setObjectName("faceName");
        faceName->setMaximumSize(QSize(16777215, 50));

        horizontalLayout->addWidget(faceName, 0, Qt::AlignLeft);

        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(170, 30, 601, 451));
        verticalLayout_2 = new QVBoxLayout(layoutWidget2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget2);
        label->setObjectName("label");
        label->setMaximumSize(QSize(16777215, 50));

        verticalLayout_2->addWidget(label, 0, Qt::AlignHCenter);

        input = new QLabel(layoutWidget2);
        input->setObjectName("input");

        verticalLayout_2->addWidget(input, 0, Qt::AlignHCenter);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Browse->setText(QCoreApplication::translate("MainWindow", "Browse", nullptr));
        train->setText(QCoreApplication::translate("MainWindow", "Train", nullptr));
        recognize->setText(QCoreApplication::translate("MainWindow", "Recognize", nullptr));
        rocCurve->setText(QCoreApplication::translate("MainWindow", "ROC ", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Face:", nullptr));
        faceName->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "Input Face", nullptr));
        input->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
