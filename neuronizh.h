#ifndef NEURONIZH_H
#define NEURONIZH_H
#include <stdio.h>
#define TAU_SYN 30//22
#define REVERSE_TAU 1./TAU_SYN


using namespace std;

//class neuronIzh;


class neuronIzh
{
public:

    float a;
    float b;
    float c;
    float d;
    float step;
    float fired;
    float E_m;
    float U_e;
    float dE_m;
    float dU_e;
    float input_sum;
    float post_sum;
    float freq;
    float freq_show;
    int freq_cnt;


    neuronIzh();
    void compute(float);

};

#endif // NEURONIZH_H
