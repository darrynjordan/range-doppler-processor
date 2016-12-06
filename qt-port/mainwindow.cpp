#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->b_openFile, SIGNAL(clicked(bool)), SLOT(openFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    QString directory = QFileDialog::getOpenFileName(this, "Load Dataset", QDir::currentPath());
    ui->e_filePath->setText(directory);
}
