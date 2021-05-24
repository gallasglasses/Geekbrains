#include <iostream>
#include "mylib.h"

namespace FindPositiveNegativeNumber
{
	float fillArray(size_t size)
	{
		float* ptrArr;
		ptrArr = new float[size]();

		for (size_t i = 0; i < size; i++)
		{
			return ptrArr[i] = static_cast<float>(rand() % 50 + 0) / static_cast<float> (rand() % 10 + 1) - static_cast<float>(rand() % 20 + 0);
		}
		delete[] ptrArr;
		ptrArr = nullptr;
	}

	void printArray(float* arr, size_t size)
	{
		for (size_t i = 0; i < size; i++)
		{
			std::cout << arr[i] << " ";
		}
		std::cout << "\n";
	}

	void countPositiveNegative(float* arr, size_t size)
	{
		size_t countPositive = 0,
			countNegative = 0;
		for (size_t i = 0; i < size; i++)
		{
			if (arr[i] > 0)
			{
				countPositive++;
			}
			else if (arr[i] < 0)
			{
				countNegative++;
			}
			else continue;
		}
		if (countPositive > 0)
		{
			std::cout << "Positive numbers " << countPositive << "\n";
		}
		if (countNegative > 0)
		{
			std::cout << "Negative numbers " << countNegative << "\n";
		}
	}
}