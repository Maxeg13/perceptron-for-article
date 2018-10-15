#include "layer.h"
#include <math.h>
#include <iostream>
#include "perceptron.h"
#define NN 4

float neuron::act(float x)
{
    //        return(1/(1+exp(-x)));

    if(x<thr)
        return(0);
    else
        return(x-thr)*perc->f_k;
}
float neuron::actDer(float x)
{
    //    return(act(x)*(1-act(x)));
    if(x<thr)
        return 0;
    else
        return perc->f_k;
}

neuron::neuron()
{}

neuron::neuron(perceptron* _perc)
{
    perc=_perc;
    //_____232
    state=0;
    err=0;
}

layer::layer()
{

}


layer::layer(int N,int mode,perceptron* _perc,layer* l=NULL)
{
    x_shift=1;
    two_sub_inLayers=0;
    a=5;
    inLayer=l;
    size=N;
    izh=new neuronIzh[N+1];
    switch(mode)
    {
    case 1:
        n=new neuron[N]();break;
    case 2:
        1;
//        n=new scaled_neuron[N](_perc);
    }
    for(int i=0;i<N;i++)
        n[i]=neuron(_perc);

    if(l!=NULL)
    {
        size_inp=l->size;
        w=new float*[size_inp+1];
        for(int i=0;i<(size_inp+1);i++)
            w[i]=new float[size];
        reset_w();
    }
}

void layer::reset_w()
{
    //    rand();
    //    rand();
    for(int i=0;i<(size_inp+1);i++)
        for(int j=0;j<size;j++)
            w[i][j]=(((rand()%50)-25)/50.+0.7)*0.1;

    // for f=_/
    for(int j=0;j<size;j++)
        w[size_inp][j]+=thr;
}

void layer::set(float* x)
{
    for (int i=0;i<size;i++)
        n[i].state=x[i];
}
void layer::refresh()//not for first
{
    for(int j=0;j<size;j++)
    {
        n[j].state_in=0;
        for(int i=0;i<size_inp;i++)
            n[j].state_in+=(inLayer->n[i].state*w[i][j]);

        n[j].state_in+=w[size_inp][j]*x_shift;
        n[j].state=n[j].act(n[j].state_in);
    }
}

void layer::dynRefresh()
{    
    for(int i=0;i<size;i++)
    {
        float sum=izh[size].fired*w[size_inp][i];
        for(int j=0;j<inLayer->size;j++)
            sum+=inLayer->izh[j].fired*w[j][i];
//        sum*=10;

        izh[i].compute(sum);
    }
}

void layer::getErr(float* t)
{
    for (int i=0;i<size;i++)
        n[i].err=(-n[i].state+t[i])*n[i].actDer(n[i].state_in);
}
void layer::pushErr()
{
    for(int i=0;i<size_inp;i++)
    {
        inLayer->n[i].err_in=0;
        for(int j=0;j<size;j++)
        {
            inLayer->n[i].err_in+=w[i][j]*n[j].err;
        }

        inLayer->n[i].err=inLayer->n[i].err_in*inLayer->n[i].actDer(inLayer->n[i].state_in);
    }
}
void layer::refreshW()
{

    for(int i=0;i<size_inp;i++)
        for(int j=0;j<size;j++)
        {
            w[i][j]+=a*inLayer->n[i].state*n[j].err;
        }
    for(int j=0;j<size;j++)
        w[size_inp][j]+=a*n[j].err;


    if(two_sub_inLayers)
        for(int i=0;i<size_inp;i++)
            for(int j=0;j<size;j++)
                if(i<size_inp/2)
                {
                    if(j>(size/2-1))
                        w[i][j]=0;
                }
                else
                    if(i>(size_inp/2-1))
                        if(j<(size/2))
                            w[i][j]=0;

}
