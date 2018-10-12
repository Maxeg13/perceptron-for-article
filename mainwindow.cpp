#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "perceptron.h"
#include "drawing.h"
#include <QDebug>

myCurve *test_curve;
vector<float> test_data;

float x_in1[]={0,1,0,1},
x_in2[]={1,0,1,0},
x_in3[]={1,1,1,1};

float t1[]={0.1},
t2[]={0.8},
t3[]={1};
int bufShowSize=1000;
int ind_c=0;

QwtPlot* d_plot;
vector<int> constr;

void rescale(float*,int,float);
perceptron* perc;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    d_plot = new QwtPlot(this);
    drawingInit(d_plot,QString("test"));
    d_plot->setAxisScale(QwtPlot::yLeft,-2000,2000);
    d_plot->setAxisScale(QwtPlot::xBottom,0,bufShowSize);
//    GL->addWidget(d_plot[i_pl],(i_pl)/4,1+(i_pl)%4);
    test_curve=new myCurve(bufShowSize, test_data, d_plot,"spikes",Qt::black,Qt::black,ind_c);
    ind_c=(ind_c+1)%test_data.size();


    constr.push_back(4);
    constr.push_back(4);
//    constr.push_back(3);
    constr.push_back(1);

    rand();
//    rand();
//    rand();
//    rand();
//    rand();
//    rand();



    perc=new perceptron(constr,1);

    for(int i=0;i<10000;i++)
    {
        perc->learn1(x_in1,t1);
        perc->learn1(x_in2,t2);
        perc->learn1(x_in3,t3);
    }


    perc->refresh(x_in1);
    qDebug()<<perc->lr[perc->N-1]->n[0].state;
    perc->refresh(x_in2);
    qDebug()<<perc->lr[perc->N-1]->n[0].state;
    perc->refresh(x_in3);
    qDebug()<<perc->lr[perc->N-1]->n[0].state;

    //rescale f
    for(int i=0;i<perc->N;i++)
            perc->lr[i]->n=new scaled_neuron[perc->lr[i]->size]();
    rescale(x_in1,constr[0],2);
    rescale(x_in2,constr[0],2);
    rescale(x_in3,constr[0],2);
    rescale(t1,1,2);
    rescale(t2,1,2);
    rescale(t3,1,2);
    perc->rescaleW(0.5);



    perc->refresh(x_in1);
    perc->showStates();

    perc->rescaleXShifts(20);

    rescale(x_in1,constr[0],20);
    perc->refresh(x_in1);
    perc->showStates();

    rescale(x_in2,constr[0],20);
    perc->refresh(x_in2);
    perc->showStates();

    rescale(x_in3,constr[0],20);
    perc->refresh(x_in3);
    perc->showStates();

    test_curve->signalDrawing(1);
}


void MainWindow::drawingInit(QwtPlot* d_plot, QString title)
{

    //        setCentralWidget(MW);

    //canvas().resize(925,342)
    //    d_plot->canvas()->resize(100,150);
    //d_plot->autoRefresh();
    d_plot->setAutoReplot();
    //_______232

    // настройка функций
    QwtPlotPicker *d_picker =
            new QwtPlotPicker(
                QwtPlot::xBottom, QwtPlot::yLeft, // ассоциация с осями
                QwtPlotPicker::CrossRubberBand, // стиль перпендикулярных линий
                QwtPicker::ActiveOnly, // включение/выключение
                d_plot->canvas() ); // ассоциация с полем
    // Цвет перпендикулярных линий
    d_picker->setRubberBandPen( QColor( Qt::red ) );

    // цвет координат положения указателя
    d_picker->setTrackerPen( QColor( Qt::black ) );

    // непосредственное включение вышеописанных функций
    d_picker->setStateMachine( new QwtPickerDragPointMachine() );

    // Включить возможность приближения/удаления графика
    // #include <qwt_plot_magnifier.h>
    QwtPlotMagnifier *magnifier = new QwtPlotMagnifier(d_plot->canvas());
    // клавиша, активирующая приближение/удаление
    magnifier->setMouseButton(Qt::MidButton);
    // Включить возможность перемещения по графику
    // #include <qwt_plot_panner.h>
    QwtPlotPanner *d_panner = new QwtPlotPanner( d_plot->canvas() );
    // клавиша, активирующая перемещение
    d_panner->setMouseButton( Qt::RightButton );
    // Включить отображение координат курсора и двух перпендикулярных
    // линий в месте его отображения

    QwtText* qwtt=new QwtText(title);
    qwtt->setFont(QFont("Helvetica", 11,QFont::Normal));

    d_plot->setAxisScale(1,-500,500,200);
    d_plot->setTitle( *qwtt ); // заголовок
    d_plot->setCanvasBackground( Qt::white ); // цвет фона


    // Включить сетку
    // #include <qwt_plot_grid.h>
    //    QwtPlotGrid *grid = new QwtPlotGrid(); //

    //    grid->setMajorPen(QPen( Qt::gray, 2 )); // цвет линий и толщина
    //    grid->attach( d_plot ); // добавить сетку к полю графика


    d_plot->setMinimumSize(220,180);

}

void rescale(float* a,int N,float s)
{
    for(int i=0;i<N;i++)
        a[i]*=s;
}



MainWindow::~MainWindow()
{
    delete ui;
}
