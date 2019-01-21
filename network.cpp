#include <math.h>
#include <stdlib.h>
#include <vector>

using namespace std;

// Each neuron has a input weights and a bias
class Neuron {

    public:
        Neuron();

        void setBias(double b);
        double getBias();

        void clearWeight();
        void setWeight(vector<double> input);
        vector<double> getWeight();

        double calculateOutput(vector<double> input);

    private:

        double bias;
        vector<double> weight;

};

// 3 input neurons (passed in as vector), 10 hidden neurons, 15 output neurons
// The inputs are from the number in each pile
// The outputs are every possible move
class Network {
    public:
        Network();
        Neuron neuron[25];         // 10 hidden, 15 output
        vector<double> calculateOutput(vector<double> input);
    private:
        vector<int> setup;
};

// Converts value to value between -1 and 1
double sigmoid(double a) {
    return(1.0 / (1.0 + exp(a)));
}

// Generates random number in [0, 1]
double randNum() {
    return (double) rand() / RAND_MAX;
}

// Neuron constructor
Neuron::Neuron() {
    bias = 0;
}

void Neuron::setBias(double b) {
    bias = b;
}

double Neuron::getBias() {
    return bias;
}

void Neuron::clearWeight() {
    weight.clear();
}

void Neuron::setWeight(vector<double> input) {
    weight.clear();
    weight = input;
}

vector<double> Neuron::getWeight() {
    return weight;
}

double Neuron::calculateOutput(vector<double> input) {
    double output = bias;
    for(int i = 0; i < weight.size(); i++) {
        output += input[i] * weight[i];
    }
    return sigmoid(output);
}

Network::Network() {
    setup.push_back(3);
    setup.push_back(10);
    setup.push_back(15);
}

vector<double> Network::calculateOutput(vector<double> input) {
    // From second layer to last layer
    for(int layer = 1; layer < setup.size(); layer++) {

    }
}