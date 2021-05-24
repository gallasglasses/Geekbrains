// HW6.cpp

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>

std::string nameFile();

void fillArray(int* arr, size_t size);
void printArray(int* arr, size_t size);
void deleteArray(int* arr);
void delete2DimArray(int** arr, size_t size1, size_t size2);
void fillRandArray(int** arr, size_t size1, size_t size2);
void print2DimArray(int** arr, size_t size1, size_t size2);
void newFile(std::string name);
void mergingFiles();
void findWord();

int main()
{
    
    std::cout << "This is 1 exercise\n";
    {
        int* ptrArr;
        size_t sizeMassiv;
        std::cout << "Enter the size of massiv: ";
        std::cin >> sizeMassiv;
        ptrArr = new int[sizeMassiv]();
        fillArray(ptrArr, sizeMassiv);
        printArray(ptrArr, sizeMassiv);
        deleteArray(ptrArr);
        std::cout << "\n_____________________________________________\n\n";
    }

    std::cout << "This is 2 exercise\n";
    {
        int** ptrArr2;
        const size_t n = 4;
        const size_t m = 4;
        ptrArr2 = new int * [m];
        for (size_t i = 0; i < m; i++)
        {
            ptrArr2[i] = new int[n];
        }
        fillRandArray(ptrArr2, m, n);
        print2DimArray(ptrArr2, m, n);
        delete2DimArray(ptrArr2, m, n);
        std::cout << "\n_____________________________________________\n\n";
    }

    std::cout << "This is 3 exercise\n";
    {
        std::string nameForFile;
        nameForFile = nameFile();
        newFile(nameForFile);

        nameForFile = nameFile();
        newFile(nameForFile);
        std::cout << "\n_____________________________________________\n\n";
    }

    std::cout << "This is 4 exercise\n";
    {
        mergingFiles();
        std::cout << "\n_____________________________________________\n\n";
    }

    std::cout << "This is 5 exercise\n";
    {
        findWord();
        std::cout << "\n_____________________________________________\n\n";
    }
    

    return 0;
}

void fillArray(int* arr, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = static_cast<int>(pow(2, i));
    }
}

void printArray(int* arr, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }
}

void deleteArray(int* arr)
{
    delete[] arr;
    arr = nullptr;
}

void delete2DimArray(int** arr, size_t size1, size_t size2)
{
    for (size_t i = 0; i < size2; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
    arr = nullptr;
}

void fillRandArray(int** arr, size_t size1, size_t size2)
{
    for (size_t i = 0; i < size1; i++)
    {
        for (size_t j = 0; j < size2; j++)
        {
            arr[i][j] = rand() % 100 + 1;
        }
    }
}

void print2DimArray(int** arr, size_t size1, size_t size2)
{
    for (size_t i = 0; i < size1; i++)
    {
        for (size_t j = 0; j < size2; j++)
        {
            std::cout.width(5);
            std::cout << std::right << arr[i][j] << " ";
        }
        std::cout << "\n";
    }
}

std::string nameFile()
{
    std::string fName;
    std::cout << "\nPlease give the filename(without \".txt\"): ";
    std::cin >> fName;
    std::cout << "The filename: " << fName << "\n";
    fName += ".txt";
    return fName;
}

void newFile(std::string name)
{
    
    const char text[25] = "some text write here";
    std::ofstream fout(name);
    if (fout.is_open())
    {
        for (size_t i = 0; i < 15; i++)
        {
            fout << text << " " << i << " ";
        }
        fout.close();
    }

    std::string textFile;
    const size_t size = 255;
    char buf[size];
    std::ifstream fin(name);
    
    if (fin.is_open())
    {
        
        for (size_t i = 0; i < size; i++)
        {
            fin >> buf[i];
            std::cout << buf[i];
        }
        fin.close();
    }
    else
    {
        std::cout << "Error. Can not open file.";
    }

    std::cin.get();
}

void mergingFiles()
{
    std::string str;

    std::string fName1;
    std::cout << "\nFirst file\n";
    std::cout << "\nPlease give the filename(without \".txt\"): ";
    std::cin >> fName1;
    fName1 += ".txt";

    std::string fName2;
    std::cout << "\nSecond file\n";
    std::cout << "\nPlease give the filename(without \".txt\"): ";
    std::cin >> fName2;
    fName2 += ".txt";


    std::ifstream fin1(fName1);
    std::ifstream fin2(fName2);
    
    int firstFile = fin1.is_open(),
        secondFile = fin2.is_open();
    if ( firstFile && secondFile ) 
    {
        std::string fName3;
        std::cout << "\nThird file\n";
        fName3 = nameFile();
        std::ofstream fout(fName3);
        fout.is_open();

        do 
        {
            std::getline(fin1, str);
            fout << str << std::endl;
            //std::getline(fin2, str);
            //fout << str << std::endl;
        } while (fin1 && fin2);

        fin1.close();
        fin2.close();
        fout.close();
    }
    else 
    {
        if (!firstFile)
            std::cout << "Error! First file " << fName1 << " not found!\n";
        if (!secondFile)
            std::cout << "Error! Second file " << fName2 << " not found!\n";
    }

    std::cin.get();
}

void findWord()
{
    std::string fileName,
                line,
                word;
    //bool isContinue = true;
    
    while (1)
    {
        size_t countWords = 0,
               foundWords = 0,
               lineNumber = 0;
        std::cout << "Please give the filename with expansion (ex: \"text.txt\" or \"HW6.cpp\") : ";
        std::cin >> fileName;
        
        std::cout << "Write the word you're searching for.";
        std::cin >> word;
        std::ifstream File(fileName.c_str());
        if (File)
        {
            while (std::getline(File, line))
            {
                lineNumber++;
                size_t coutPos = 0;
                for (size_t i = line.find(word); i < line.length(); i = i + word.length())
                {
                        
                    coutPos = line.find(word, i);
                    if ((coutPos != std::string::npos))
                    {
                        std::cout << word << " is at " << lineNumber << ":" << coutPos << "\n";
                        countWords++;
                    }
                    else break;
                    if (coutPos > i)
                    {
                        i = coutPos;
                    }
                }
            }
            File.close();
            if (countWords > 0)
            {
                    std::cout << "The word \"" << word << "\" has been found " << countWords << " times.\n";
            }
            else
            {
                    std::cout << "The word has not been found.\n";
            }
        }
        else
        {
            std::cout << "Error! File not found!\n";
        }
    }
}
    
