#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "game.cpp"
#include "network.cpp"

using namespace std;

int main() {
    Network network;

    cout << network.layer1[0].getWeight();
}