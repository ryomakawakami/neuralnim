#include <math.h>

using namespace std;

// 3 input neurons, 10 hidden neurons, 15 output neurons
// The inputs are from the number in each pile
// The outputs are every possible move
class Network {

};

// Each neuron has a weight and a bias
class Neuron {
    public:
        void setWeight(float w), setBias(float b);
        float getWeight(), getBias();
    private:
        float weight, bias;
};

// Converts value to value between -1 and 1
float sigmoid(float a) {
    return(1.0 / (1.0 + exp(a)));
}

void Neuron::setWeight(float w) {
    weight = w;
}

void Neuron::setBias(float b) {
    bias = b;
}

float Neuron::getWeight() {
    return weight;
}

float Neuron::getBias() {
    return bias;
}