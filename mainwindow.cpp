#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "net.h"
#include <QDebug>
float x_in1[4]={1,0,1,1},
x_in2[4]={0,1,0,0};
float t1[4]={0,1,0.4,1};
float t2[4]={1,0,0,1};
net* setka;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setka=new net(4,4,4);
    for(int i=0;i<10000;i++)
    {
    setka->learn1(x_in1,t1);
    setka->learn1(x_in2,t2);
    }



    setka->refresh(x_in2);
//qDebug()<<setka->lr2->w[0][0];
//    qDebug()<<((rand()%10)-5)/12.;

    qDebug()<<setka->lr2->n[2].state;
    setka->refresh(x_in1);

    qDebug()<<setka->lr2->n[2].state;

}

MainWindow::~MainWindow()
{
    delete ui;
}
