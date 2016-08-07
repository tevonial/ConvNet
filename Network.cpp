//
// Created by Connor on 8/4/2016.
//

#include <cmath>
#include "Network.h"

namespace Network {
    double LEARNING_RATE;
    bool BACKPROP;

    std::vector<Layer*> layers;
    std::vector<double> target;

    double activate(double activation) {
        return 1 / (1 + exp(-1 * activation));
    }

    double activate_prime(double activation) {
        return activation * (1.0 - activation);
    }

    void build_conv() {
        LEARNING_RATE = 0.01;
        target = {0, 0, 1, 0, 0, 0, 0, 0, 0, 1};
        BACKPROP = true;

        layers.push_back(new FullLayer(layers.size(), 3, 144));
        layers.push_back(new ConvolutionalLayer(layers.size(), 1, 5));
        layers.push_back(new FullLayer(layers.size(), 784, 1));
    }

    void build_full() {
        LEARNING_RATE = 0.01;
        target = {0, 0, 1, 0, 0, 0, 0, 0, 0, 1};
        BACKPROP = true;

        layers.push_back(new FullLayer(layers.size(), 10, 50));
        layers.push_back(new FullLayer(layers.size(), 50, 5));
        layers.push_back(new FullLayer(layers.size(), 5, 1));
    }

    std::vector<double> process(std::vector<double> *input) {
        layers.at(layers.size() - 1)->feed_forward(input);
        return ((FullLayer *) layers.at(0))->output;
    }

}