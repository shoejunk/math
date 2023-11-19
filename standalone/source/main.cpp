#include <assert.h>

import stk.math;

#pragma warning(push)
#pragma warning(disable: 5050) // _M_FP_PRECISE is defined in current command line and not in module command line
import std.core;
#pragma warning(pop)

using namespace stk;

int main(int argc, char* argv[])
{
	if (argc > 2)
	{
		if (strcmp(argv[1], "NextPrime") == 0)
		{
			int n = atoi(argv[2]);
			auto prime = next_prime((uint32_t)n);
			if (prime == 0)
			{
				std::cout << "Failure. The next prime is larger than would fit in a uint32_t so I cannot compute it." << std::endl;
			}
			else
			{
				std::cout << "The next prime number that comes after " << n << " is " << prime << std::endl;
			}
		}
		else if (argc > 3 && (strcmp(argv[1], "Random") == 0))
		{
			auto seed = atoi(argv[2]);
			auto max = atoi(argv[3]);
			auto r = det_rand_int<uint32_t>(static_cast<uint32_t>(seed), static_cast<uint32_t>(max));
			std::cout << r << std::endl;
		}
		else if (argc > 3 && (strcmp(argv[1], "RandomInt") == 0))
		{
			auto min = atoi(argv[2]);
			auto max = atoi(argv[3]);
			stk::c_rand r;
			auto r_int = r.rand_int(min, max);
			std::cout << r_int << std::endl;
		}
		else if (argc > 3 && (strcmp(argv[1], "RandomFloat") == 0))
		{
			auto min = atof(argv[2]);
			auto max = atof(argv[3]);
			stk::c_rand r;
			auto r_float = r.rand_float(min, max);
			std::cout << r_float << std::endl;
		}
	}
	else
	{
		std::cout << "Enter \"NextPrime <X>\" to find the next prime that comes after X." << std::endl;
		std::cout << "Enter \"Random <Seed> <Max>\" to find a random number with the given Seed in the range [0, Max)." << std::endl;
		std::cout << "Enter \"RandomInt <Min> <Max>\" to find a random int in the range [Min, Max]." << std::endl;
		std::cout << "Enter \"RandomFloat <Min> <Max>\" to find a random number in the range from Min to Max." << std::endl;
	}

	int32_t test[] = { 5, 4, 4, 8, 2, -1, 0, 3, 10, 9, 7, 6, 1, 2, 3, 4, 5, 6, 7, 8 };
	auto size = sizeof(test) / sizeof(int32_t);
	int32_t test_sorted[] = { 10, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 4, 4, 3, 3, 2, 2, 1, 0, -1 };
	auto size_sorted = sizeof(test_sorted) / sizeof(int32_t);

	c_vec2i v1(1, 2);
	c_vec2f v2 = c_vec2f(v1);

	c_rot angle = c_rot::from_deg(90.0f);
	c_rot angle2 = c_rot::from_rad(std::numbers::pi_v<float> / 2.0f);
	assert(angle == angle2);

	return 0;
}
