//значения нейромедиаторов = частота
//ток не равен частоте, ток какой есть такой есть
#include "mainwindow.h"
#include "perceptron.h"
#include "drawing.h"
#include <QDebug>
#include <QGridLayout>
#include <QTimer>
#include <QLineEdit>
#include <QPushButton>

QTimer* timer;
myCurve *test_curve;
vector<float> test_data;
QLineEdit *lr_line, *n_line, *x_inp_line;
QPushButton *freq_btn;

float x_in[4][4]={{0,0,0,1},
                  {1,0,0,1},
                  {0,1,1,1},
                  {1,1,1,1}};

float
t1[]={0.3},
t2[]={1},//0.8
t3[]={1},
t4[]={0.3};
int bufShowSize=1000;
int ind_c=0;

QwtPlot* d_plot;
vector<int> constr;

float noise()
{
    return ((rand()%10)-4.5)/10.;
}

void rescale(float*,int,float);
perceptron* perc;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    n_line=new QLineEdit(QString::number(QString("0").toInt()));
    lr_line=new QLineEdit(QString::number(QString(constr.size()-1).toInt()));/**/
    x_inp_line=new QLineEdit(QString::number(QString("0").toInt()));

    freq_btn=new QPushButton("info");
    connect(freq_btn, SIGNAL(released()),this,SLOT(showFreq()));

    d_plot = new QwtPlot();
    drawingInit(d_plot,QString("test"));
    d_plot->setAxisScale(QwtPlot::yLeft,-100,50);
    d_plot->setAxisScale(QwtPlot::xBottom,0,bufShowSize);
    QGridLayout* GL=new QGridLayout();
    QWidget *centralWidget1=new QWidget();
    centralWidget1->setLayout(GL);
    GL->addWidget(d_plot,1,1);
    GL->addWidget(lr_line,2,1);
    GL->addWidget(n_line,3,1);
    GL->addWidget(x_inp_line,4,1);
    GL->addWidget(freq_btn,5,1);

    this->setCentralWidget(centralWidget1);

    test_curve=new myCurve(bufShowSize, test_data, d_plot,"spikes",Qt::black,Qt::black,ind_c);
    ind_c=(ind_c+1)%test_data.size();

    timer=new QTimer();
    timer->start(42);
    connect(timer,SIGNAL(timeout()),this,SLOT(frame()));

    //4 6 1
    //4 6 4 1
    constr.push_back(4);
    constr.push_back(8);//15 // 8
    //    constr.push_back(2);
    constr.push_back(1);

    rand();
    rand();
    //        rand();
    //    rand();
    //    rand();
    //    rand();



    perc=new perceptron(constr,1);

    for(int i=0;i<10000;i++)
    {
        perc->learn1(x_in[0],t1);
        perc->learn1(x_in[1],t2);
        perc->learn1(x_in[2],t3);
        perc->learn1(x_in[3],t4);
    }


    perc->refresh(x_in[0]);
    qDebug()<<perc->lr[perc->N-1]->n[0].state;
    perc->refresh(x_in[1]);
    qDebug()<<perc->lr[perc->N-1]->n[0].state;
    perc->refresh(x_in[2]);
    qDebug()<<perc->lr[perc->N-1]->n[0].state;
    perc->refresh(x_in[3]);
    qDebug()<<perc->lr[perc->N-1]->n[0].state;


    //    rescale act_func //!!!!!!!!!!bad code snippet!!!!!!!!!!!!
    //    float resc=0.1;
    //        for(int i=0;i<perc->N;i++)
    //                perc->lr[i]->n=new scaled_neuron[perc->lr[i]->size]();
    //        rescale(x_in[0],constr[0],1/resc);
    //        rescale(x_in[1],constr[0],1/resc);
    //        rescale(x_in[2],constr[0],1/resc);
    //        rescale(t1,1,2);
    //        rescale(t2,1,2);
    //        rescale(t3,1,2);
    //        perc->rescaleW(0.5);
    perc->refresh(x_in[0]);
    perc->showStates();

    //rescale act_func
    //    perc->f_k=0.0022;
    //    perc->rescaleW(11);



    float resc_x=50;
    perc->rescaleXShifts(resc_x);

    rescale(x_in[0],constr[0],resc_x);
    perc->refresh(x_in[0]);
    perc->showStates();

    rescale(x_in[1],constr[0],resc_x);
    perc->refresh(x_in[1]);
    perc->showStates();

    rescale(x_in[2],constr[0],resc_x);
    perc->refresh(x_in[2]);
    perc->showStates();

    rescale(x_in[3],constr[0],resc_x);
    perc->refresh(x_in[3]);
    perc->showStates();

    test_curve->signalDrawing(1);
}

void MainWindow::frame()
{


    static int k=0;

    perc->refresh(x_in[x_inp_line->text().toInt()]);

    float k_stat=0.54;
    for(int i=0;i<42;i++)
    {
        //        neur.input_sum=4;

        for(int j=0;j<constr[0];j++)
            perc->lr[0]->izh[j].compute(perc->lr[0]->n[j].state*k_stat+noise());

        //        qDebug()<<perc->lr[0]->izh[0].post_sum;

        for(int l=1;l<constr.size();l++)
        {
            perc->lr[l]->izh[constr[l]].compute(perc->lr[l]->x_shift*k_stat+noise());
        }

        for(int l=1;l<constr.size();l++)
            perc->lr[l]->dynRefresh();



        //                k++;
        ind_c=(ind_c+1)%test_data.size();

        int l_i=lr_line->text().toInt();

        test_data[ind_c]=perc->lr[l_i]->izh[n_line->text().toInt()].E_m;
    }
    //    qDebug()<<perc->lr[0]->izh[0].post_sum;
    test_curve->signalDrawing(1);
}

void rescale(float* a,int N,float s)
{
    for(int i=0;i<N;i++)
        a[i]*=s;
}

void MainWindow::showFreq()
{
    int l_i=lr_line->text().toInt();
    qDebug()<<perc->lr[l_i]->izh[n_line->text().toInt()].freq_show;
    //    qDebug()<<"\n";
    ////    for(int i=0;i<perc->lr[l_i]->size;i++)
    //        for(int j=0;j<perc->lr[l_i]->size_inp+1;j++)
    //            qDebug()<<perc->lr[l_i]->w[j][n_line->text().toInt()];
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

    //    d_plot->setAxisScale(1,-500,-100,50);
    d_plot->setTitle( *qwtt ); // заголовок
    d_plot->setCanvasBackground( Qt::white ); // цвет фона


    // Включить сетку
    // #include <qwt_plot_grid.h>
    //    QwtPlotGrid *grid = new QwtPlotGrid(); //

    //    grid->setMajorPen(QPen( Qt::gray, 2 )); // цвет линий и толщина
    //    grid->attach( d_plot ); // добавить сетку к полю графика


    d_plot->setMinimumSize(420,250);

}





MainWindow::~MainWindow()
{

}
