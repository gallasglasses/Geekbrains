
#include <iostream>

//№ 4
extern const int A, B, C, D; // const_here.cpp

//№ 2
const int POINT = 21;

//№ 3
const int SIZE = 3;

int main()
{
    //№ 4 
    std::cout << "This is 4 exercise" << std::endl << std::endl;
    
    float value;
    value = A * (B + (static_cast<float>(C) / D));
    std::cout << "A * (B + (C / D)) = " << value << std::endl;
    std::cout << std::endl;

    //№ 2
    std::cout << "This is 2 exercise" << std::endl << std::endl;

    std::cout << "Enter the digit ('q' to terminate): ";
    int digit;
    while (std::cin >> digit)
    {
     int value = (digit <= POINT) ? (POINT - digit) : ((digit - POINT) << 1);
        std::cout << "The difference between numbers " << POINT << " and " << digit << " is " << value << std::endl;
        std::cout << "Enter the digit ('q' to terminate): ";
    }
    std::cout << std::endl;

    //№ 3
    std::cout << "This is 3 exercise" << std::endl << std::endl;
   
    int cube[SIZE][SIZE][SIZE] = {0};
    int *pCube = nullptr;

    pCube = &cube[1][1][1];
    *pCube = 1;

    std::cout << "cube[1][1][1] = " << cube[1][1][1] << std::endl;
    std::cout << "The memory address of this variable: " << pCube << std::endl << std::endl;
    
    std::cout << "And this is a cube:" << std::endl;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < SIZE; k++)
                std::cout << cube[i][j][k] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

