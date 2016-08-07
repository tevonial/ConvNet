//
// Created by Connor on 8/4/2016.
//

#include <iostream>

#include "Network.h"

Perceptron::Perceptron(unsigned int layer_index, unsigned int index, unsigned int num_inputs) {
    this->layer_index = layer_index;
    this->index = index;
    this->num_inputs = num_inputs;

    for (int i=0; i<=num_inputs; i++) {  //<= for bias
        weights.push_back( ((double)(rand() % 2000) / 1000.0) - 1 );
    }
}

double Perceptron::process(std::vector<double> *in) {
    double activation = 0;

    if (num_inputs == 1) {                               //For input layer
        input = std::vector<double>(num_inputs);
        input[0] = (*in)[index];
    } else {                                            //For all other layers
        input = (*in);
    }

    for (int i = 0; i < input.size(); i++) {
        activation += weights[i] * input[i];
    }

    activation += weights[weights.size()-1];      //bias weight * 1

    output = Network::activate(activation);

    return output;
}

void Perceptron::correct(std::vector<double> *d, std::vector<double> *w) {
    if (layer_index == 0) {  //OUTPUT LAYER
        delta = (output - Network::target[index]) * Network::activate_prime(output);
    } else {                //HIDDEN LAYER
        delta = 0;
        for (int i=0; i < d->size(); i++) {
            delta += ((*d)[i] * (*w)[i]);
        }
        delta *= Network::activate_prime(output);
    }

    double delta_weight = delta * (-1) * Network::LEARNING_RATE;

    for (int i=0; i<weights.size(); i++) {
        if (i != input.size())
            weights[i] = weights[i] + (delta_weight * input[i]);
        else
            weights[i] = weights[i] + delta_weight;
    }
}