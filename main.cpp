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

    vector<double> input;
    input.push_back(1);
    input.push_back(1);
    input.push_back(1);

    vector<double> test = network.calculateOutput(input);

    for(int i = 0; i < test.size(); i++) {
        cout << test[i] << " ";
    }
}