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
void outputFile(std::string name);
void copyFile(std::ifstream& fin, std::ofstream& fout);
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
        outputFile(nameForFile);

        nameForFile = nameFile();
        newFile(nameForFile);
        outputFile(nameForFile);
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
    const size_t SIZE = 1024;
    char text[SIZE];
    std::ofstream fout(name);
    if (fout.is_open())
    {
        std::cin.get();
        std::cin.get(text, SIZE);
        fout << text;
        fout.close();
    }
    else
    {
        std::cout << "Error.";
    }
}

void outputFile(std::string name)
{
    const size_t SIZE = 1024;
    char buf[SIZE];
    std::ifstream fin(name);
    std::cout << "\nFile \" " << name << " \" :\n";
    if (fin.is_open())
    {

        while (!fin.eof())
        {
            fin.getline(buf, SIZE);
            std::cout << buf << std::endl;
        }
        fin.close();
    }
    else
    {
        std::cout << "Error. Can not open file.";
    }
}

void copyFile(std::ifstream& fin, std::ofstream& fout)
{
    const size_t SIZE = 1024;
    char buf[SIZE];

    while (!fin.eof())
    {
        fin.getline(buf, SIZE);
        fout << buf << std::endl;
    }
}

void mergingFiles()
{
    std::string fName1;
    std::cout << "\nFirst file\n";
    fName1 = nameFile();
    
    std::string fName2;
    std::cout << "\nSecond file\n";
    fName2 = nameFile();


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
        if (fout.is_open())
        {
            copyFile(fin1, fout);
            fin1.close();

            copyFile(fin2, fout);
            fin2.close();
        }
        outputFile(fName3);
    }
    else 
    {
        if (!firstFile)
            std::cout << "Error! First file " << fName1 << " not found!\n";
        if (!secondFile)
            std::cout << "Error! Second file " << fName2 << " not found!\n";
    }
}

void findWord()
{
    std::string fileName,
                line,
                word;
    bool isContinue = true;
    
    while (isContinue)
    {
        size_t countWords = 0,
               foundWords = 0,
               lineNumber = 0;
        std::cout << "Please give the filename with expansion (ex: \"text.txt\" or \"HW6.cpp\").\n";
        std::cout << "Enter for exit \"~\"\n";
        std::cin >> fileName;
        std::cout << "\n";
        std::cout << "Write the word you're searching for.\n";
        std::cout << "Enter for exit \"~\"\n";
        std::cin >> word;
        std::cout << "\n";
        while (fileName != "~" && word != "~")
        {
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
                    std::cout << "The word \"" << word << "\" has been found " << countWords << " times.\n\n";
                }
                else
                {
                    std::cout << "The word has not been found.\n\n";
                }
            }
            else
            {
                std::cout << "Error! File not found!\n";
            }
            std::cout << "Please give the filename with expansion (ex: \"text.txt\" or \"HW6.cpp\")\n";
            std::cout << "Enter for exit \"~\"\n";
            std::cin >> fileName;
            std::cout << "\n";
            std::cout << "Write the word you're searching for.\n";
            std::cout << "Enter for exit \"~\"\n";
            std::cin >> word;
            std::cout << "\n";
        }
        if (fileName == "~" || word == "~")
            isContinue = false;
    }
    std::cout << "\nEnd of the programme.\n\n";
}
    
