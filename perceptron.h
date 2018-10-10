#ifndef PERCEPTRON_H
#define PERCEPTRON_H
#include <math.h>

class neuron
{
public:
    float state_in;
    float state;
    float err_in;
    float err;

    static float getErr(float x)
    {

    }
    static float act(float x)
    {
//        return(1/(1+exp(-x)));
        float a=3.75;
        if(x<a)
        return()
    }
    static float actDer(float x)
    {
//        return(act(x)*(1-act(x)));
    }
    neuron()
    {
        //_____232
        state=0;
        err=0;
    }
};





class layer
{
public:
    layer* inLayer;
    int size;
    int size_inp;
    neuron *n;
    float** w;
    float a;
    layer()
    {

    }
    layer(int N,layer* l=NULL)
    {
        a=0.1;
        inLayer=l;
        size=N;
        n=new neuron[N]();

        if(l!=NULL)
        {
            size_inp=l->size;
            w=new float*[size_inp+1];
            for(int i=0;i<(size_inp+1);i++)
                w[i]=new float[size];
            for(int i=0;i<(size_inp+1);i++)
                for(int j=0;j<size;j++)
                    //232 0
                    w[i][j]=((rand()%10)-5)/12.;
        }
    }
    void set(float* x)
    {
        for (int i=0;i<size;i++)
            n[i].state=x[i];
    }
    void refresh()//not for first
    {
        for(int j=0;j<size;j++)
        {
            n[j].state_in=0;
            for(int i=0;i<size_inp;i++)
                n[j].state_in+=(inLayer->n[i].state*w[i][j]);

            n[j].state_in+=w[size_inp][j];
            n[j].state=neuron::act(n[j].state_in);
        }
    }
    void getErr(float* t)
    {
        for (int i=0;i<size;i++)
            n[i].err=(-n[i].state+t[i])*neuron::actDer(n[i].state_in);
    }
    void pushErr()
    {
        for(int i=0;i<size_inp;i++)
        {
            inLayer->n[i].err_in=0;
            for(int j=0;j<size;j++)
            {
                inLayer->n[i].err_in+=w[i][j]*n[j].err;
            }

            inLayer->n[i].err=inLayer->n[i].err_in*neuron::actDer(inLayer->n[i].state_in);
        }
    }
    void refreshW()
    {
        for(int i=0;i<size_inp;i++)
            for(int j=0;j<size;j++)
            {
                w[i][j]+=a*inLayer->n[i].state*n[j].err;
            }
        for(int j=0;j<size;j++)
        w[size_inp][j]+=a*n[j].err;
    }
};





#endif // PERCEPTRON_H
