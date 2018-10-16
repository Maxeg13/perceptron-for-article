#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qwt_plot.h>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void drawingInit(QwtPlot* d_plot, QString title);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void frame();
    void showFreq();

};

#endif // MAINWINDOW_H
