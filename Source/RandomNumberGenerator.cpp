//
// Created by Krzysztof Sawicki on 17/05/2024.
//

#include <random>

class RandomNumberGenerator
{
private:
    std::mt19937 rng; // Mersenne Twister random number generator

public:
    // get Random index of table without repeating
    static unsigned int getRandomIndex(RandomNumberGenerator* rng, const std::vector<bool>& seedUsed)
    {
        unsigned int index = rng->generate(0, seedUsed.size() - 1);
        while (seedUsed[index])
        {
            index = rng->generate(seedUsed.size() - 1);
        }
        return index;
    }

    // Default constructor
    RandomNumberGenerator()
    {
        // Initialize the random number generator with a non-deterministic seed
        rng.seed(std::random_device{}());
    }

    // Constructor with seed
    RandomNumberGenerator(unsigned int seed)
    {
        // Initialize the random number generator with the provided seed
        rng.seed(seed);
    }

    // Generate a random number in the range [min, max]
    int generate(int min, int max)
    {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }

    // Generate a random number in the range [0, max]
    int generate(int max)
    {
        return generate(0, max);
    }

    // Generate a random number
    int generate()
    {
        return generate(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    }

    // Generate a random float number in the range [min, max]
    float generateFloat(float min, float max)
    {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(rng);
    }

    // Generate a random float number in the range [0, max]
    float generateFloat(float max)
    {
        return generateFloat(0.0f, max);
    }

    // Generate a random float number
    float generateFloat()
    {
        return generate(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
    }
};