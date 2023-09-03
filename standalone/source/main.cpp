#include <iostream>
#include <cstdlib>

#include <math/math.h>

using namespace NStk;

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		int n = atoi(argv[1]);
		auto prime = NStk::NMath::NextPrime((uint32_t)n);
		if (prime == 0)
		{
			std::cout << "Failure. The next prime is larger than would fit in a uint32_t so I cannot compute it." << std::endl;
		}
		else
		{
			std::cout << "The next prime number that comes after " << n << " is " << prime << std::endl;
		}
	}
	else
	{
		std::cout << "Enter a number to find the next highest prime." << std::endl;
	}
	return 0;
}
