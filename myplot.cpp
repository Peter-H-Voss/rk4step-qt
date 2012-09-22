#include "qcustomplot.h"
#include "rk41d.h"

void myplot(QCustomPlot *plt, int plot_type, double x0, double v0,
            double (*a)(double, double, double))
{
    /* plot initialisation */
    static bool plotadded = false;
    if (!plotadded) {
        plt->addGraph();
        plt->setRangeDrag(Qt::Horizontal | Qt::Vertical);
        plt->setRangeZoom(Qt::Horizontal | Qt::Vertical);
        plotadded = true;
    }

    /* precise evolution (RK4 with a small step) */
    int n = 101;
    const double omega = 1.414213562373095;
    const double pi = 3.141592653589793;

    const double t_min = 0.0;
    const double t_max = 2*pi/omega;
    const double t_step = (t_max-t_min)/(n-1);

    QVector<double> x(n), v(n), t(n), tnT(n);

    x[0] = x0;
    v[0] = v0;
    t[0] = t_min;

    for (int i=1; i<n; i++) {
        t[i] = t_min+(t_max-t_min)*i/(n-1);
        tnT[i] = t[i]*omega/pi;
        rk41d(x[i-1],v[i-1],t[i-1],t_step,a,x[i],v[i]);
    }

    /* precise evolution plot */
    plt->graph(0)->clearData();

    QCPCurve *vx = new QCPCurve(plt->xAxis, plt->yAxis);

    switch (plot_type) {
    case 0: /* v over x */
        plt->addPlottable(vx);
        vx->setData(x, v);
        plt->xAxis->setLabel("x");
        plt->yAxis->setLabel("v");
        plt->xAxis->setRange(-4, 4);
        plt->yAxis->setRange(-3, 3);
        break;
    case 1: /* x over t */
        plt->graph(0)->addData(tnT,x);
        plt->xAxis->setLabel("t*omega/pi");
        plt->yAxis->setLabel("x");
        plt->xAxis->setRange(0, 2);
        plt->yAxis->setRange(-3, 3);
        break;
    case 2: /* v over t */
        plt->graph(0)->addData(tnT,v);
        plt->xAxis->setLabel("t*omega/pi");
        plt->yAxis->setLabel("v");
        plt->xAxis->setRange(0, 2);
        plt->yAxis->setRange(-3, 3);
        break;
    }
    plt->replot();

    plt->removePlottable(vx);
}
