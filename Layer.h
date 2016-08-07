//
// Created by Connor on 8/4/2016.
//

#ifndef CONVNET_LAYER_H
#define CONVNET_LAYER_H

#include "Neuron.h"

class Layer {
public:
    virtual void feed_forward(std::vector<double> *in) = 0;
    virtual void back_propagate(std::vector<double> *d, std::vector<std::vector<double>> *w) = 0;
};

class FullLayer : public Layer {
    unsigned int layer_index;
    void rotate(std::vector<std::vector<double>> *in);

public:
    std::vector<Perceptron*> neurons;
    std::vector<double> output;

    FullLayer(unsigned int layer_index, unsigned int size, unsigned int num_inputs);

    void feed_forward(std::vector<double> *input);
    void back_propagate(std::vector<double> *d, std::vector<std::vector<double>> *w);
};

class ConvolutionalLayer : public Layer {
    unsigned int layer_index;
    unsigned int convoluted_dim;

    std::vector<double> pool(std::vector<double> in);

public:
    std::vector<FeatureMap*> features;
    std::vector<double> output;

    ConvolutionalLayer(unsigned int layer_index, unsigned int size, unsigned int dim);

    void feed_forward(std::vector<double> *in);
    void back_propagate(std::vector<double> *d, std::vector<std::vector<double>> *w);
};


#endif //CONVNET_LAYER_H