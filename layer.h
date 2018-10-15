#ifndef PERCEPTRON_H
#define PERCEPTRON_H
#include "neuronizh.h"


#define thr 0
//100./47.;
class perceptron;

class neuron
{
public:
    perceptron* perc;
    neuron();
    neuron(perceptron*);
    float state_in;
    float state;
    float err_in;
    float err;

    virtual float act(float x);
    virtual float actDer(float x);


};

//class integrNeuron:public neuron
//{
//public:
//    float act(float x)
//    {
//        return x;
//    }
//    float actDer(float x)
//    {
//        return 1;
//    }
//};

//class scaled_neuron:public neuron
//{
//public:
//    float act(float x)
//    {
//        if(x<thr)
//            return(0);
//        else
//            return(x-thr)*perc->f_k;
//    }
//    float actDer(float x)
//    {
//        if(x<thr)
//            return 0;
//        else
//            return perc->f_k;
//    }
//};



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
    layer(int N,int mode,perceptron*,layer* );
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
