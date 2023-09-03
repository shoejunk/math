#pragma once

#include <cstdint>

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
}
