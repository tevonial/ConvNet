cmake_minimum_required(VERSION 3.5)
project(ConvNet)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(SOURCE_FILES main.cpp Perceptron.cpp Network.cpp Network.h FullLayer.cpp Layer.h FeatureMap.cpp Neuron.h ConvolutionalLayer.cpp)

add_executable(ConvNet ${SOURCE_FILES})