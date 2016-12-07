#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->e_summaryPath, SIGNAL(textEdited(QString)), SLOT(openSummaryFile()));
    connect(ui->e_datasetPath, SIGNAL(textEdited(QString)), SLOT(startProcessing()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openSummaryFile()
{
    QString directory = QFileDialog::getOpenFileName(this, "Load Dataset", QDir::currentPath());
    ui->e_summaryPath->setText(directory);
    processor.extractParameters(directory.toStdString());

    //TODO populate form with processor data
    ui->c_debugEnabled->setChecked(processor.getIsDebug());
    ui->c_dopplerEnabled->setChecked(processor.getIsDoppler());
    ui->e_datasetPath->setText(QString::fromStdString(processor.getBinaryFilePath()));
    //ui->c_updateRate->setCurrentIndex(2);
}

void MainWindow::startProcessing()
{
    timer.start(); //TODO Give timer to processor
    processor.sniffDataset();
    processor.allocateMemory();
    processor.createPlans();
    processor.initPlots();
    processor.perRangeProc();
    processor.releaseMemory();
}
