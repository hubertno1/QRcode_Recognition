/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "qrcode.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *portLineEdit_2;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *hostLineEdit_2;
    QPushButton *pushButton_connect;
    QPushButton *pushButton_disconnect;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_status;
    QTextEdit *textEdit_log;
    QPushButton *pushButton_send;
    QLineEdit *lineEdit_message;
    QSplitter *splitter;
    QLabel *label_5;
    QPushButton *Update;
    QRCode *widget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(832, 553);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 40, 172, 26));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        portLineEdit_2 = new QLineEdit(layoutWidget);
        portLineEdit_2->setObjectName(QString::fromUtf8("portLineEdit_2"));

        horizontalLayout_4->addWidget(portLineEdit_2);

        layoutWidget_2 = new QWidget(centralWidget);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(20, 10, 172, 26));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        hostLineEdit_2 = new QLineEdit(layoutWidget_2);
        hostLineEdit_2->setObjectName(QString::fromUtf8("hostLineEdit_2"));

        horizontalLayout_5->addWidget(hostLineEdit_2);

        pushButton_connect = new QPushButton(centralWidget);
        pushButton_connect->setObjectName(QString::fromUtf8("pushButton_connect"));
        pushButton_connect->setGeometry(QRect(261, 41, 231, 31));
        QFont font;
        font.setPointSize(13);
        font.setBold(true);
        font.setWeight(75);
        pushButton_connect->setFont(font);
        pushButton_connect->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));
        pushButton_disconnect = new QPushButton(centralWidget);
        pushButton_disconnect->setObjectName(QString::fromUtf8("pushButton_disconnect"));
        pushButton_disconnect->setEnabled(true);
        pushButton_disconnect->setGeometry(QRect(500, 40, 271, 31));
        pushButton_disconnect->setFont(font);
        pushButton_disconnect->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(260, 10, 484, 28));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_status = new QLabel(layoutWidget1);
        label_status->setObjectName(QString::fromUtf8("label_status"));
        label_status->setMaximumSize(QSize(9999, 16777215));
        label_status->setFont(font);
        label_status->setFrameShape(QFrame::Box);
        label_status->setFrameShadow(QFrame::Sunken);
        label_status->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_status);

        textEdit_log = new QTextEdit(centralWidget);
        textEdit_log->setObjectName(QString::fromUtf8("textEdit_log"));
        textEdit_log->setGeometry(QRect(20, 80, 551, 381));
        pushButton_send = new QPushButton(centralWidget);
        pushButton_send->setObjectName(QString::fromUtf8("pushButton_send"));
        pushButton_send->setGeometry(QRect(480, 470, 101, 31));
        lineEdit_message = new QLineEdit(centralWidget);
        lineEdit_message->setObjectName(QString::fromUtf8("lineEdit_message"));
        lineEdit_message->setGeometry(QRect(20, 470, 441, 31));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(640, 90, 120, 23));
        splitter->setOrientation(Qt::Horizontal);
        label_5 = new QLabel(splitter);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        splitter->addWidget(label_5);
        Update = new QPushButton(splitter);
        Update->setObjectName(QString::fromUtf8("Update"));
        splitter->addWidget(Update);
        widget = new QRCode(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(590, 130, 230, 210));
        widget->setMinimumSize(QSize(200, 200));
        widget->setBaseSize(QSize(200, 200));
        MainWindow->setCentralWidget(centralWidget);
        textEdit_log->raise();
        pushButton_send->raise();
        lineEdit_message->raise();
        splitter->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget_2->raise();
        pushButton_connect->raise();
        pushButton_disconnect->raise();
        widget->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\344\272\214\347\273\264\347\240\201\350\257\206\345\210\253QT\344\270\212\344\275\215\346\234\272", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\347\253\257\345\217\243\357\274\232", nullptr));
        portLineEdit_2->setPlaceholderText(QApplication::translate("MainWindow", "5000", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "\344\270\273\346\234\272\357\274\232", nullptr));
        hostLineEdit_2->setPlaceholderText(QApplication::translate("MainWindow", "10.10.10.103", nullptr));
        pushButton_connect->setText(QApplication::translate("MainWindow", "Connect to server", nullptr));
        pushButton_disconnect->setText(QApplication::translate("MainWindow", "Disconnect from server", nullptr));
        label_status->setText(QApplication::translate("MainWindow", "status", nullptr));
        pushButton_send->setText(QApplication::translate("MainWindow", "Send this:", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "\344\272\214\347\273\264\347\240\201", nullptr));
        Update->setText(QApplication::translate("MainWindow", "Update", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
