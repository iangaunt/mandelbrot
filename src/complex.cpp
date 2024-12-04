#include "headers/complex.h"

complex::complex(double realh, double imh) {
    real = realh;
    im = imh;
}

void complex::add(complex* other) {
    real += other->real;
    im += other->im;
}

void complex::multiply(complex* other) {
    double realp = real * other->real - im * other->im;
    double imp = real * other->im + im * other->real;

    real = realp;
    im = imp;
}

int complex::test(complex* z, complex* c, int threshold) {
    for (int i = 0; i < threshold; i++) {
        z->multiply(z);
        z->add(c);

        if (z->real * z->real + z->im * z->im >= 4) return i;
    }

    return threshold;
}