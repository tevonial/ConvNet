//
// Created by Connor on 8/4/2016.
//

#ifndef CONVNET_NEURON_H
#define CONVNET_NEURON_H

#include <vector>

class Neuron {
public:
    virtual double process(std::vector<double> *inputs) = 0;
    virtual void correct(std::vector<double> *d, std::vector<double> *w) = 0;
};

class Perceptron {
    unsigned int layer_index;
    unsigned int index;
    unsigned int num_inputs;

    std::vector<double> input;
    double output;

public:
    std::vector<double> weights;
    double delta;

    Perceptron(unsigned int layer_index, unsigned int index, unsigned int num_inputs);
    double process(std::vector<double> *in);
    void correct(std::vector<double> *d, std::vector<double> *w);
};

class FeatureMap {
    unsigned int dim, convoluted_dim;
    std::vector<double> input;
    std::vector<double> weights;
    std::vector<double> output;

public:
    FeatureMap(unsigned int dim);
    std::vector<double> process(std::vector<double> *in);
    void correct(std::vector<double> *d, std::vector<std::vector<double>> *w);

};

#endif //CONVNET_NEURON_H
