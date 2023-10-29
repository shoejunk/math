export module stk.math;

#pragma warning(push)
#pragma warning(disable: 5050) // _M_FP_PRECISE is defined in current command line and not in module command line
import std.core;
#pragma warning(pop)

export namespace stk
{
	// Returns the next prime number after x. Returns 0 if there is no prime number after uX that fits in a uint32_t.
	constexpr uint32_t next_prime(uint32_t x)
	{
		if (x < 2)
			return 2;

		if (x == 2)
			return 3;

		if (x >= 4294960003) // Largest prime number that fits in a uint32_t.
			return 0;

		uint32_t prime = (x + 1) | 1;
		while (true)
		{
			bool is_prime = true;
			for (uint32_t divisor = 3; divisor * divisor <= prime; divisor += 2)
			{
				if (prime % divisor == 0)
				{
					is_prime = false;
					break;
				}
			}

			if (is_prime)
				return prime;

			prime += 2;
		}
	}
	static_assert(next_prime(0) == 2);
	static_assert(next_prime(1) == 2);
	static_assert(next_prime(2) == 3);
	static_assert(next_prime(3) == 5);
	static_assert(next_prime(4) == 5);
	static_assert(next_prime(5) == 7);
	static_assert(next_prime(6) == 7);
	static_assert(next_prime(2147483646) == 2147483647);
	static_assert(next_prime(2147483647) == 2147483659);
	static_assert(next_prime(4294960002) == 4294960003);
	static_assert(next_prime(4294960003) == 0);
	static_assert(next_prime(4294967295) == 0);

	// constexpr and deterministic random number generator.
	template<class T>
	constexpr T det_rand_int(T seed, T max)
	{
		static_assert(std::is_integral_v<T>, "T must be an integral type");
		if (max == 0)
		{
			return 0;
		}
		return (seed * 1664525 + 1013904223) % max;
	}
	static_assert(det_rand_int<uint32_t>(0, 1) == 0);
	static_assert(det_rand_int<uint64_t>(0, 10000) == 4223);
	static_assert(det_rand_int<uint32_t>(1, 10000) == 8748);

	// Uses the device to generate a non-deterministic random number
	class rand
	{
	public:
		rand() : m_engine(m_device()) {}

		template<class T>
		T rand_int(T min, T max)
		{
			static_assert(std::is_integral_v<T>, "T must be an integral type");
			if (min > max)
			{
				std::swap(min, max);
			}
			std::uniform_int_distribution<T> dist(min, max);
			return dist(m_engine);
		}

		template<class T>
		T rand_float(T min, T max)
		{
			static_assert(std::is_floating_point_v<T>, "T must be a floating-point type");
			if (min > max)
			{
				std::swap(min, max);
			}
			std::uniform_real_distribution<T> dist(min, max);
			return dist(m_engine);
		}

	private:
		std::random_device m_device;
		std::mt19937 m_engine;
	};

	template<class T>
	class c_vec2
	{
	public:
		c_vec2() : x(0), y(0) {}
		c_vec2(T x, T y) : x(x), y(y) {}

		c_vec2<T> operator+(const c_vec2<T>& other) const
		{
			return c_vec2<T>(x + other.x, y + other.y);
		}

		c_vec2<T> operator-(const c_vec2<T>& other) const
		{
			return c_vec2<T>(x - other.x, y - other.y);
		}

		c_vec2<T> operator*(const c_vec2<T>& other) const
		{
			return c_vec2<T>(x * other.x, y * other.y);
		}

		c_vec2<T> operator/(const c_vec2<T>& other) const
		{
			return c_vec2<T>(x / other.x, y / other.y);
		}

		c_vec2<T> operator*(T scalar) const
		{
			return c_vec2<T>(x * scalar, y * scalar);
		}

		c_vec2<T> operator/(T scalar) const
		{
			return c_vec2<T>(x / scalar, y / scalar);
		}

		c_vec2<T>& operator+=(const c_vec2<T>& other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		c_vec2<T>& operator-=(const c_vec2<T>& other)
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}

		c_vec2<T>& operator*=(const c_vec2<T>& other)
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}

		c_vec2<T>& operator/=(const c_vec2<T>& other)
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}

		c_vec2<T>& operator*=(T scalar)
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

		c_vec2<T>& operator/=(T scalar)
		{
			x /= scalar;
			y /= scalar;
			return *this;
		}

	private:
		T x;
		T y;
	};
}