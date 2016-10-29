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

public:
    Ising2D();
    Ising2D(int spins);
    void InitializeGroundState();
    void InitializeRandomState();
    void delteLattice();
    void Metropolis(int nSpin,int maxCycles, double temperature);
};

#endif // ISING2D_H
