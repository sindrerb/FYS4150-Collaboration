#ifndef NUMERICALSOLVER_H
#define NUMERICALSOLVER_H
#include "vec3.h"
#include "math.h"

class NumericalSolver {

public:

    static vec3 solveEuler(vec3 x, vec3 dx, double step);
    static vec3 solveVerletPos(vec3 x, vec3 dx, vec3 ddx, double step);
    static vec3 solveVerletPos(vec3 x, vec3 dx, vec3 ddx, double step, double stepSquared);
    static vec3 solveVerletVel(vec3 dx, vec3 ddx1, vec3 ddx0, double step);

private:
    NumericalSolver();
};

#endif // NUMERICALSOLVER_H
