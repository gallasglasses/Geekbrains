
#include <iostream>
#include <ctype.h>
#include <string>
#include <sstream> 

unsigned long numericValidation(void);
void hw1(void);
void hw2(void);
void hw3(void);
void hw4(void);
void hw5(void);

int main()
{

    std::cout << "This is 1 exercise\n\n";

    hw1();

    std::cout << "This is 2 exercise\n\n";

    hw2();

    std::cout << "This is 3 exercise\n\n";

    hw3();

    std::cout << "This is 4 exercise\n\n";

    hw4();

    std::cout << "This is 5 exercise\n\n";

    hw5();

    return 0;
}


void hw1(void)
{
    int number1, number2;
    std::cout << "Checking that the sum of two (entered from the keyboard) numbers ranges from 10 to 20 (inclusive).\n";
    std::cout << "Enter the first number:\n";
    std::cin >> number1;
    std::cout << "Enter the second number:\n";
    std::cin >> number2;
    int sum;
    sum = number1 + number2;
    if ((sum >= 10) && (sum <= 20))
        std::cout << "true\n\n";
    else std::cout << "false\n\n";

    std::cout << "\nProgram completed!\n\n";
}

void hw2(void)
{
    const int CONSTANT1 = 10;
    const int CONSTANT2 = 5;
    std::cout << "Program that prints the string 'true' to the screen if the two integer"
        "constants declared at the beginning of it are either both 10 by themselves, or their sum is 10.\n";
    if (((CONSTANT1 == 10) & (CONSTANT2 == 10)) | ((CONSTANT1 + CONSTANT2) == 10))
        std::cout << "true\n\n";
    else std::cout << "false\n\n";

    std::cout << "\nProgram completed!\n\n";
}

void hw3(void)
{
    std::cout << "Program that displays a list of all odd numbers from 1 to 50.\n";
    std::cout << "Odd numbers: ";
    for (int i = 1; i <= 50; i+=2)
        std::cout << i << " ";
    
    std::cout << "\nProgram completed!\n\n";
}

unsigned long numericValidation(void)
{
    std::string userInput = "";

    int numCount = 0;
    unsigned long userConvertedNum;

    bool isIntNumber = false;
    bool isFloatNumber = false;
    bool isNegativeNumber = false;
    bool isZeroFirst = false;
    bool isZeroNumber = false;
    bool isExit = false;

    do
    {
        //std::cout << "Enter the number: ";
        std::cin >> userInput;

        if (userInput[0] == '-')
        {
            isNegativeNumber = true;
            numCount = 0;
        }
        else if (userInput[0] == '0' && isdigit(userInput[1]))
        {
            isZeroFirst = true;
            numCount = 0;
        }
        else if (userInput[0] == 'q')
        {
            isExit = true;
            numCount = 0;
        }
        else
            for (int i = 0; i < userInput.size(); i++)
            {
                if (isdigit(userInput[i]))
                {
                    numCount++;
                    isIntNumber = true;
                }
                else
                {
                    isIntNumber = false;
                    numCount = 0;
                }
                if (userInput[i] == '.')
                {
                    isFloatNumber = true;
                    numCount = 0;
                }
            }
        if (userInput[0] == '0' && numCount == 1 && isIntNumber == true)
        {
            isZeroNumber = true;
            isIntNumber = false;
            numCount = 0;
        }

        if (numCount == userInput.size() && isZeroNumber == false)
        {
            std::stringstream ssInput(userInput);
            ssInput >> userConvertedNum;
        }
        else
        {
            if (isFloatNumber == true)
                std::cout << "It's float-point number!\nEnter the integer number: ";
            else if (isNegativeNumber == true)
                std::cout << "It's negative number!\nEnter the positive number: ";
            else if (isZeroFirst == true)
                std::cout << "There the first number is zero!\nEnter the number: ";
            else if (isZeroNumber == true)
                std::cout << "It's zero!\nEnter the number: ";
            else if (isExit == true)
                break;
            else std::cout << "It's not a number!\nEnter the number (only digits without letters, symbols): ";

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            numCount = 0;
            isIntNumber = false;
            isFloatNumber = false;
            isNegativeNumber = false;
            isZeroFirst = false;
            isZeroNumber = false;

        }

    } while (isIntNumber == false && isExit == false);

    if (isExit == true)
        userConvertedNum = 0;

    return userConvertedNum;

}

void hw4(void)
{
    unsigned long checkedNumber;
    unsigned long divider;
    bool isNumberPrime;
    std::cout << "Program that checks if a number is prime.\n";
    std::cout << "Enter the number ('q' to terminate):\n";

    checkedNumber = numericValidation();
    while (checkedNumber != 0)
    {
        for (divider = 2, isNumberPrime = true; divider * divider <= checkedNumber; divider++)
        {
            if (checkedNumber % divider == 0)
                isNumberPrime = false;
        }
        if (isNumberPrime)
            std::cout << checkedNumber << " is a prime number!\n";
        else
            std::cout << checkedNumber << " is not a prime number!\n";
        std::cout << "Enter the next number ('q' to terminate):\n";
        checkedNumber = numericValidation();
    }

    std::cout << "\nProgram completed!\n";
    std::cout << std::endl;
}

void hw5(void)
{
    unsigned short checkedYear;
    std::cout << "Program that determines if this is a leap year.\n";
    std::cout << "Enter the year ('q' to terminate):\n";

    checkedYear = static_cast <unsigned short> (numericValidation());
    while (checkedYear != 0)
    {
        if (((checkedYear % 100 != 0) && (checkedYear % 4 == 0)) || (checkedYear % 400 == 0))
            std::cout << checkedYear << " is a leap year!\n";
        else std::cout << checkedYear << " is not a leap year!\n";

        std::cout << "Enter the next year ('q' to terminate):\n";
        checkedYear = static_cast <unsigned short> (numericValidation());
    }
    std::cout << "\nProgram completed!\n";
    std::cout << std::endl;
}