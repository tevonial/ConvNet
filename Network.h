//
// Created by Connor on 8/4/2016.
//

#ifndef CONVNET_NETWORK_H
#define CONVNET_NETWORK_H


#include "Layer.h"

#include <vector>

namespace Network {

    extern double LEARNING_RATE;
    extern bool BACKPROP;

    extern std::vector<Layer*> layers;
    extern std::vector<double> target;

    extern void build_conv();
    extern void build_full();
    extern std::vector<double> process(std::vector<double> *input);

    extern double activate(double activation);
    extern double activate_prime(double activation);

    /*    static double LEARNING_RATE = 0;
    static bool BACKPROP = false;

    static std::vector<Layer*> layers;
    static std::vector<double> target;

    static void build_conv();
    static void build_full();
    static std::vector<double> process(std::vector<double> *input);

    static double activate(double activation);
    static double activate_prime(double activation);*/
}

#endif //CONVNET_NETWORK_H
