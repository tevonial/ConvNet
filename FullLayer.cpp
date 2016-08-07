//
// Created by Connor on 8/4/2016.
//


#include <iostream>
#include "Network.h"

FullLayer::FullLayer(unsigned int layer_index, unsigned int size, unsigned int num_inputs) {
    this->layer_index = layer_index;
    neurons = std::vector<Perceptron*>(size);
    output = std::vector<double>(size);

    for (unsigned int i=0; i<size; i++) {
        neurons[i] = new Perceptron(layer_index, i, num_inputs);
    }
}

void FullLayer::feed_forward(std::vector<double> *input) {
    for (int i=0; i<neurons.size(); i++) {
        output[i] = neurons[i]->process(input);
    }

    /*{
        using namespace std;

        cout << "Layer " << layer_index << " output: ";
        for (int i=0; i<output.size(); i++)
            cout << output[i] << " ";
        cout << endl << endl;
    }*/

    if (layer_index > 0) {
        Network::layers[layer_index - 1]->feed_forward(&output);
    } else {
        if (Network::BACKPROP) this->back_propagate(NULL, NULL);
    }
}

void FullLayer::back_propagate(std::vector<double> *d, std::vector<std::vector<double>> *w) {
    std::vector<std::vector<double>> _w;
    std::vector<double> _d;
    for (int i=0; i<neurons.size(); i++) {


        if (d != NULL)
            neurons[i]->correct(d, &((*w)[i]));
        else {
            neurons[i]->correct(NULL, NULL);
        }

        _d.push_back(neurons[i]->delta);
        _w.push_back(neurons[i]->weights);
    }

    rotate(&_w);

    if (layer_index + 1 != Network::layers.size())
        Network::layers[layer_index + 1]->back_propagate(&_d, &_w);
}

void FullLayer::rotate(std::vector<std::vector<double>> *in) {
    unsigned int dims[] = {in->size(), in->at(0).size()};
    std::vector<std::vector<double>> temp(dims[1], std::vector<double>(dims[0]));

    for (int y=0; y < dims[0]; y++) {
        for (int x=0; x < dims[1]; x++) {
            temp[x][y] = (*in)[y][x];
        }
    }

    (*in) = temp;
}
