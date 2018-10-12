#ifndef DRAWING_H
#define DRAWING_H

#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_legend.h>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>
//#include"serial.h"

class myCurve:public QwtPlotCurve
{
public:

    std::vector<float> &data;
    QwtPlot* d_plot;
    QwtSymbol *symbol;
    int& ind_c;

    myCurve(int bufShowSize, std::vector<float> &dataH,QwtPlot* d_plotH,const QString &title,
            const QColor &color, const QColor &colorSymbol,int& ind_ch );
    void signalDrawing(float k);
    void pointDrawing(float , float);
    void set_Drawing(std::vector<float> &x, std::vector<float> &y, int,float k);
};



#endif // DRAWING_H
