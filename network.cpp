#include <math.h>
#include <stdlib.h>
#include <vector>

#define LAYERS 4
#define LAYER1 3
#define LAYER2 5
#define LAYER3 5
#define LAYER4 15
#define TOTAL (LAYER1 + LAYER2 + LAYER3 + LAYER4)
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
    int start = 0, end = setup[1];
    vector<double> weights;

    // Initialize weight and bias for layers 2 to last
    for(int layer = 1; layer < setup.size(); layer++) {
        for(int i = start; i < end; i++) {
            weights.clear();
            for(int j = 0; j < setup[layer-1]; j++) {
                weights.push_back(randNum());
            }
            neuron[i].setWeight(weights);
            neuron[i].setBias(randNum());
        }
        start += setup[layer];
        end += setup[layer+1];
    }  
}

// TODO: Standardize each layer calculation using setup vector
vector<double> Network::calculateOutput(vector<double> input) {

    cout << "in: " << input[0] << " " << input[1] << " " << input[2] << endl << endl;

    int start = 0, end = setup[1];

    // pass vector
    vector<double> pass;

    // Second to last layer
    for(int layer = 1; layer < setup.size(); layer++) {
        pass.clear();
        for(int i = start; i < end; i++) {
            double entry = neuron[i].getBias();

            cout << "b: " << neuron[i].getBias() << endl;
            cout << "w: ";

            for(int j = 0; j < setup[layer-1]; j++) {
                entry += neuron[i].getWeight()[j] * input[j];
                cout << neuron[i].getWeight()[j] << " ";
            }

            cout << "\nt: " << sigmoid(entry) << endl << endl;

            pass.push_back(sigmoid(entry));
        }
        start += setup[layer];
        end += setup[layer+1];
        cout << "--------------" << endl << endl;
    }

    return pass;
}