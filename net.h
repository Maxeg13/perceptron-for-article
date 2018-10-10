#ifndef NET_H
#define NET_H
#include "perceptron.h"
class net
{
public:
    layer *lr0, *lr1, *lr2;
    net(int n1, int n2, int n3)
    {
        lr0=new layer(n1);
        lr1=new layer(n2,lr0);
        lr2=new layer(n3,lr1);
    }
    void refresh(float* x)
    {
        lr0->set(x);
        lr1->refresh();
        lr2->refresh();

    }
    void learn1(float* x,float* t)
    {
        refresh(x);
        lr2->getErr(t);
        lr2->pushErr();
        lr1->refreshW();
        lr2->refreshW();

    }
};
#endif // NET_H
