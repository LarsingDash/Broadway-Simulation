//
// Created by larsv on 16/10/2024.
//

#ifndef BROADWAY_SIMULATION_SINGLETONRANDOM_HPP
#define BROADWAY_SIMULATION_SINGLETONRANDOM_HPP

#include <iostream>
#include <random>

class SingletonRandom {
	public:
		static SingletonRandom& get_instance();

		SingletonRandom(const SingletonRandom&) = delete;
		SingletonRandom(SingletonRandom&&) = delete;
		SingletonRandom& operator=(const SingletonRandom&) = delete;
		SingletonRandom& operator=(SingletonRandom&&) = delete;
		
		int RandomInt(int lower, int upper);
		float RandomFloat(float lower, float upper);

		[[nodiscard]] std::default_random_engine& getEngine() { return engine; }
	private:
		static SingletonRandom instance;

		std::random_device device;
		std::default_random_engine engine {device()};

		SingletonRandom() = default;
};

#endif //BROADWAY_SIMULATION_SINGLETONRANDOM_HPP
