#include <math.h>
#include <vector>

using namespace std;

// Each neuron has a input weights and a bias
class Neuron {

    public:
        Neuron();

        void setBias(float b);
        float getBias();

        void clearWeight();
        void setWeight(vector<float> input);
        vector<float> getWeight();

        float calculateOutput(vector<float> input);

    private:

        float bias;
        vector<float> weight;

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

void Neuron::clearWeight() {
    weight.clear();
}

void Neuron::setWeight(vector<float> input) {
    weight.clear();
    weight = input;
}

vector<float> Neuron::getWeight() {
    return weight;
}

float Neuron::calculateOutput(vector<float> input) {
    float output = bias;
    for(int i = 0; i < weight.size(); i++) {
        output += input[i] * weight[i];
    }
    return sigmoid(output);
}

Network::Network() {
    // Store the configuration for future reference
    setup.push_back(3);
    setup.push_back(10);
    setup.push_back(15);
}