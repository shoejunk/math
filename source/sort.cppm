export module stk.math:sort;

import std.core;

export namespace NStk::NMath
{
	constexpr void InsertionSortDecreasing(int32_t* aiArr, int32_t iSize)
	{
		for (int32_t i = 1; i < iSize; ++i)
		{
			int32_t iKey = aiArr[i];
			int32_t j = i - 1;

			while (j >= 0 && aiArr[j] < iKey)
			{
				aiArr[j + 1] = aiArr[j];
				--j;
			}

			aiArr[j + 1] = iKey;
		}
	}

	constexpr bool Match(int32_t* aiA, int32_t iSizeA, int32_t* aiB, int32_t iSizeB)
	{
		if (iSizeA != iSizeB)
		{
			return false;
		}

		for (int32_t i = 0; i < iSizeA; ++i)
		{
			if (aiA[i] != aiB[i])
			{
				return false;
			}
		}

		return true;
	}

	constexpr int32_t Search(int32_t const* aiArr, int32_t iSize, int32_t iValue)
	{
		for (size_t i = 0; i < iSize; ++i)
		{
			if (aiArr[i] == iValue)
			{
				return i;
			}
		}
		return -1;
	}

	constexpr int32_t aiTest[] = { 5, 4, 4, 8, 2, -1, 0, 3, 10, 9, 7, 6, 1, 2, 3, 4, 5, 6, 7, 8 };
	constexpr auto iSize = sizeof(aiTest) / sizeof(int32_t);
	static_assert(NMath::Search(aiTest, iSize, 10) == 8);
	static_assert(NMath::Search(aiTest, iSize, -1) == 5);
	static_assert(NMath::Search(aiTest, iSize, 5) == 0);
	static_assert(NMath::Search(aiTest, iSize, -2) == -1);
}