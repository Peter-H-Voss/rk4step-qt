#include "pot.h"

double (*chosen_a(int comboindex))(double, double, double)
{
    switch (comboindex) {
        case 0:
            return &a_harmonic;
    }
}

double a_harmonic(double x, double v, double t)
/* Harmonic potential: V(x) = x^2. */
{
    return -2.0*x;
}
