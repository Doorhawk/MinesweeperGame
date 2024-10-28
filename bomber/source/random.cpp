#include "random.h"

Random::Random() : gen(rd()) {};  // �������������� ��������� ��������� ��������� �� random_device
int Random::get_random_int(int min, int max) {
    std::uniform_int_distribution<> distrib(min, max); // ����������� ������������� �� min �� max
    return distrib(gen);
}
float Random::get_random_float(float min, float max) {
    std::uniform_real_distribution<> distrib(min, max);
    return distrib(gen);
}