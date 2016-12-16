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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *a_open_config;
    QAction *a_exit;
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *l_filePath;
    QLineEdit *e_datasetPath;
    QLabel *label;
    QComboBox *comboBox_5;
    QLabel *label_2;
    QLineEdit *e_samplingRate;
    QLabel *label_3;
    QLineEdit *e_upPeriod;
    QLabel *label_4;
    QLineEdit *e_downPeriod;
    QLabel *label_5;
    QLineEdit *e_trim;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_17;
    QCheckBox *c_debugEnabled;
    QLabel *label_6;
    QCheckBox *c_dopplerEnabled;
    QLabel *label_7;
    QComboBox *c_dopplerPoints;
    QLabel *label_8;
    QComboBox *c_updateRate;
    QLabel *label_9;
    QComboBox *comboBox;
    QLabel *label_10;
    QComboBox *comboBox_2;
    QPushButton *b_start;
    QGroupBox *groupBox_4;
    QLabel *rti_plot;
    QGroupBox *groupBox_5;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuAbout;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(874, 526);
        a_open_config = new QAction(MainWindow);
        a_open_config->setObjectName(QStringLiteral("a_open_config"));
        a_exit = new QAction(MainWindow);
        a_exit->setObjectName(QStringLiteral("a_exit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 20, 231, 201));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        l_filePath = new QLabel(groupBox);
        l_filePath->setObjectName(QStringLiteral("l_filePath"));

        gridLayout->addWidget(l_filePath, 0, 0, 1, 1);

        e_datasetPath = new QLineEdit(groupBox);
        e_datasetPath->setObjectName(QStringLiteral("e_datasetPath"));

        gridLayout->addWidget(e_datasetPath, 0, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        comboBox_5 = new QComboBox(groupBox);
        comboBox_5->setObjectName(QStringLiteral("comboBox_5"));

        gridLayout->addWidget(comboBox_5, 1, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        e_samplingRate = new QLineEdit(groupBox);
        e_samplingRate->setObjectName(QStringLiteral("e_samplingRate"));
        e_samplingRate->setEnabled(false);

        gridLayout->addWidget(e_samplingRate, 2, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        e_upPeriod = new QLineEdit(groupBox);
        e_upPeriod->setObjectName(QStringLiteral("e_upPeriod"));

        gridLayout->addWidget(e_upPeriod, 3, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        e_downPeriod = new QLineEdit(groupBox);
        e_downPeriod->setObjectName(QStringLiteral("e_downPeriod"));

        gridLayout->addWidget(e_downPeriod, 4, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 5, 0, 1, 1);

        e_trim = new QLineEdit(groupBox);
        e_trim->setObjectName(QStringLiteral("e_trim"));

        gridLayout->addWidget(e_trim, 5, 1, 1, 1);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 240, 231, 231));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout_2->addWidget(label_17, 0, 0, 1, 1);

        c_debugEnabled = new QCheckBox(groupBox_2);
        c_debugEnabled->setObjectName(QStringLiteral("c_debugEnabled"));

        gridLayout_2->addWidget(c_debugEnabled, 0, 1, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 1, 0, 1, 1);

        c_dopplerEnabled = new QCheckBox(groupBox_2);
        c_dopplerEnabled->setObjectName(QStringLiteral("c_dopplerEnabled"));

        gridLayout_2->addWidget(c_dopplerEnabled, 1, 1, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 2, 0, 1, 1);

        c_dopplerPoints = new QComboBox(groupBox_2);
        c_dopplerPoints->setObjectName(QStringLiteral("c_dopplerPoints"));

        gridLayout_2->addWidget(c_dopplerPoints, 2, 1, 1, 1);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_2->addWidget(label_8, 3, 0, 1, 1);

        c_updateRate = new QComboBox(groupBox_2);
        c_updateRate->setObjectName(QStringLiteral("c_updateRate"));

        gridLayout_2->addWidget(c_updateRate, 3, 1, 1, 1);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_2->addWidget(label_9, 4, 0, 1, 1);

        comboBox = new QComboBox(groupBox_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout_2->addWidget(comboBox, 4, 1, 1, 1);

        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_2->addWidget(label_10, 5, 0, 1, 1);

        comboBox_2 = new QComboBox(groupBox_2);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        gridLayout_2->addWidget(comboBox_2, 5, 1, 1, 1);

        b_start = new QPushButton(centralWidget);
        b_start->setObjectName(QStringLiteral("b_start"));
        b_start->setGeometry(QRect(10, 480, 80, 22));
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(250, 20, 361, 451));
        rti_plot = new QLabel(groupBox_4);
        rti_plot->setObjectName(QStringLiteral("rti_plot"));
        rti_plot->setGeometry(QRect(10, 30, 341, 321));
        rti_plot->setFrameShape(QFrame::Panel);
        groupBox_5 = new QGroupBox(centralWidget);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(620, 20, 361, 451));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 874, 19));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        MainWindow->setMenuBar(menuBar);
        QWidget::setTabOrder(e_datasetPath, comboBox_5);
        QWidget::setTabOrder(comboBox_5, e_samplingRate);
        QWidget::setTabOrder(e_samplingRate, e_upPeriod);
        QWidget::setTabOrder(e_upPeriod, e_downPeriod);
        QWidget::setTabOrder(e_downPeriod, e_trim);
        QWidget::setTabOrder(e_trim, c_debugEnabled);
        QWidget::setTabOrder(c_debugEnabled, c_dopplerEnabled);
        QWidget::setTabOrder(c_dopplerEnabled, c_dopplerPoints);
        QWidget::setTabOrder(c_dopplerPoints, c_updateRate);
        QWidget::setTabOrder(c_updateRate, comboBox);
        QWidget::setTabOrder(comboBox, comboBox_2);
        QWidget::setTabOrder(comboBox_2, b_start);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuFile->addAction(a_open_config);
        menuFile->addSeparator();
        menuFile->addAction(a_exit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Range-Doppler Processor", 0));
        a_open_config->setText(QApplication::translate("MainWindow", "Open Config File", 0));
        a_exit->setText(QApplication::translate("MainWindow", "Exit", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Dataset Properties", 0));
        l_filePath->setText(QApplication::translate("MainWindow", "Date:", 0));
        label->setText(QApplication::translate("MainWindow", "Decimation Factor:", 0));
        comboBox_5->clear();
        comboBox_5->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "32", 0)
         << QApplication::translate("MainWindow", "64", 0)
         << QApplication::translate("MainWindow", "128", 0)
         << QApplication::translate("MainWindow", "256", 0)
         << QApplication::translate("MainWindow", "512", 0)
        );
        label_2->setText(QApplication::translate("MainWindow", "Sampling Rate:", 0));
        label_3->setText(QApplication::translate("MainWindow", "Up-Ramp Length:", 0));
        label_4->setText(QApplication::translate("MainWindow", "Down-Ramp Length:", 0));
        label_5->setText(QApplication::translate("MainWindow", "Trim:", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Processing Configuration", 0));
        label_17->setText(QApplication::translate("MainWindow", "Debug", 0));
        c_debugEnabled->setText(QApplication::translate("MainWindow", "Enabled", 0));
        label_6->setText(QApplication::translate("MainWindow", "Doppler Processing:", 0));
        c_dopplerEnabled->setText(QApplication::translate("MainWindow", "Enabled", 0));
        label_7->setText(QApplication::translate("MainWindow", "Doppler Points:", 0));
        c_dopplerPoints->clear();
        c_dopplerPoints->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "32", 0)
         << QApplication::translate("MainWindow", "64", 0)
         << QApplication::translate("MainWindow", "128", 0)
         << QApplication::translate("MainWindow", "256", 0)
         << QApplication::translate("MainWindow", "512", 0)
        );
        label_8->setText(QApplication::translate("MainWindow", "Update Rate:", 0));
        c_updateRate->clear();
        c_updateRate->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "32", 0)
         << QApplication::translate("MainWindow", "64", 0)
         << QApplication::translate("MainWindow", "128", 0)
         << QApplication::translate("MainWindow", "256", 0)
         << QApplication::translate("MainWindow", "512", 0)
        );
        label_9->setText(QApplication::translate("MainWindow", "Range Window:", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Uniform", 0)
         << QApplication::translate("MainWindow", "Hanning", 0)
         << QApplication::translate("MainWindow", "Hamming", 0)
         << QApplication::translate("MainWindow", "Blackman", 0)
        );
        label_10->setText(QApplication::translate("MainWindow", "Doppler Window:", 0));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Uniform", 0)
         << QApplication::translate("MainWindow", "Hanning", 0)
         << QApplication::translate("MainWindow", "Hamming", 0)
         << QApplication::translate("MainWindow", "Blackman", 0)
        );
        b_start->setText(QApplication::translate("MainWindow", "Start", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Range-Time-Intensity", 0));
        rti_plot->setText(QString());
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Range-Doppler", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuAbout->setTitle(QApplication::translate("MainWindow", "About", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
