#include "neuronizh.h"
#include <math.h>
#include <stdlib.h>
#include <QDebug>
#include <iostream>
float max(float x,float y)
{
    if(x>y)
        return x;
    return y;
}



neuronIzh::neuronIzh()
{
    freq_cnt=0;
    fired=0;
    a=0.02;
    b=0.2;
    c=-65;
    d=8;

    E_m=-75;
    U_e=13;
    post_sum=0;
}


void neuronIzh::compute(float x)
{
    post_sum=post_sum*(1-REVERSE_TAU)+REVERSE_TAU*(x+((rand()%10)-4.5)/10.);
    dE_m = 0.04*E_m*E_m + 5*E_m + 140 - U_e + (post_sum);
    E_m +=  dE_m;
    dU_e = a*(b*E_m - U_e);
    U_e +=   dU_e;

    if(E_m >= 30) // spike here! value 30 mV - by Izhikevich
    {
        fired=1;
        E_m = c;
        U_e = U_e + d;
    }
    else
        fired=0;


    freq_cnt++;
    if(freq_cnt<3000)
        freq+=fired;
    else
    {
        freq_show=freq/3;
        freq=0;
        freq_cnt=9;
    }
}
