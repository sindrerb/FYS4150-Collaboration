#include "numericalsolver.h"

NumericalSolver::NumericalSolver() {
}

vec3 NumericalSolver::solveEuler(vec3 x, vec3 dx, double step) {
    return x + (dx * step);
}

vec3 NumericalSolver::solveVerletPos(vec3 x, vec3 dx, vec3 ddx, double step) {
    return x +  (step * dx) + (step*step * ddx)/2.0;
}

vec3 NumericalSolver::solveVerletPos(vec3 x, vec3 dx, vec3 ddx, double step, double halfStepSquared) {
    return x +  (step * dx) + halfStepSquared * ddx;
}

vec3 NumericalSolver::solveVerletVel(vec3 dx, vec3 ddx1, vec3 ddx0, double halfStep) {
    return dx + halfStep * (ddx1 + ddx0);
}

