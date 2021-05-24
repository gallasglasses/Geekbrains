// HW7.cpp 

#include <iostream>
#include <fstream>
#include <string>

#include "mylib.h" //This is 1 exercise

#define IS_INCLUDED(checkNumber, max) ((checkNumber>=0 && checkNumber < max) ? true : false) //This is 2 exercise
#define SIZE 15                                   //This is 3 exercise
#define SWAPPING(a, b) std::swap(a, b)            //This is 3 exercise

//This is 4 exercise
#pragma pack (push, 1)

struct Employee
{
    long id{};
    std::string first_name{};
    std::string last_name{};
    unsigned int age{};
    double salary{};
    unsigned long long phone{};
    unsigned short id_position{};
};

#pragma pack(pop) 

void printUnsortArray(int* arr, size_t size);
void fillUnsortArray(int* arr, size_t size);             //This is 3 exercise
void bubbleSortArray(int* arr, size_t size);       //This is 3 exercise

void fillStruct(Employee* s);                       //This is 4 exercise
void printStruct(Employee* s);                      //This is 4 exercise
void saveStructFile(Employee* s);                  //This is 4 exercise

int main()
{
    std::cout << "This is 1 exercise\n";
    std::cout << "Create a project from 2 cpp files and a header(main.cpp, mylib.cpp, mylib.h)\n"
                 "in the second module mylib declare 3 functions: to initialize an array(of float type),\n"
                 "print it to the screenand count the number of negativeand positive elements.Call these\n"
                 "3 functions from main to work with the array.\n";
    std::cout << "__________________________________________________________________________________________\n\n";

    {
        size_t sizeMassiv;
        std::cout << "Enter the size of massiv: ";
        std::cin >> sizeMassiv;
        float* array;
        array = new float[sizeMassiv]();
        for (size_t i = 0; i < sizeMassiv; i++)
        {
            array[i] = FindPositiveNegativeNumber::fillArray(sizeMassiv);
        }

        FindPositiveNegativeNumber::printArray(array, sizeMassiv);
        FindPositiveNegativeNumber::countPositiveNegative(array, sizeMassiv);
        delete[] array;
        array = nullptr;
        std::cout << "\n__________________________________________________________________________________________\n\n";
    }

    std::cout << "This is 2 exercise\n";
    std::cout << "Describe a macro (via the define directive) that checks whether the number passed to it\n"
        "(entered from the keyboard) is in the range from zero (inclusive) to the second argument\n"
        "passed to it (exclusively) and returns true or false, display \"true\" or \"false\".\n";
    std::cout << "__________________________________________________________________________________________\n\n";

    {
        size_t inputCheckNumber,
               inputMaxNumber;
        std::cout << "Enter the checked number: ";
        std::cin >> inputCheckNumber;
        std::cout << "Enter the maximum bounding number: ";
        std::cin >> inputMaxNumber;
        if (IS_INCLUDED (inputCheckNumber, inputMaxNumber))
            std::cout << "The number " << inputCheckNumber << " is in the specified interval ( 0 - " << inputMaxNumber << " ).\n";
        else std::cout << "The number " << inputCheckNumber << " is not included in the specified interval ( 0 - " << inputMaxNumber << " ).\n";
        std::cout << "__________________________________________________________________________________________\n\n";
    }

    std::cout << "This is 3 exercise\n";
    std::cout << "Specify an array of type int.Let its size be set through the #define \n"
        "preprocessor directive.Initialize it via keyboard input.Write your own sort\n"
        "function for it(eg Bubble).Implement the swapping of elements as SwapINT(a, b) macro.\n"
        "Call it from within the sort loop.\n";
    std::cout << "__________________________________________________________________________________________\n\n";
    
    {
        int* array;
        array = new int[SIZE]();
        fillUnsortArray(array, SIZE);
        printUnsortArray(array, SIZE);
        bubbleSortArray(array, SIZE);
        printUnsortArray(array, SIZE);
        std::cout << "__________________________________________________________________________________________\n\n";
    }

    std::cout << "This is 4 exercise\n";
    std::cout << "Declare an Employee structure with different fields. Make it\n"
        "byte-aligned using the pragma pack directive. Allocate dynamically a \n"
        "variable of this type. Initialize it. Print it to the screen and its \n"
        "size using sizeof. Save this structure to a text file.\n";
    std::cout << "__________________________________________________________________________________________\n\n";

    {
        Employee* pEmployee = new Employee;
       
        fillStruct(pEmployee);
        std::cout << "\n";
        std::cout << "Size of structure Employee: " << sizeof(Employee) << "\n";
        std::cout << "Size of type pEmployee: " << sizeof(pEmployee) << "\n";
        printStruct(pEmployee);
        saveStructFile(pEmployee);

        delete pEmployee;
        pEmployee = nullptr;
    }

}

void printUnsortArray(int* arr, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        std::cout.width(2);
        std::cout << std::right << arr[i] << " ";
    }
    std::cout << "\n";
}

void fillUnsortArray(int* arr, size_t size)
{
    std::cout << "Enter " << size << " elements of array: \n";
    for (size_t i = 0; i < size; i++)
    {
        std::cout << "Element " << i + 1 << " : ";
        std::cin >> arr[i];
    }
}

void bubbleSortArray(int* arr, size_t size)
{
    for (size_t j = 0; j < size - 1; j++)
    {
        size_t count = 0;
        for (size_t i = 0; i < size - 1 - j; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                SWAPPING(arr[i], arr[i + 1]);
            }
        }
    }
}

void fillStruct(Employee* s)
{
    std::cout << "Employee information\n";
    std::cout << "ID: ";
    std::cin >> s->id;
    std::cout << "First Name: ";
    std::cin >> s->first_name;
    std::cout << "Last Name: ";
    std::cin >> s->last_name;
    std::cout << "Age: ";
    std::cin >> s->age;
    std::cout << "Salary: ";
    std::cin >> s->salary;
    std::cout << "Phone: ";
    std::cin >> s->phone;
    std::cout << "ID position: ";
    std::cin >> s->id_position;
}

void printStruct(Employee* s)
{
    std::cout << "Employee information\n";
    std::cout << "ID: " << s->id << "\n";
    std::cout << "First Name: " << s->first_name << "\n";
    std::cout << "Last Name: " << s->last_name << "\n";
    std::cout << "Age: " << s->age << "\n";
    std::cout << "Salary: " << s->salary << "\n";
    std::cout << "Phone: " << s->phone << "\n";
    std::cout << "ID position: " << s->id_position << "\n";
    
}

void saveStructFile(Employee *s)
{
    std::string fileName;
    bool fileOpen;
    fileName = "EI_";
    fileName += s->first_name;
    fileName += "_";
    fileName += s->last_name;
    fileName += ".txt";
    std::ofstream fout(fileName);
    std::cout << "fileName: " << fileName << "\n";
    fileOpen = fout.is_open();
    
    if (fileOpen)
    {
        fout << "Employee information\n";
        fout << "ID: " << s->id << "\n";
        fout << "First Name: " << s->first_name << "\n";
        fout << "Last Name: " << s->last_name << "\n";
        fout << "Age: " << s->age << "\n";
        fout << "Salary: " << s->salary << "\n";
        fout << "Phone: " << s->phone << "\n";
        fout << "ID position: " << s->id_position << "\n";
        fout.close();
    }
    else
    {
        std::cout << "Error.";
    }
}
