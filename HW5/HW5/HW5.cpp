// HW5.cpp 

#include <iostream>
#include <cmath>

void arrayHW1(double* array, int size);
int HW2(int* array, int i);
void HW3(int* array, int size);
void HW4(int x, int* array, int size);
int shiftDigit(int a, int b);
bool HW5(int* array, int size);

int main()
{
    std::cout << "This is 1 exercise\n\n";
    {
        const int SIZE = 10;
        double array[SIZE] = { 1.2,1.9,2.3,4.5,6.2,1.7,2.9,0.1,3.3,9.9 };
        arrayHW1(array, SIZE);
    }

    std::cout << "This is 2 exercise\n\n";
    {
        const int SIZE = 10;
        int array[SIZE] = { 1, 1, 0, 0, 1, 0, 1, 1, 0, 0 };

        std::cout.width(25);
        std::cout << std::right << "Array before changes: ";
        for (int i = 0; i < SIZE; i++)
        {
            std::cout << array[i] << ' ';
        }
        std::cout << "\n";
        std::cout.width(25);
        std::cout << std::right << "Array after changes: ";
        for (int i = 0; i < SIZE; i++)
        {
            std::cout << HW2(array, i) << ' ';
        }
        std::cout << "\n_____________________________________________\n\n";
    }

    std::cout << "This is 3 exercise\n\n";

    {
        const int SIZE = 8;
        int array[SIZE] = { };

        HW3(array, SIZE);

        for (int i : array)
        {
            std::cout << i << ' ';
        }
        std::cout << "\n_____________________________________________\n\n";
    }

    std::cout << "This is 4 exercise\n\n";

    {
        const int SIZE = 10;
        int array[SIZE] = {0,1,2,3,4,5,6,7,8,9};
        int n;
        std::cout << "Enter the number to shift " 
            "(positive number - shift to the right, negative number - shift to the left) ";
        std::cin >> n;
        
        HW4(n, array, SIZE);
        for (int i : array)
        {
            std::cout << i << ' ';
        }
        std::cout << "\n_____________________________________________\n\n";
    }

    std::cout << "This is 5 exercise\n\n";

    {
        const int SIZE = 5;
        int array[SIZE] = { 1,2,3,4,10 };
        
        
        for (int i : array)
        {
            std::cout << i << ' ';
        }
        std::cout << "\n";

        if (HW5(array, SIZE))
            std::cout << " - true\n";
        else std::cout << " - false\n";

        std::cout << "\n_____________________________________________\n\n";

    }

    return 0;
}

void arrayHW1(double * array, int size)
{
    for (int i = 0; i < size ; i++)
    {
        std::cout << array[i] << ' ';
    }
    std::cout << "\n_____________________________________________\n\n";
}

int HW2(int* array, int i)
{
    return ((array[i] == 1) ? array[i] = 0 : array[i] = 1);
}

void HW3(int* array, int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = 1 + i * 3;
    }
}

void HW4(int x, int* array, int size)
{
    int shift,
        remember = 0,
        currentIndex = 0,
        shiftedIndex;
      
    if (abs(x) > size)
        shift = x % size;
    else shift = x;
    //std::cout << "shift: " << shift << "\n";
    for (int i = size-1; i >= (size - shiftDigit(abs(shift), size)); i--)
    {
        remember = array[i];
        currentIndex = i;
        //std::cout << "currentIndex " << currentIndex << "\n";

        if (shift > 0)
        {
            while (true)
            {
                shiftedIndex = currentIndex - shift;
                if (shiftedIndex < 0)
                    shiftedIndex = size + shiftedIndex;
                if (shiftedIndex == i)
                    break;
                array[currentIndex] = array[shiftedIndex];
                //std::cout << "currentIndex " << currentIndex << " = " << array[currentIndex] << "\n";
                currentIndex = shiftedIndex;
                
            }
        }
        else 
        {
            while (true)
            {
                shiftedIndex = currentIndex - shift;
                if (shiftedIndex >= size)
                    shiftedIndex = shiftedIndex - size;
                if (shiftedIndex == i)
                    break;
                array[currentIndex] = array[shiftedIndex];
                //std::cout << "currentIndex " << currentIndex << " = " << array[currentIndex] << "\n";
                currentIndex = shiftedIndex;
            }
        }
        array[currentIndex] = remember;
        //std::cout << "currentIndex " << currentIndex << " = " << array[currentIndex] << "\n";
    }
    
}

int shiftDigit(int a, int b)
{
    if (b == 0)
        return a;
    else
        return shiftDigit(b, a % b);
}

bool HW5(int* array, int size)
{
    int sum = 0;
    bool isBalanceArray = false;
    for (int i = 0; i< size; i++)
    {
        sum += array[i];
    }
    int checkLeftPart = 0,
        leftBorder = 0;
    for (int i = 0; i < size; i++)
    {
        checkLeftPart += array[i];
        if (checkLeftPart == sum - checkLeftPart)
        {
            isBalanceArray = true;
            leftBorder = i;
            std::cout << "the sum of left part: " << checkLeftPart << " = the sum of right part: " << sum - checkLeftPart << "\n";
            std::cout << " { ";
            for (i = 0; i < size; i++)
            {
                std::cout << array[i] << " ";
                if (i == leftBorder)
                    std::cout << "|| ";

            }
            std::cout << " } ";
        }       
    }
    return isBalanceArray;
    
}
