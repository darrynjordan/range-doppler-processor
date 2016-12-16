#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->a_open_config, SIGNAL(triggered(bool)), SLOT(openSummaryFile()));
    connect(ui->b_start, SIGNAL(clicked(bool)), SLOT(processing()));
    connect(ui->a_exit, SIGNAL(triggered(bool)), SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openSummaryFile()
{
    QString directory = QFileDialog::getOpenFileName(this, "Load Dataset", QDir::currentPath());
    processor.extractParameters(directory.toStdString());

    //TODO populate form with processor data
    ui->c_debugEnabled->setChecked(processor.getIsDebug());
    //ui->e_samplingRate->setText("Test");
    ui->c_dopplerEnabled->setChecked(processor.getIsDoppler());
    ui->e_datasetPath->setText(QString::fromStdString(processor.getBinaryFilePath()));
    //ui->c_updateRate->setCurrentIndex(2);
}

void MainWindow::process()
{
    timer.start(); //TODO Give timer to processor
    processor.sniffDataset();
    processor.allocateMemory();
    processor.createPlans();
    processor.initPlots();
    processor.perRangeProc();
    processor.releaseMemory();
}


void MainWindow::updatePlot(cv::Mat& image, QLabel* widget)
{
    cv::resize(image, image, cv::Size(widget->width(), widget->height()), 0, 0, cv::INTER_LINEAR);
    cv::cvtColor(image, image, CV_BGR2RGB);

    QImage imdisplay((uchar*)image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
    widget->setPixmap(QPixmap::fromImage(imdisplay));
}
