
void rk41d(double x, double v, double t, double dt,
           double (*a)(double, double, double),
           double &xf, double &vf)
{
    double  x1, v1, a1,
            x2, v2, a2,
            x3, v3, a3,
            x4, v4, a4;

    x1 = x;
    v1 = v;
    a1 = (*a)(x1, v1, t);

    x2 = x + 0.5*v1*dt;
    v2 = v + 0.5*a1*dt;
    a2 = (*a)(x2, v2, t + 0.5*dt);

    x3 = x + 0.5*v2*dt;
    v3 = v + 0.5*a2*dt;
    a3 = (*a)(x3, v3, t + 0.5*dt);

    x4 = x + v3*dt;
    v4 = v + a3*dt;
    a4 = (*a)(x4, v4, t + dt);

    xf = x + (dt/6.0)*(v1 + 2*v2 + 2*v3 + v4);
    vf = v + (dt/6.0)*(a1 + 2*a2 + 2*a3 + a4);
}
