#include <math.h>
#include <stdlib.h>
#include <vector>

#define LAYER1 3
#define LAYER2 5
#define LAYER3 5
#define LAYER4 15
#define NUM_NEURONS (LAYER2 + LAYER3 + LAYER4)

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

// 3 input neurons (passed in as vector), 10 hidden neurons (2 layers), 15 output neurons
// The inputs are from the number in each pile
// The outputs are every possible move
class Network {
    public:
        Network();
        Neuron neuron[NUM_NEURONS];         // LAYER2 + LAYER3 + LAYER3
        void initialize();
        vector<double> calculateOutput(vector<double> input);
    private:
        vector<int> setup;
};

// Converts value to value between -1 and 1
double sigmoid(double a) {
    return(1.0 / (1.0 + exp(-a)));
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

Network::Network() {
    // Store configuration in vector
    setup.push_back(LAYER1);
    setup.push_back(LAYER2);
    setup.push_back(LAYER3);
    setup.push_back(LAYER4);
}

void Network::initialize() {
    // start and end are the indexes for neurons in current layer
    int start = 0, end = setup[1];
    // weights is a temp vector to push random values to neurons
    vector<double> weights;

    // Initialize weight and bias for second layer to last layer
    for(int layer = 1; layer < setup.size(); layer++) {
        // For the neurons in current layer
        for(int i = start; i < end; i++) {
            // Clear temp vector
            weights.clear();
            // Add random weights to temp vector
            for(int j = 0; j < setup[layer-1]; j++) {
                weights.push_back(randNum());
            }
            // Set weight vector as temp vector
            neuron[i].setWeight(weights);
            // Set bias as random number
            neuron[i].setBias(randNum());
        }
        // Shift indexes to next layer
        start += setup[layer];
        end += setup[layer+1];      // Seg fault?
    }  
}

vector<double> Network::calculateOutput(vector<double> input) {
    // start and end are the indexes for neurons in current layer
    int start = 0, end = setup[1];

    // pass is the vector passed between layers
    vector<double> pass;

    // Second layer to last layer
    for(int layer = 1; layer < setup.size(); layer++) {
        // Clear the pass vector
        pass.clear();
        // For each neuron in current layer
        for(int i = start; i < end; i++) {
            // entry holds each entry into pass vector
            double entry = neuron[i].getBias();
            // For each weight
            for(int j = 0; j < setup[layer-1]; j++) {
                // Dot product of weights and pass vector (input vector for layer 2)
                if(layer != 1) {
                    entry += neuron[i].getWeight()[j] * pass[j];
                }
                else {
                    entry += neuron[i].getWeight()[j] * input[j];
                }
            }
            // Add new entry to pass vector
            pass.push_back(sigmoid(entry));
        }
        // Shift indexes to next layer
        start += setup[layer];
        end += setup[layer+1];
    }
    // Return the pass vector
    return pass;
}