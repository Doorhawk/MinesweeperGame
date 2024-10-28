#include "random.h"

Random::Random() : gen(rd()) {};  // »нициализируем генератор случайным значением от random_device
int Random::get_random_int(int min, int max) {
    std::uniform_int_distribution<> distrib(min, max); // –авномерное распределение от min до max
    return distrib(gen);
}
float Random::get_random_float(float min, float max) {
    std::uniform_real_distribution<> distrib(min, max);
    return distrib(gen);
}