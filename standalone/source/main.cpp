#include <math/math.h>

#include <cstdlib>
#include <iostream>

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
	}
	return 0;
}
