#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "timer.h"
#include "processor.h"
#include "opencv/cv.h"
#include <QLabel>

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
    void process(void);
    void updatePlot(cv::Mat& image, QLabel* widget);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
