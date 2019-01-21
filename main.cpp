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
    network.initialize();
    for(int i = 0; i < NUM_NEURONS; i++) {
        for(int j = 0; j < network.neuron[i].getWeight().size(); j++) {
            cout << "Neuron " << i << "\t" << network.neuron[i].getWeight()[j] << endl;
        }
    }
}