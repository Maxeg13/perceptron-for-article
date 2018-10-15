#ifndef PERCEPTRON_H
#define PERCEPTRON_H
#include "neuronizh.h"


#define thr 0
#define f_k 0.0022//100./47.;


class neuron
{
public:

    float state_in;
    float state;
    float err_in;
    float err;

    virtual float act(float x);
    virtual float actDer(float x);

    neuron();
};

class integrNeuron:public neuron
{
public:
    float act(float x)
    {
        return x;
    }
    float actDer(float x)
    {
        return 1;
    }
};

class scaled_neuron:public neuron
{
public:
    float act(float x)
    {
        if(x<thr)
            return(0);
        else
            return(x-thr)*f_k*2;
    }
    float actDer(float x)
    {
        if(x<thr)
            return 0;
        else
            return f_k*2;
    }
};



class layer
{
public:
    bool two_sub_inLayers;
    layer* inLayer;
    int size;
    int size_inp;
    neuronIzh* izh;
    neuron *n;
    float** w;
    float a;
    layer();
    layer(int N,int mode,layer*);
    float x_shift;

    void reset_w();
    void set(float* x);
    void refresh();
    void dynRefresh();
    void getErr(float* t);
    void pushErr();
    void refreshW();
};





#endif // PERCEPTRON_H
