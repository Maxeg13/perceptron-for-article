#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "perceptron.h"
#include <QDebug>
float x_in1[]={1,0,1,0},
x_in2[]={0,1,0,1};
float t1[]={0,1,1,0};
float t2[]={0,1,1,1};
void rescale(float*,float);
perceptron* perc;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    vector<int> constr;
    constr.push_back(4);
    constr.push_back(3);
    constr.push_back(4);
    perc=new perceptron(constr,1);
    for(int i=0;i<10000;i++)
    {
        perc->learn1(x_in1,t1);
        perc->learn1(x_in2,t2);
    }


    perc->refresh(x_in1);
    qDebug()<<perc->lr[2]->n[2].state;
    perc->refresh(x_in2);
    qDebug()<<perc->lr[2]->n[2].state;
    perc->refresh(x_in1);
    perc->showStates();

    //rescale f
    for(int i=0;i<3;i++)
//        for(int j=0;j<4;j++)
            perc->lr[i]->n=new scaled_neuron[perc->lr[i]->size]();
    rescale(x_in1,2);
    rescale(x_in2,2);
    rescale(t1,2);
    rescale(t2,2);
    perc->rescaleW(0.5);

    perc->refresh(x_in1);
    qDebug()<<perc->lr[2]->n[2].state;
    perc->refresh(x_in2);
    qDebug()<<perc->lr[2]->n[2].state;

    perc->refresh(x_in1);
    perc->showStates();

    perc->rescaleXShifts(20);

    rescale(x_in1,20);
    perc->refresh(x_in1);
    perc->showStates();

    rescale(x_in2,20);
    perc->refresh(x_in2);
    perc->showStates();
}


void rescale(float* a,float s)
{
    for(int i=0;i<4;i++)
        a[i]*=s;
}

MainWindow::~MainWindow()
{
    delete ui;
}
