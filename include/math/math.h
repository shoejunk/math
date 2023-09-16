#pragma once

#include <bitset>
#include <cstdint>
#include <random>

namespace NStk::NMath
{
	// Returns the next prime number after uX. Returns 0 if there is no prime number after uX that fits in a uint32_t.
	constexpr uint32_t NextPrime(uint32_t uX)
	{
		if (uX < 2)
			return 2;

		if (uX == 2)
			return 3;

		if (uX >= 4294960003) // Largest prime number that fits in a uint32_t.
			return 0;

		uint32_t uPrime = (uX + 1) | 1;
		while (true)
		{
			bool bIsPrime = true;
			for (uint32_t uDivisor = 3; uDivisor * uDivisor <= uPrime; uDivisor += 2)
			{
				if (uPrime % uDivisor == 0)
				{
					bIsPrime = false;
					break;
				}
			}

			if (bIsPrime)
				return uPrime;

			uPrime += 2;
		}
	}
	static_assert(NextPrime(0) == 2);
	static_assert(NextPrime(1) == 2);
	static_assert(NextPrime(2) == 3);
	static_assert(NextPrime(3) == 5);
	static_assert(NextPrime(4) == 5);
	static_assert(NextPrime(5) == 7);
	static_assert(NextPrime(6) == 7);
	static_assert(NextPrime(2147483646) == 2147483647);
	static_assert(NextPrime(2147483647) == 2147483659);
	static_assert(NextPrime(4294960002) == 4294960003);
	static_assert(NextPrime(4294960003) == 0);
	static_assert(NextPrime(4294967295) == 0);

	constexpr uint32_t Random(uint32_t seed, uint32_t max)
	{
		if (max == 0)
		{
			return 0;
		}
		return (seed * 1664525 + 1013904223) % max;
	}
	static_assert(Random(0, 1) == 0);
	static_assert(Random(0, 10000) == 4223);
	static_assert(Random(1, 10000) == 8748);

	class CRandom
	{
	public:
		CRandom() : m_oEngine(m_oDevice()) {}
		template<class T>
		T RandomInt(T iMin, T iMax)
		{
			if (iMin > iMax)
			{
				std::swap(iMin, iMax);
			}
			std::uniform_int_distribution<T> oDist(iMin, iMax);
			return oDist(m_oEngine);
		}
		template<class T>
		T RandomReal(T fMin, T fMax)
		{
			if (fMin > fMax)
			{
				std::swap(fMin, fMax);
			}
			std::uniform_real_distribution<T> oDist(fMin, fMax);
			return oDist(m_oEngine);
		}

	private:
		std::random_device m_oDevice;
		std::mt19937 m_oEngine;
	};

	template<size_t uBits>
	constexpr std::bitset<uBits + 1> AddBits(std::bitset<uBits> const& kBitsA, std::bitset<uBits> const& kBitsB)
	{
		std::bitset<uBits + 1> bitsRes;
		uint32_t uCarry = 0;
		for (size_t i = 0; i < uBits; ++i)
		{
			uint32_t uCarryNext = 0;
			if ((kBitsA[i] & kBitsB[i]) || (uCarry & (kBitsA[i] | kBitsB[i])))
			{
				uCarryNext = 1;
			}

			bitsRes[i] = (kBitsA[i] ^ kBitsB[i]) ^ uCarry;
			uCarry = uCarryNext;
		}

		if (uCarry)
		{
			bitsRes.set(uBits);
		}

		return bitsRes;
	}
}