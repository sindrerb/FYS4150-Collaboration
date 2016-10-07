#ifndef NUMERICALSOLVER_H
#define NUMERICALSOLVER_H
#include "vec3.h"
#include "math.h"

class NumericalSolver {

public:

    static vec3 solveEuler(vec3 x, vec3 dx, double step);

private:
    NumericalSolver();
};

#endif // NUMERICALSOLVER_H
