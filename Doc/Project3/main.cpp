#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include "satellite.h"
#include "matrix.h"

using namespace std;



int main(){

    string satelliteName;

    cout << "Type a planet name: ";
    cin >> satelliteName;

    Satellite satelite1(satelliteName);

    cout << "You made planet: " << satelite1.getSatelliteName() <<endl;
}
