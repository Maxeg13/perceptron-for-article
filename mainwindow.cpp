#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "perceptron.h"
#include <QDebug>
float x_in1[4]={1,0,1,1},
x_in2[4]={0,1,0,0};
float t1[4]={0,1,0.4,1};
float t2[4]={1,0,0,1};
perceptron* perc;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    vector<int> constr;
    constr.push_back(4);
    constr.push_back(4);
    constr.push_back(4);
    perc=new perceptron(constr);
    for(int i=0;i<10000;i++)
    {
        perc->learn1(x_in1,t1);
        perc->learn1(x_in2,t2);
    }



    perc->refresh(x_in2);
    //qDebug()<<setka->lr2->w[0][0];
    //    qDebug()<<((rand()%10)-5)/12.;

    qDebug()<<perc->lr[2]->n[2].state;
    perc->refresh(x_in1);

    qDebug()<<perc->lr[2]->n[2].state;

}

MainWindow::~MainWindow()
{
    delete ui;
}
