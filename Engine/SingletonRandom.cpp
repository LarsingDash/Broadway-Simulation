//
// Created by larsv on 16/10/2024.
//

#include "SingletonRandom.hpp"

SingletonRandom SingletonRandom::instance;

SingletonRandom& SingletonRandom::get_instance() { return instance; }

int SingletonRandom::RandomInt(int lower, int upper) {
	std::uniform_int_distribution dist(lower, upper);
	return dist(engine);
}

float SingletonRandom::RandomFloat(float lower, float upper) {
	std::uniform_real_distribution<float> dist(lower, upper);
	return dist(engine);
}

