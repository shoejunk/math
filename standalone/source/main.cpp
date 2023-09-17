#include <assert.h>

import stk.math;
import std.core;

using namespace NStk;

int main(int argc, char* argv[])
{
	if (argc > 2)
	{
		if (strcmp(argv[1], "NextPrime") == 0)
		{
			int iN = atoi(argv[2]);
			auto uPrime = NStk::NMath::NextPrime((uint32_t)iN);
			if (uPrime == 0)
			{
				std::cout << "Failure. The next prime is larger than would fit in a uint32_t so I cannot compute it." << std::endl;
			}
			else
			{
				std::cout << "The next prime number that comes after " << iN << " is " << uPrime << std::endl;
			}
		}
		else if (argc > 3 && (strcmp(argv[1], "Random") == 0))
		{
			auto iSeed = atoi(argv[2]);
			auto iMax = atoi(argv[3]);
			auto uR = NStk::NMath::Random(static_cast<uint32_t>(iSeed), static_cast<uint32_t>(iMax));
			std::cout << uR << std::endl;
		}
		else if (argc > 3 && (strcmp(argv[1], "RandomInt") == 0))
		{
			auto iMin = atoi(argv[2]);
			auto iMax = atoi(argv[3]);
			NMath::CRandom oRandom;
			auto iR = oRandom.RandomInt(iMin, iMax);
			std::cout << iR << std::endl;
		}
		else if (argc > 3 && (strcmp(argv[1], "RandomReal") == 0))
		{
			auto fMin = atof(argv[2]);
			auto fMax = atof(argv[3]);
			NMath::CRandom oRandom;
			auto fR = oRandom.RandomReal(fMin, fMax);
			std::cout << fR << std::endl;
		}
	}
	else
	{
		std::cout << "Enter \"NextPrime <X>\" to find the next prime that comes after X." << std::endl;
		std::cout << "Enter \"Random <Seed> <Max>\" to find a random number with the given Seed in the range [0, Max)." << std::endl;
		std::cout << "Enter \"RandomInt <Min> <Max>\" to find a random int in the range [Min, Max]." << std::endl;
		std::cout << "Enter \"RandomReal <Min> <Max>\" to find a random number in the range from Min to Max." << std::endl;
	}

	int32_t aiTest[] = { 5, 4, 4, 8, 2, -1, 0, 3, 10, 9, 7, 6, 1, 2, 3, 4, 5, 6, 7, 8 };
	auto iSize = sizeof(aiTest) / sizeof(int32_t);
	int32_t aiTestSorted[] = { 10, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 4, 4, 3, 3, 2, 2, 1, 0, -1 };
	auto iSizeSorted = sizeof(aiTestSorted) / sizeof(int32_t);

	NMath::InsertionSortDecreasing(aiTest, iSize);

	assert(NMath::Match(aiTestSorted, iSizeSorted, aiTest, iSize));

	assert(NMath::AddBits(std::bitset<1>{ 0 }, std::bitset<1>{ 0 }) == std::bitset<2>{ 0 });
	assert(NMath::AddBits(std::bitset<1>{ 0 }, std::bitset<1>{ 1 }) == std::bitset<2>{ 1 });
	assert(NMath::AddBits(std::bitset<1>{ 1 }, std::bitset<1>{ 0 }) == std::bitset<2>{ 1 });
	auto bitsRes = NMath::AddBits(std::bitset<2>("11"), std::bitset<2>("11"));
	assert(bitsRes == std::bitset<3>("110"));

	return 0;
}
