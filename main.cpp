#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "game.cpp"
#include "network.cpp"

using namespace std;

int main() {
    // Seed random
    srand(time(NULL));
    
    Network network;
    cout << network.neuron[0].getBias() << endl;
}