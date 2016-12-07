#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "timer.h"
#include "processor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    Timer timer;
    Processor processor;

private slots:
    void openSummaryFile(void);
    void start(void);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



};

#endif // MAINWINDOW_H
