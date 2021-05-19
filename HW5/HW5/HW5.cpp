// HW5.cpp 

#include <iostream>
#include <cmath>

void printArray(double* array, size_t size);
void printArray(int* array, size_t size);
void inverseBinArray(int* array, size_t size);
void fillArray(int* array, size_t size);
void shiftArray(int x, int* array, size_t size);
int shiftDigit(int a, int b);
bool HW5(int* array, size_t size);

int main()
{
    std::cout << "This is 1 exercise\n"
        "Write a function that prints an array of double numbers to the screen.\n\n";

    {
        const size_t SIZE = 10;
        double array[SIZE] = { 1.2,1.9,2.3,4.5,6.2,1.7,2.9,0.1,3.3,9.9 };
        printArray(array, SIZE);
        std::cout << "\n_____________________________________________\n\n";
    }

    std::cout << "This is 2 exercise\n"
        "Specify an integer array of elements 0 and 1.\n"
        "Write a function that replaces 0 by 1, 1 by 0 in the received array.\n\n";

    {
        const size_t SIZE = 10;
        int array[SIZE] = { 1, 1, 0, 0, 1, 0, 1, 1, 0, 0 };

        std::cout.width(25);
        std::cout << std::right << "Array before changes: ";
        printArray(array, SIZE);
        std::cout << "\n";
        std::cout.width(25);
        std::cout << std::right << "Array after changes: ";
        inverseBinArray(array, SIZE);
        printArray(array, SIZE);
        std::cout << "\n_____________________________________________\n\n";
    }

    std::cout << "This is 3 exercise\n"
        "Set an empty integer array of size 8.\n"
        "Write a function that will use a loop to fill it with values 1 4 7 10 13 16 19 22.\n\n";

    {
        const size_t SIZE = 8;
        int array[SIZE] = { };

        fillArray(array, SIZE);
        printArray(array, SIZE);
        std::cout << "\n_____________________________________________\n\n";
    }

    std::cout << "This is 4 exercise\n"
        "Write a function that accepts a one-dimensional array \n"
        "and a number n (can be positive or negative) as input, \n"
        "and the method must cyclically shift all elements of \n"
        "the array by n positions.\n\n";

    {
        const size_t SIZE = 10;
        int array[SIZE] = {0,1,2,3,4,5,6,7,8,9};
        int n;
        std::cout << "Enter the number to shift " 
            "(positive number - shift to the right, negative number - shift to the left) ";
        std::cin >> n;
        
        shiftArray(n, array, SIZE);
        printArray(array, SIZE);
        std::cout << "\n_____________________________________________\n\n";
    }

    std::cout << "This is 5 exercise\n"
        "Write a function that is passed a non-empty one-dimensional \n"
        "integer array, the function must return true if there is \n"
        "a place in the array where the sum of the left and right \n"
        "sides of the array are equal.\n\n";

    {
        const size_t SIZE = 5;
        int array[SIZE] = { 1,2,3,4,10 };
        
        std::cout << "Checking the balance of this array: ";
        printArray(array, SIZE);
        std::cout << "\n\n";

        if (HW5(array, SIZE))
            std::cout << " - true\n";
        else std::cout << " - false\n";

        std::cout << "\n_____________________________________________\n\n";

    }

    return 0;
}

void printArray(double * array, size_t size)
{
    for (size_t i = 0; i < size ; i++)
    {
        std::cout << array[i] << ' ';
    }
    
}

void printArray(int* array, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        std::cout << array[i] << ' ';
    }

}

void inverseBinArray(int* array, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        array[i] = (array[i] == 1) ? 0 : 1;
    }
}

void fillArray(int* array, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        array[i] = 1 + i * 3;
    }
}

void shiftArray(int x, int* array, size_t size)
{
    int shift,
        remember = 0,
        currentIndex = 0,
        shiftedIndex;
    if (x == 0)
    {
        return;
    }
    if (abs(x) > size)
        shift = x % size;
    else shift = x;
    //std::cout << "shift: " << shift << "\n";
    for (size_t i = size-1; i >= (size - shiftDigit(abs(shift), size)); i--)
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

//Find G.C.D using recursion
int shiftDigit(int a, int b)
{
    if (b == 0)
        return a;
    else
        return shiftDigit(b, a % b);
}

bool HW5(int* array, size_t size)
{
    int sum = 0;
    bool isBalanceArray = false;
    for (size_t i = 0; i< size; i++)
    {
        sum += array[i];
    }
    int checkLeftPart = 0,
        leftBorder = 0;
    for (size_t i = 0; i < size; i++)
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
