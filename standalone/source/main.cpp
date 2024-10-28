#include <cassert>

import se;
import stk.log;
import stk.math;

using namespace stk;

int main(int argc, char* argv[])
{
	if (argc > 2)
	{
		if (se::strcmp(argv[1], "NextPrime") == 0)
		{
			int n = se::atoi(argv[2]);
			auto prime = next_prime((se::uint32_t)n);
			if (prime == 0)
			{
				se::cout << "Failure. The next prime is larger than would fit in a uint32_t so I cannot compute it." << se::endl;
			}
			else
			{
				se::cout << "The next prime number that comes after " << n << " is " << prime << se::endl;
			}
		}
		else if (argc > 3 && (strcmp(argv[1], "Random") == 0))
		{
			auto seed = se::atoi(argv[2]);
			auto max = se::atoi(argv[3]);
			auto r = det_rand_int<se::uint32_t>(static_cast<se::uint32_t>(seed), static_cast<se::uint32_t>(max));
			se::cout << r << se::endl;
		}
		else if (argc > 3 && (strcmp(argv[1], "RandomInt") == 0))
		{
			auto min = atoi(argv[2]);
			auto max = atoi(argv[3]);
			stk::c_rand r;
			auto r_int = r.rand_int(min, max);
			se::cout << r_int << se::endl;
		}
		else if (argc > 3 && (strcmp(argv[1], "RandomFloat") == 0))
		{
			auto min = se::atof(argv[2]);
			auto max = se::atof(argv[3]);
			stk::c_rand r;
			auto r_float = r.rand_float(min, max);
			se::cout << r_float << se::endl;
		}
	}
	else
	{
		se::cout << "Enter \"NextPrime <X>\" to find the next prime that comes after X." << se::endl;
		se::cout << "Enter \"Random <Seed> <Max>\" to find a random number with the given Seed in the range [0, Max)." << se::endl;
		se::cout << "Enter \"RandomInt <Min> <Max>\" to find a random int in the range [Min, Max]." << se::endl;
		se::cout << "Enter \"RandomFloat <Min> <Max>\" to find a random number in the range from Min to Max." << se::endl;
	}

	se::int32_t test[] = { 5, 4, 4, 8, 2, -1, 0, 3, 10, 9, 7, 6, 1, 2, 3, 4, 5, 6, 7, 8 };
	auto size = sizeof(test) / sizeof(se::int32_t);
	se::int32_t test_sorted[] = { 10, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 4, 4, 3, 3, 2, 2, 1, 0, -1 };
	auto size_sorted = sizeof(test_sorted) / sizeof(se::int32_t);

	constexpr c_vec2i v1(1, 2);
	constexpr c_vec2f v2 = c_vec2f(v1);

	constexpr c_angle angle = 90._deg;
	constexpr c_angle angle2 = c_angle::from_rad(se::numbers::pi_v<long double> / 2L);
	constexpr c_angle angle3 = 180_deg;
	constexpr c_angle angle4 = c_angle::from_rad(se::numbers::pi_v<long double>);
	constexpr c_angle angle5 = -90_deg;
	constexpr c_angle angle6 = 270.0_deg;
	static_assert(angle == angle2);
	static_assert(angle + angle2 == angle3);
	static_assert(angle3 == angle4);
	static_assert(angle5 == angle6);
	static_assert(-2_rad + 1.5_rad == -0.5_rad);
	c_vec2i v3 = angle.rot(v1);
	assert(v3 == c_vec2i(-2, 1));
	
	// True Reals:
	c_true_real tr1(se::numeric_limits<se::uint64_t>::max());
	debugln("tr1: {}", tr1.to_string());
	c_true_real tr2(1);
	c_true_real tr3 = tr1 + tr2;
	debugln("tr3: {}", tr3.to_string());
	return 0;
}
