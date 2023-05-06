#pragma once

#include <random>

class RandomGenerator
{
public:

	RandomGenerator()
	{
		srand(time(0));
	};

	// https://stackoverflow.com/questions/686353/random-float-number-generation
	static float randomFloat(float min, float max)
	{
		return min + static_cast <float>(rand() / (static_cast <float>(RAND_MAX / max)));
	};

	static int randomInt(int min, int max)
	{
		return min + rand() % ((max + 1) - min);
	};
};