export module stk.math;
export import :true_real;

import std.core;
import "gcem.hpp";

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
	constexpr T det_rand_int(T seed, T max = std::numeric_limits<T>::max())
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
	class c_rand
	{
	public:
		c_rand() : m_engine(m_device()) {}

		template<class T>
		T rand_int(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max())
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
		constexpr c_vec2() : m_x(0), m_y(0) {}
		constexpr c_vec2(T x, T y) : m_x(x), m_y(y) {}

		template<typename U>
		constexpr c_vec2(const c_vec2<U>& other) : m_x(static_cast<T>(other.x())), m_y(static_cast<T>(other.y())) {}

		constexpr T x() const { return m_x; }
		constexpr T y() const { return m_y; }
		constexpr T& x() { return m_x; }
		constexpr T& y() { return m_y; }
		void x(T x) { m_x = x; }
		void y(T y) { m_y = y; }

		c_vec2<T> operator+(const c_vec2<T>& other) const
		{
			return c_vec2<T>(m_x + other.m_x, m_y + other.m_y);
		}

		c_vec2<T> operator-(const c_vec2<T>& other) const
		{
			return c_vec2<T>(m_x - other.m_x, m_y - other.m_y);
		}

		c_vec2<T> operator-() const
		{
			return c_vec2<T>(-m_x, -m_y);
		}

		c_vec2<T> operator*(const c_vec2<T>& other) const
		{
			return c_vec2<T>(m_x * other.m_x, m_y * other.m_y);
		}

		c_vec2<T> operator/(const c_vec2<T>& other) const
		{
			return c_vec2<T>(m_x / other.m_x, m_y / other.m_y);
		}

		c_vec2<T> operator*(T scalar) const
		{
			return c_vec2<T>(m_x * scalar, m_y * scalar);
		}

		c_vec2<T> operator/(T scalar) const
		{
			return c_vec2<T>(m_x / scalar, m_y / scalar);
		}

		c_vec2<T>& operator+=(const c_vec2<T>& other)
		{
			m_x += other.m_x;
			m_y += other.m_y;
			return *this;
		}

		c_vec2<T>& operator-=(const c_vec2<T>& other)
		{
			m_x -= other.m_x;
			m_y -= other.m_y;
			return *this;
		}

		c_vec2<T>& operator*=(const c_vec2<T>& other)
		{
			m_x *= other.m_x;
			m_y *= other.m_y;
			return *this;
		}

		c_vec2<T>& operator/=(const c_vec2<T>& other)
		{
			m_x /= other.m_x;
			m_y /= other.m_y;
			return *this;
		}

		c_vec2<T>& operator*=(T scalar)
		{
			m_x *= scalar;
			m_y *= scalar;
			return *this;
		}

		c_vec2<T>& operator/=(T scalar)
		{
			m_x /= scalar;
			m_y /= scalar;
			return *this;
		}

		constexpr bool operator==(const c_vec2<T>& rhs) const
		{
			return m_x == rhs.m_x && m_y == rhs.m_y;
		}

	private:
		T m_x;
		T m_y;
	};

	using c_vec2i = c_vec2<int32_t>;
	using c_vec2f = c_vec2<float>;

	class c_rot
	{
	public:
		static constexpr int16_t deg_0 = 0;
		static constexpr int16_t deg_45 = 8192;
		static constexpr int16_t deg_90 = 16384;
		static constexpr int32_t deg_180 = 32768;

		static constexpr c_rot from_rad(long double angle_rad)
		{
			return (int16_t)(angle_rad * (long double)deg_180 / std::numbers::pi_v<long double>);
		}

		static constexpr c_rot from_deg(long double angle_deg)
		{
			return (int16_t)(angle_deg * (long double)deg_45 / 45.f);
		}

	public:
		constexpr c_rot()
			: m_angle(0)
		{
		}

		constexpr c_rot(int16_t angle)
			: m_angle(angle)
		{
		}

		constexpr int16_t angle() const
		{
			return m_angle;
		}

		constexpr int16_t& angle()
		{
			return m_angle;
		}

		constexpr long double angle_rad() const
		{
			return (long double)m_angle * std::numbers::pi_v<long double> / (long double)deg_180;
		}

		constexpr long double angle_deg() const
		{
			return (long double)m_angle / (long double)deg_45 * 45.f;
		}

		void set_rad(float angle_rad)
		{
			m_angle = (int16_t)(angle_rad * (float)deg_180 / std::numbers::pi_v<float>);
		}

		void set_deg(float angle_deg)
		{
			m_angle = (int16_t)(angle_deg * (float)deg_45 / 45.f);
		}

		constexpr bool operator==(c_rot const& other) const
		{
			return m_angle == other.m_angle;
		}

		constexpr bool operator!=(c_rot const& other) const
		{
			return m_angle != other.m_angle;
		}

		constexpr c_rot operator+(c_rot const& other) const
		{
			return c_rot(m_angle + other.m_angle);
		}

		constexpr c_rot operator-(c_rot const& other) const
		{
			return c_rot(m_angle - other.m_angle);
		}

		constexpr c_rot operator-() const
		{
			return c_rot(-m_angle);
		}

		c_rot& operator+=(c_rot const& other)
		{
			m_angle += other.m_angle;
			return *this;
		}

		c_rot& operator-=(c_rot const& other)
		{
			m_angle -= other.m_angle;
			return *this;
		}

		[[nodiscard]] constexpr c_vec2f rot(c_vec2f const vec) const
		{
			float x = vec.x();
			float y = vec.y();
			long double rad = angle_rad();
			auto cos = gcem::cos(rad);
			auto sin = gcem::sin(rad);
			return { static_cast<float>(cos * x - y * sin), static_cast<float>((sin * x + y * cos)) };
		}

 		[[nodiscard]] constexpr c_vec2i rot(c_vec2i const vec) const
		{
			int32_t x = vec.x();
			int32_t y = vec.y();
			long double rad = angle_rad();
			auto cos = gcem::cos(rad);
			auto sin = gcem::sin(rad);
			return { static_cast<int32_t>(cos * x - sin * y), static_cast<int32_t>(sin * x + cos * y) };
		}

	private:
		int16_t m_angle;
	};

	bool overlaps(c_vec2i a_center, c_vec2i a_extents, c_vec2i b_center, c_vec2i b_extents)
	{
		return std::abs(a_center.x() - b_center.x()) < a_extents.x() / 2 + b_extents.x() / 2
			&& std::abs(a_center.y() - b_center.y()) < a_extents.y() / 2 + b_extents.y() / 2;
	}

	constexpr c_rot operator "" _deg(long double degrees)
	{
		return c_rot::from_deg(degrees);
	}

	constexpr c_rot operator "" _deg(unsigned long long degrees)
	{
		return c_rot::from_deg(degrees);
	}

	constexpr c_rot operator "" _rad(long double radians)
	{
		return c_rot::from_rad(radians);
	}

	constexpr c_rot operator "" _rad(unsigned long long radians)
	{
		return c_rot::from_rad(radians);
	}
}
