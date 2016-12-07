#include "mainwindow.h"
#include <QApplication>


#define VERSION "0.2.0"

void splash(void);

int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);
    MainWindow main_window;

    splash();

    main_window.show();

    return a.exec();
}

void splash(void)
{
    printf("Range-Doppler Processor v%s\n", VERSION);
    printf("------------------------------\n");
}
