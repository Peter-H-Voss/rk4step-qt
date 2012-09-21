#ifndef RK41D_H
#define RK41D_H

void rk41d(double x, double v, double t, double dt,
           double (*a)(double, double, double),
           double &xf, double &vf);

#endif // RK41D_H
