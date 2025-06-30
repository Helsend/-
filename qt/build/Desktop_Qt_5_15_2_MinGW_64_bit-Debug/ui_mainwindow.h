/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QComboBox *comboBox_wait_2;
    QPushButton *pushButton_dis_2;
    QPushButton *pushButton_con_2;
    QLabel *label_11;
    QPlainTextEdit *plainTextEdit_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_con;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButton_dis;
    QPlainTextEdit *plainTextEdit;
    QComboBox *comboBox_wait;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_6;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_poll_2;
    QPushButton *pushButton_poll;
    QPushButton *pushButton_clear;
    QLabel *label_12;
    QLineEdit *lineEdit;
    QLabel *label_13;
    QLineEdit *lineEdit_2;
    QWidget *widget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(826, 572);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        groupBox_3->setMaximumSize(QSize(200, 16777215));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(14);
        font.setBold(false);
        font.setItalic(false);
        groupBox_3->setFont(font);
        groupBox_3->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        comboBox_wait_2 = new QComboBox(groupBox_3);
        comboBox_wait_2->addItem(QString());
        comboBox_wait_2->addItem(QString());
        comboBox_wait_2->addItem(QString());
        comboBox_wait_2->addItem(QString());
        comboBox_wait_2->setObjectName(QString::fromUtf8("comboBox_wait_2"));
        comboBox_wait_2->setMinimumSize(QSize(30, 30));

        gridLayout_3->addWidget(comboBox_wait_2, 5, 1, 1, 1);

        pushButton_dis_2 = new QPushButton(groupBox_3);
        pushButton_dis_2->setObjectName(QString::fromUtf8("pushButton_dis_2"));
        pushButton_dis_2->setMinimumSize(QSize(30, 30));

        gridLayout_3->addWidget(pushButton_dis_2, 7, 1, 1, 1);

        pushButton_con_2 = new QPushButton(groupBox_3);
        pushButton_con_2->setObjectName(QString::fromUtf8("pushButton_con_2"));
        pushButton_con_2->setMinimumSize(QSize(30, 30));

        gridLayout_3->addWidget(pushButton_con_2, 7, 0, 1, 1);

        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_3->addWidget(label_11, 5, 0, 1, 1);

        plainTextEdit_2 = new QPlainTextEdit(groupBox_3);
        plainTextEdit_2->setObjectName(QString::fromUtf8("plainTextEdit_2"));

        gridLayout_3->addWidget(plainTextEdit_2, 6, 0, 1, 2);


        gridLayout->addWidget(groupBox_3, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setEnabled(true);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        groupBox_2->setMaximumSize(QSize(200, 16777215));
        groupBox_2->setFont(font);
        groupBox_2->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pushButton_con = new QPushButton(groupBox_2);
        pushButton_con->setObjectName(QString::fromUtf8("pushButton_con"));
        pushButton_con->setMinimumSize(QSize(30, 30));

        gridLayout_2->addWidget(pushButton_con, 9, 1, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("font: 700 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setStyleSheet(QString::fromUtf8("font: 700 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        pushButton_dis = new QPushButton(groupBox_2);
        pushButton_dis->setObjectName(QString::fromUtf8("pushButton_dis"));
        pushButton_dis->setMinimumSize(QSize(30, 30));

        gridLayout_2->addWidget(pushButton_dis, 10, 1, 1, 1);

        plainTextEdit = new QPlainTextEdit(groupBox_2);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));

        gridLayout_2->addWidget(plainTextEdit, 8, 0, 1, 2);

        comboBox_wait = new QComboBox(groupBox_2);
        comboBox_wait->setObjectName(QString::fromUtf8("comboBox_wait"));
        comboBox_wait->setMinimumSize(QSize(30, 30));

        gridLayout_2->addWidget(comboBox_wait, 7, 1, 1, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 7, 0, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(9);
        font1.setBold(true);
        font1.setItalic(false);
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8("font: 700 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        gridLayout_2->addWidget(label_2, 2, 1, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 9, 0, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8("font: 700 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        gridLayout_2->addWidget(label_5, 3, 1, 1, 1);


        gridLayout->addWidget(groupBox_2, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_poll_2 = new QPushButton(centralWidget);
        pushButton_poll_2->setObjectName(QString::fromUtf8("pushButton_poll_2"));
        pushButton_poll_2->setMinimumSize(QSize(30, 30));
        pushButton_poll_2->setFont(font);
        pushButton_poll_2->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        horizontalLayout->addWidget(pushButton_poll_2);

        pushButton_poll = new QPushButton(centralWidget);
        pushButton_poll->setObjectName(QString::fromUtf8("pushButton_poll"));
        pushButton_poll->setMinimumSize(QSize(30, 30));
        pushButton_poll->setFont(font);
        pushButton_poll->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        horizontalLayout->addWidget(pushButton_poll);

        pushButton_clear = new QPushButton(centralWidget);
        pushButton_clear->setObjectName(QString::fromUtf8("pushButton_clear"));
        pushButton_clear->setMinimumSize(QSize(30, 30));
        pushButton_clear->setFont(font);
        pushButton_clear->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        horizontalLayout->addWidget(pushButton_clear);

        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font);
        label_12->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        horizontalLayout->addWidget(label_12);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(30, 30));

        horizontalLayout->addWidget(lineEdit);

        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font);
        label_13->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        horizontalLayout->addWidget(label_13);

        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setMinimumSize(QSize(30, 30));

        horizontalLayout->addWidget(lineEdit_2);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(2, 1);
        horizontalLayout->setStretch(3, 1);
        horizontalLayout->setStretch(4, 2);
        horizontalLayout->setStretch(5, 1);
        horizontalLayout->setStretch(6, 1);

        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 3);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));

        gridLayout->addWidget(widget, 0, 1, 2, 2);

        MainWindow->setCentralWidget(centralWidget);
        groupBox_2->raise();
        groupBox_3->raise();
        widget->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\350\260\203\350\257\225\344\277\241\346\201\257", nullptr));
        comboBox_wait_2->setItemText(0, QCoreApplication::translate("MainWindow", "3kg", nullptr));
        comboBox_wait_2->setItemText(1, QCoreApplication::translate("MainWindow", "10kg", nullptr));
        comboBox_wait_2->setItemText(2, QCoreApplication::translate("MainWindow", "20kg", nullptr));
        comboBox_wait_2->setItemText(3, QCoreApplication::translate("MainWindow", "50kg", nullptr));

        pushButton_dis_2->setText(QCoreApplication::translate("MainWindow", "\346\270\205\351\231\244\346\240\241\345\207\206", nullptr));
        pushButton_con_2->setText(QCoreApplication::translate("MainWindow", "\351\233\266\347\202\271\346\240\241\345\207\206", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\351\207\217\347\250\213\351\200\211\346\213\251", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\345\217\202\346\225\260", nullptr));
        pushButton_con->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242\344\275\215:1", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\344\275\215:8", nullptr));
        pushButton_dis->setText(QCoreApplication::translate("MainWindow", "\346\226\255\345\274\200", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\345\217\267\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207:115200", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\346\223\215\344\275\234\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\346\240\241\351\252\214\344\275\215:\346\227\240", nullptr));
        pushButton_poll_2->setText(QCoreApplication::translate("MainWindow", "\350\223\235\347\211\231\346\211\253\346\217\217", nullptr));
        pushButton_poll->setText(QCoreApplication::translate("MainWindow", "\350\223\235\347\211\231\347\273\221\345\256\232", nullptr));
        pushButton_clear->setText(QCoreApplication::translate("MainWindow", "\346\226\255\345\274\200\350\223\235\347\211\231\350\277\236\346\216\245", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "\350\223\235\347\211\231\350\260\203\350\257\225\344\277\241\346\201\257:", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "\350\266\263\345\272\225\351\207\215\345\277\203\344\275\215\347\275\256\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
