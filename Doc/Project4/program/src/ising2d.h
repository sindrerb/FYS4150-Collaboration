#ifndef ISING2D_H
#define ISING2D_H
#include <random>

inline int periodic(int i, int limit, int add) {
  return (i+limit+add) % (limit);
}

class Ising2D
{
private:
    int nSpin=0;
    int **lattice;
    double energy;
    double magneticMoment;
    double w[17];
    double average[5];

public:
    Ising2D();
    Ising2D(int spins);
    void InitializeGroundState();
    void InitializeRandomState();
    void generate(int start, int end, double temperature);
    void delteLattice();
    void Metropolis();
    double *fetch();
};

#endif // ISING2D_H
