#include "qcustomplot.h"
#include "rk41d.h"

void myplot(QCustomPlot *plt, int plot_type, double x0, double v0, double dt,
            double (*a)(double, double, double))
{
    static QCPCurve *vx;
    static QCPItemText *textLabel;
    static QCPItemLine *arrow;

    /* plot initialisation */
    static bool plotadded = false;
    if (!plotadded) {
        vx = new QCPCurve(plt->xAxis, plt->yAxis);
        plt->addPlottable(vx);

        // add the text label indicating t=0 point:
        textLabel = new QCPItemText(plt);
        plt->addItem(textLabel);
        textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
        textLabel->setText("t = 0");

        // add the arrow:
        arrow = new QCPItemLine(plt);
        plt->addItem(arrow);
        arrow->start->setParentAnchor(textLabel->bottom);
        arrow->setHead(QCPLineEnding::esSpikeArrow);

        plt->addGraph();
        plt->addGraph();

        plt->graph(1)->setLineStyle(QCPGraph::lsNone);
        plt->graph(1)->setScatterStyle(QCP::ssCircle);
        plt->graph(1)->setScatterSize(8);

        plt->setRangeDrag(Qt::Horizontal | Qt::Vertical);
        plt->setRangeZoom(Qt::Horizontal | Qt::Vertical);

        plotadded = true;
    }

    int n = 101;
    const double omega = 1.414213562373095;
    const double pi = 3.141592653589793;

    const double t_min = 0.0;
    const double t_max = 2*pi/omega;
    const double t_step = (t_max-t_min)/(n-1);

    /* RK4 step visualisation */

    QVector<double> rkx(5), rkv(5), rkt(5), rka(5);

    rkx[0] = x0;
    rkv[0] = v0;
    rka[0] = (*a)(rkx[0], rkv[0], t_min);

    rkx[1] = x0 + 0.5*rkv[0]*dt;
    rkv[1] = v0 + 0.5*rka[0]*dt;
    rka[1] = (*a)(rkx[1], rkv[1], t_min + 0.5*dt);

    rkx[2] = x0 + 0.5*rkv[1]*dt;
    rkv[2] = v0 + 0.5*rka[1]*dt;
    rka[2] = (*a)(rkx[2], rkv[2], t_min + 0.5*dt);

    rkx[3] = x0 + rkv[2]*dt;
    rkv[3] = v0 + rka[2]*dt;
    rka[3] = (*a)(rkx[3], rkv[3], t_min + dt);

    rkx[4] = x0 + (dt/6.0)*(rkv[0] + 2*rkv[1] + 2*rkv[2] + rkv[3]);
    rkv[4] = v0 + (dt/6.0)*(rka[0] + 2*rka[1] + 2*rka[2] + rka[3]);

    rkt[0] = t_min;
    rkt[1] = rkt[2] = t_min+dt/2.0*omega/pi;
    rkt[3] = rkt[4] = t_min+dt*omega/pi;

    /* precise evolution (RK4 with a small step) */

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
    plt->graph(1)->clearData();
    vx->clearData();

    arrow->setVisible(plot_type==0);
    textLabel->setVisible(plot_type==0);

    switch (plot_type) {
    case 0: /* v over x */
        plt->graph(1)->setData(rkx, rkv);

        vx->setData(x, v);
        plt->xAxis->setLabel("x");
        plt->yAxis->setLabel("v");
        plt->xAxis->setRange(-4, 4);
        plt->yAxis->setRange(-3, 3);

        textLabel->position->setCoords(x[0]+0.6,v[0]+0.4);
        arrow->end->setCoords(x[0],v[0]);

        break;

    case 1: /* x over t */
        plt->graph(1)->setData(rkt, rkx);

        plt->graph(0)->setData(tnT,x);
        plt->xAxis->setLabel("t*omega/pi");
        plt->yAxis->setLabel("x");
        plt->xAxis->setRange(0, 2);
        plt->yAxis->setRange(-3, 3);
        break;

    case 2: /* v over t */
        plt->graph(1)->setData(rkt, rkv);

        plt->graph(0)->setData(tnT,v);
        plt->xAxis->setLabel("t*omega/pi");
        plt->yAxis->setLabel("v");
        plt->xAxis->setRange(0, 2);
        plt->yAxis->setRange(-3, 3);
        break;
    }

    plt->replot();
}



