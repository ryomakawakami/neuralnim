#include <math.h>
#include <stdlib.h>
#include <vector>

#define LAYERS 3
#define LAYER1 3
#define LAYER2 10
#define LAYER3 15
#define TOTAL (LAYER1 + LAYER2 + LAYER3)
#define NUM_NEURONS (LAYER2 + LAYER3)

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
        Neuron neuron[NUM_NEURONS];         // LAYER2 + LAYER3
        void initialize();
        vector<double> calculateOutput(vector<double> input);
};

// Converts value to value between -1 and 1
double sigmoid(double a) {
    return(1.0 / (1.0 + exp(a)));
}

// Generates random number in [-1, 1]
double randNum() {
    return (double) rand() / RAND_MAX * 2 - 1;
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

// TODO: Make more modular (maybe store LAYER info in vector)
void Network::initialize() {
    // Initialize layer 2 weight and bias
    for(int i = 0; i < LAYER2; i++) {
        vector<double> weights;
        for(int j = 0; j < LAYER1; j++) {
            weights.push_back(randNum());
        }
        neuron[i].setWeight(weights);
        neuron[i].setBias(randNum());
    }

    // Initialize layer 3 weight and bias
    for(int i = LAYER2; i < (LAYER2+LAYER3); i++) {
        vector<double> weights;
        for(int j = 0; j < LAYER2; j++) {
            weights.push_back(randNum());
        }
        neuron[i].setWeight(weights);
        neuron[i].setBias(randNum());
    }
}

vector<double> Network::calculateOutput(vector<double> input) {
    // From second layer to last layer
    for(int layer = 1; layer < LAYERS; layer++) {

    }
}