//
// Created by Connor on 8/4/2016.
//


#include <iostream>
#include "Network.h"

ConvolutionalLayer::ConvolutionalLayer(unsigned int layer_index, unsigned int size, unsigned int dim) {
    this->layer_index = layer_index;
    this->convoluted_dim = 28 - dim + 1;

    for (int i=0; i<size; i++)
        features.push_back(new FeatureMap(dim));
}

void ConvolutionalLayer::feed_forward(std::vector<double> *in) {
    output.clear();
    std::vector<double> temp;

    for (int i=0; i<features.size(); i++) {
        temp = pool(features[i]->process(in));
        output.insert(output.end(), temp.begin(), temp.end());
    }

    if (layer_index > 0) {
        Network::layers[layer_index - 1]->feed_forward(&output);
    } else {
        if (Network::BACKPROP) this->back_propagate(nullptr, nullptr);
    }
}

void ConvolutionalLayer::back_propagate(std::vector<double> *d, std::vector<std::vector<double>> *w) {
    int convoluted_size = (convoluted_dim * convoluted_dim) / 4;

    for (int i=0; i<features.size(); i++) {

        int index = i*convoluted_size;
        std::vector<std::vector<double>> sub_vector(w->begin()+index, w->begin()+index+convoluted_size);

        features[i]->correct(d, &sub_vector);
    }

    if (layer_index + 1 != Network::layers.size())
        Network::layers[layer_index + 1]->back_propagate(d, w);
}

std::vector<double> ConvolutionalLayer::pool(std::vector<double> in) {
    std::vector<double> output;

    for (int y=0; y<convoluted_dim-2; y+=2) {
        for (int x=0; x<convoluted_dim-2; x+=2) {
            output.push_back(
                    std::max(in[y*convoluted_dim + x],
                    std::max(in[y*convoluted_dim + x + 1],
                    std::max(in[(y+1)*convoluted_dim + x],
                             in[(y+1)*convoluted_dim + x + 1])))
            );
        }
    }

    return output;
}
