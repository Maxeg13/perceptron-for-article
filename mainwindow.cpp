#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "perceptron.h"
#include <QDebug>
float x_in1[]={0,1,0,1},
x_in2[]={1,0,1,0},
x_in3[]={1,1,1,1};

float t1[]={0.1},
t2[]={0.8},
t3[]={1};

vector<int> constr;

void rescale(float*,int,float);
perceptron* perc;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    constr.push_back(4);
    constr.push_back(4);
//    constr.push_back(3);
    constr.push_back(1);

    rand();
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
