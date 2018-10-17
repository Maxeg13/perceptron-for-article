#include "perceptron.h"
#include "iostream"
using namespace std;
perceptron::perceptron(vector<int>& constr, int mode)
{
    f_k=0.0021;

    N=constr.size();

    inp_size=constr[0];
    out_size=constr[N-1];

    inp_ptr=new float[constr[0]];
    tg_ptr=new float[constr[N-1]];
//    cout<<1;
    lr=new layer*[N]();
    lrh=NULL;
    for( i=0;i<(N);i++)
    {
        lr[i]=new layer();
        *lr[i]=layer(constr[i],mode,this,lrh);
        lrh=lr[i];
    }
//    *lr[N-1]=layer(constr[N-1],mode,this,lrh);
//    cout<<2;
    out=new float*[constr[N-1]];
    for( i=0;i<constr[N-1];i++)
        out[i]=&(lr[N-1]->n[i].state);
}

void perceptron::rescaleXShifts(float s)
{
    for(int i=0;i<N;i++)
        lr[i]->x_shift*=s;
}

void perceptron::rescaleW(float s)
{
    for( i=1;i<N;i++)
    {
        for(int j=0;j<lr[i]->size_inp;j++)
            for(int k=0;k<lr[i]->size;k++)
                lr[i]->w[j][k]*=s;
    }
}

int perceptron::getMaxInd()
{
    float max=-1000;
    int ind=0;
    for(i=0;i<lr[N-1]->size;i++)
    {
        if(lr[N-1]->n[i].state>max)
        {
            ind=i;
            max=lr[N-1]->n[i].state;
        }
    }
    return  ind;
}

void perceptron::showStates()
{
    cout<<"\n\n";
    cout<<"inconvenient arrangement of x_shifts (right)";
    for ( i=0;i<(N);i++)
    {
        cout<<"\n";
        for(int j=0;j<lr[i]->size;j++)
            cout<<lr[i]->n[j].state<<"  ";
        cout<<lr[i]->x_shift;
    }
}

float perceptron::reset_w()
{
    for ( i=1;i<(N);i++)
        lr[i]->reset_w();
}

float** perceptron::refresh(float* x)
{

    lr[0]->set(x);
    for(int i=1;i<N;i++)
        lr[i]->refresh();

    return out;
}

float** perceptron::refresh(vector<float>& x)
{
    for( i=0;i<lr[0]->size;i++)
        inp_ptr[i]=x[i];

    refresh(inp_ptr);
}

void perceptron::learn1(float* x,float* t)
{
    refresh(x);
    lr[N-1]->getErr(t);
    for( i=(N-1);i>1;i--)
    {
        lr[i]->pushErr();
    }
    for( i=1;i<N;i++)
        lr[i]->refreshW();
}

void perceptron::learn1(vector<float>& x,vector<float>& t, float k)
{
    for( i=0;i<lr[0]->size;i++)
        inp_ptr[i]=x[i];

    for( i=0;i<lr[N-1]->size;i++)
        tg_ptr[i]=t[i]*k;

    learn1(inp_ptr, tg_ptr);
}

void perceptron::learn1(vector<float>& x,vector<float>& t)
{
    for( i=0;i<lr[0]->size;i++)
        inp_ptr[i]=x[i];

    for( i=0;i<lr[N-1]->size;i++)
        tg_ptr[i]=t[i];

    learn1(inp_ptr, tg_ptr);
}

void perceptron::learn1(float* x,float t)
{
    refresh(x);
    lr[N-1]->getErr(&t);
    for( i=(N-1);i>1;i--)
    {
        lr[i]->pushErr();
    }
    for( i=1;i<N;i++)
        lr[i]->refreshW();
}



void perceptron::learnFunc()
{}
