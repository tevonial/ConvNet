#include <iostream>
#include <time.h>
#include <chrono>
#include "Network.h"

int main() {
    std::vector<double> in = {0.5, 0.1, 0.9, 0.5, 0.2};
    std::vector<double> out;
    //Network::build_full();

    /*for (int i=0; i<784; i++) {
        in.push_back(rand() % 100);
    }*/


    Network::build_full();

    using namespace std::chrono;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    for (int i=0; i<=10000; i++) {
        out = Network::process(&in);
        if (i % 20 == 0) {
            std::cout << "i=" << i << "  ";
            for (int a = 0; a < out.size(); a++)
                std::cout << out[a] << " ";
            std::cout << std::endl;
        }
    }



    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    double duration = duration_cast<milliseconds>( t2 - t1 ).count() / 1000.0;

    std::cout << std::endl << duration << std::endl;

    return 0;
}