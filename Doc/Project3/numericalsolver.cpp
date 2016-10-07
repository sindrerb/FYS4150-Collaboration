#include "numericalsolver.h"

NumericalSolver::NumericalSolver() {
}

vec3 NumericalSolver::solveEuler(vec3 x, vec3 dx, double step) {
    return x + (dx * step);
}

