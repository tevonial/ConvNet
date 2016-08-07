//
// Created by Connor on 8/4/2016.
//

#include <cstdlib>
#include "Network.h"

FeatureMap::FeatureMap(unsigned int dim) {
	this->dim = dim;
	this->convoluted_dim = 28 - dim + 1;

	for (int i=0; i<=dim*dim; i++)
		weights.push_back( ((double)(rand() % 2000) / 2000.0) - 1 );
}

std::vector<double> FeatureMap::process(std::vector<double> *in) {
    input = *in;
	double activation;
	output.clear();

	for (int y=0; y<convoluted_dim; y++) {
		for (int x=0; x<convoluted_dim; x++) {

			activation = weights[weights.size() - 1];

			for (int y2=0; y2<dim; y2++) {
				for (int x2=0; x2<dim; x2++) {
					activation += weights[y2*dim + x2]
							* input[(y + y2)*28 + (x + x2)];
				}
			}

			output.push_back(Network::activate(activation));
		}
	}

	return output;
}

void FeatureMap::correct(std::vector<double> *d, std::vector<std::vector<double>> *w) {
    std::vector<double> _w;
    double d_weight, temp;

    for (int a=0; a<dim; a++) {
        for (int b=0; b<dim; b++) {

            d_weight = 0.0;

            for (int y=0; y<convoluted_dim; y++) {
                for (int x=0; x<convoluted_dim; x++) {

                    _w = (*w)[(y/2)*(convoluted_dim/2) + x/2];
                    temp = 0.0;

                    for (int i=0; i<d->size(); i++) {
                        temp += (*d)[i] * _w[i] * input[(y+a) * 28 + (x+b)];
                    }

                    d_weight += temp * Network::activate_prime(output[y*convoluted_dim + x]);

                }
            }

            d_weight *= (-1) * Network::LEARNING_RATE;
            weights[a*dim + b] += d_weight;

        }
    }
}