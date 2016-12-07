/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *e_samplingRate;
    QLineEdit *e_upPeriod;
    QLineEdit *e_downPeriod;
    QLineEdit *e_trim;
    QComboBox *comboBox_5;
    QLabel *l_filePath;
    QLineEdit *e_datasetPath;
    QGroupBox *groupBox_2;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QCheckBox *c_dopplerEnabled;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QComboBox *c_dopplerPoints;
    QComboBox *c_updateRate;
    QLabel *label_17;
    QCheckBox *c_debugEnabled;
    QGroupBox *groupBox_3;
    QLabel *label_11;
    QLineEdit *e_summaryPath;
    QPushButton *b_start;
    QGroupBox *groupBox_4;
    QGroupBox *groupBox_5;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1041, 634);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 100, 281, 211));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 60, 121, 16));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 90, 121, 16));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 120, 121, 16));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 150, 141, 16));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 180, 59, 14));
        e_samplingRate = new QLineEdit(groupBox);
        e_samplingRate->setObjectName(QStringLiteral("e_samplingRate"));
        e_samplingRate->setEnabled(false);
        e_samplingRate->setGeometry(QRect(160, 90, 113, 22));
        e_upPeriod = new QLineEdit(groupBox);
        e_upPeriod->setObjectName(QStringLiteral("e_upPeriod"));
        e_upPeriod->setGeometry(QRect(160, 120, 113, 22));
        e_downPeriod = new QLineEdit(groupBox);
        e_downPeriod->setObjectName(QStringLiteral("e_downPeriod"));
        e_downPeriod->setGeometry(QRect(160, 150, 113, 22));
        e_trim = new QLineEdit(groupBox);
        e_trim->setObjectName(QStringLiteral("e_trim"));
        e_trim->setGeometry(QRect(160, 180, 113, 22));
        comboBox_5 = new QComboBox(groupBox);
        comboBox_5->setObjectName(QStringLiteral("comboBox_5"));
        comboBox_5->setGeometry(QRect(160, 60, 111, 22));
        l_filePath = new QLabel(groupBox);
        l_filePath->setObjectName(QStringLiteral("l_filePath"));
        l_filePath->setGeometry(QRect(10, 30, 56, 16));
        e_datasetPath = new QLineEdit(groupBox);
        e_datasetPath->setObjectName(QStringLiteral("e_datasetPath"));
        e_datasetPath->setGeometry(QRect(160, 30, 111, 22));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 330, 281, 231));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 60, 201, 16));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 90, 161, 16));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 120, 131, 16));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 150, 131, 16));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 180, 141, 16));
        c_dopplerEnabled = new QCheckBox(groupBox_2);
        c_dopplerEnabled->setObjectName(QStringLiteral("c_dopplerEnabled"));
        c_dopplerEnabled->setGeometry(QRect(160, 60, 85, 20));
        comboBox = new QComboBox(groupBox_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(160, 150, 111, 22));
        comboBox_2 = new QComboBox(groupBox_2);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(160, 180, 111, 22));
        c_dopplerPoints = new QComboBox(groupBox_2);
        c_dopplerPoints->setObjectName(QStringLiteral("c_dopplerPoints"));
        c_dopplerPoints->setGeometry(QRect(160, 90, 111, 22));
        c_updateRate = new QComboBox(groupBox_2);
        c_updateRate->setObjectName(QStringLiteral("c_updateRate"));
        c_updateRate->setGeometry(QRect(160, 120, 111, 22));
        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(10, 30, 59, 14));
        c_debugEnabled = new QCheckBox(groupBox_2);
        c_debugEnabled->setObjectName(QStringLiteral("c_debugEnabled"));
        c_debugEnabled->setGeometry(QRect(160, 30, 85, 20));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 20, 281, 61));
        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(10, 30, 59, 14));
        e_summaryPath = new QLineEdit(groupBox_3);
        e_summaryPath->setObjectName(QStringLiteral("e_summaryPath"));
        e_summaryPath->setGeometry(QRect(160, 30, 111, 22));
        b_start = new QPushButton(centralWidget);
        b_start->setObjectName(QStringLiteral("b_start"));
        b_start->setGeometry(QRect(10, 570, 80, 22));
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(300, 20, 361, 541));
        groupBox_5 = new QGroupBox(centralWidget);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(670, 20, 361, 541));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1041, 19));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Range-Doppler Processor", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Dataset", 0));
        label->setText(QApplication::translate("MainWindow", "Decimation Factor:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Sampling Rate:", 0));
        label_3->setText(QApplication::translate("MainWindow", "Up-Ramp Length:", 0));
        label_4->setText(QApplication::translate("MainWindow", "Down-Ramp Length:", 0));
        label_5->setText(QApplication::translate("MainWindow", "Trim:", 0));
        comboBox_5->clear();
        comboBox_5->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "32", 0)
         << QApplication::translate("MainWindow", "64", 0)
         << QApplication::translate("MainWindow", "128", 0)
         << QApplication::translate("MainWindow", "256", 0)
         << QApplication::translate("MainWindow", "512", 0)
        );
        l_filePath->setText(QApplication::translate("MainWindow", "File Path:", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Processing", 0));
        label_6->setText(QApplication::translate("MainWindow", "Doppler Processing:", 0));
        label_7->setText(QApplication::translate("MainWindow", "Doppler Points:", 0));
        label_8->setText(QApplication::translate("MainWindow", "Update Rate:", 0));
        label_9->setText(QApplication::translate("MainWindow", "Range Window:", 0));
        label_10->setText(QApplication::translate("MainWindow", "Doppler Window:", 0));
        c_dopplerEnabled->setText(QApplication::translate("MainWindow", "Enabled", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Uniform", 0)
         << QApplication::translate("MainWindow", "Hanning", 0)
         << QApplication::translate("MainWindow", "Hamming", 0)
         << QApplication::translate("MainWindow", "Blackman", 0)
        );
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Uniform", 0)
         << QApplication::translate("MainWindow", "Hanning", 0)
         << QApplication::translate("MainWindow", "Hamming", 0)
         << QApplication::translate("MainWindow", "Blackman", 0)
        );
        c_dopplerPoints->clear();
        c_dopplerPoints->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "32", 0)
         << QApplication::translate("MainWindow", "64", 0)
         << QApplication::translate("MainWindow", "128", 0)
         << QApplication::translate("MainWindow", "256", 0)
         << QApplication::translate("MainWindow", "512", 0)
        );
        c_updateRate->clear();
        c_updateRate->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "32", 0)
         << QApplication::translate("MainWindow", "64", 0)
         << QApplication::translate("MainWindow", "128", 0)
         << QApplication::translate("MainWindow", "256", 0)
         << QApplication::translate("MainWindow", "512", 0)
        );
        label_17->setText(QApplication::translate("MainWindow", "Debug", 0));
        c_debugEnabled->setText(QApplication::translate("MainWindow", "Enabled", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Summary File", 0));
        label_11->setText(QApplication::translate("MainWindow", "File Path:", 0));
        b_start->setText(QApplication::translate("MainWindow", "Start", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Range-Time-Intensity", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Range-Doppler", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
