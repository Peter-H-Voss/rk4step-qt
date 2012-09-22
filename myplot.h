#ifndef MYPLOT_H
#define MYPLOT_H

void myplot(QCustomPlot *plt, int plot_type, double x0, double v0, double dt,
            double (*a)(double, double, double));

#endif // MYPLOT_H
