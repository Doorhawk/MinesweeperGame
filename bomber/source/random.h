#pragma once
#include <random>

class Random {
public:
    Random();  

    int get_random_int(int min, int max);
    float get_random_float(float min, float max);
private:
    std::random_device rd;  
    std::mt19937 gen;     
};
