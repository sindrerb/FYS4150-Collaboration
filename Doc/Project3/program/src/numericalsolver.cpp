#include "numericalsolver.h"

NumericalSolver::NumericalSolver() {
}

vec3 NumericalSolver::solveEuler(vec3 x, vec3 dx, double step) {
    return x + (dx * step);
}

vec3 NumericalSolver::solveVerletPos(vec3 x, vec3 dx, vec3 ddx, double step) {
    return x +  (step * dx) + (step*step * ddx)/2.0;
}

vec3 NumericalSolver::solveVerletPos(vec3 x, vec3 dx, vec3 ddx, double step, double stepSquarded) {
    return x +  (step * dx) + (stepSquarded * ddx)/2.0;
}

vec3 NumericalSolver::solveVerletVel(vec3 dx, vec3 ddx1, vec3 ddx0, double step) {
    return dx + step*(ddx1+ddx0)/2.0;
}

