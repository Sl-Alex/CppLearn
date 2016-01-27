#ifndef FRAC_H
#define FRAC_H

struct Frac {
    int num;
    int denom;
};

void FracSimplify (Frac * value);
void FracMultiply (Frac * res, const Frac * a, const Frac * b);
void FracDivide   (Frac * res, const Frac * a, const Frac * b);
void FracAdd      (Frac * res, const Frac * a, const Frac * b);
void FracSubstract(Frac * res, const Frac * a, const Frac * b);
#endif // FRAC_H
