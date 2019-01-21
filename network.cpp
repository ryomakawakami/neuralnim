#include <math.h>
#include <vector>

using namespace std;

// Each neuron has a input weights and a bias
class Neuron {

    public:
        Neuron();

        void setBias(float b);
        float getBias();

        void clearWeights();
        void setWeights(vector<float> inputs);
        vector<float> getWeights();

        float calculateOutput(vector<float> inputs);

    private:

        float bias;
        vector<float> weights;

};

// 3 input neurons (passed in as vector), 10 hidden neurons, 15 output neurons
// The inputs are from the number in each pile
// The outputs are every possible move
class Network {
    public:
        Network();
        Neuron layer1[10], layer2[15];
    private:
        vector<int> setup;
};

// Converts value to value between -1 and 1
float sigmoid(float a) {
    return(1.0 / (1.0 + exp(a)));
}

// Neuron constructor
Neuron::Neuron() {
    bias = 0;
}

void Neuron::setBias(float b) {
    bias = b;
}

float Neuron::getBias() {
    return bias;
}

void Neuron::clearWeights() {
    weights.clear();
}

void Neuron::setWeights(vector<float> inputs) {
    weights.clear();
    weights = inputs;
}

vector<float> Neuron::getWeights() {
    return weights;
}

float Neuron::calculateOutput(vector<float> inputs) {
    float output = bias;
    for(int i = 0; i < weights.size(); i++) {
        output += inputs[i] * weights[i];
    }
    return sigmoid(output);
}

Network::Network() {
    // Store the configuration for future reference
    setup.push_back(3);
    setup.push_back(10);
    setup.push_back(15);
}