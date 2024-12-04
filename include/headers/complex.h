#ifndef COMPLEX_H
#define COMPLEX_H

class complex {
    public:
        double real;
        double im;

        complex(double realh, double imh);
        void add(complex* other);
        void multiply(complex* other);

        static int test(complex* z, complex* c, int threshold);
};

#endif