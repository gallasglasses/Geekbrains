#include <iostream>

const int SIZE = 3;

// №2
enum MoveOptions {
    SPACE ='_',
    ZERO ='O',
    CROSS ='X'
};

// №4
struct Field {
    bool isGameEnded; // If the game continues, the field is updated and a new move is made.
    bool isCellEmpty; // Checking the current move to an empty cell.
    char gField[SIZE][SIZE]; // The array is equal to the size of the playing field
    MoveOptions gameFigure;
};
struct Game {  
    Field tic_tac_toe;
    char winner; // who is the winner?
    char currentFigure; // What's the current move?
    char humanFigure; // What kind of figure a human moves?
    char computerFigure; // What kind of figure a computer moves?
    int humanMove; // Coordinate of the person's move
    int computerMove; // Coordinate of the computer's move
    char questionsYesNo; // Questions yes or no (kind of figure, current move)
    int humanScore;
    int computerScore;
};

// №5
struct types {
    unsigned isInt : 1;
    unsigned isChar : 1;
    unsigned isFloat : 1;
};


union UniInfo {
    int iInfo;
    char cInfo;
    float fInfo;
};

struct MyVar {
    types flag;
    UniInfo u1;
};

void data_types(); // Prototype №1 
void enumeration(); // Prototype №3 

int main()
{
       
    // №1 
    data_types();
    std::cout << std::endl;

    // №2 & №3 
    enumeration();
    std::cout << std::endl;

    // №5 - не уверена, что правильно поняла задание
    MyVar var1;

    var1.flag.isInt = 1;
    var1.flag.isChar = 0;
    var1.flag.isFloat = 0;
 
    var1.u1.fInfo = 3.75f;
    var1.u1.cInfo = 'A';
    var1.u1.iInfo = 45;
    
    
    if (var1.flag.isInt == 1)
        std::cout << "flag int: " << var1.flag.isInt << " union int: " << var1.u1.iInfo << std::endl;
    else if (var1.flag.isChar == 1)
    std::cout << "flag char: " << var1.flag.isChar << " union char: " << var1.u1.cInfo << std::endl;
    else std::cout << "flag float: " << var1.flag.isFloat << " union float: " << var1.u1.fInfo << std::endl;

    std::cin.get();
    std::cin.get();

    return 0;
}

// №1 
void data_types ()
{

    short int a = 3;
    std::cout << typeid(a).name()<<" : " << a << std::endl;
    int b = 30'567;
    std::cout << typeid(b).name() << " : " << b << std::endl;
    long long c = 9'223'372'036'854'775'807;
    std::cout << typeid(c).name() << " : " << c << std::endl;
    char d = 'd';
    std::cout << typeid(d).name() << " : " << d << std::endl;
    bool e = true;
    std::cout << typeid(e).name() << " : " << e << std::endl;
    float f = 1.012f;
    std::cout << typeid(f).name() << " : " << f << std::endl;
    double g = 1.01234;
    std::cout << typeid(g).name() << " : " << g << std::endl;
    
}

// №3
void enumeration()
{
    MoveOptions gField[SIZE][SIZE] = { {ZERO,SPACE,ZERO}, {ZERO,CROSS,SPACE}, {CROSS,CROSS,CROSS} }; // in a real game, at the beginning of the game there should be spaces everywhere
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (gField[i][j] == ZERO)
                std::cout << "O";
            else if (gField[i][j] == CROSS)
                std::cout << "X";
            else  std::cout << "_" ; // An underscore is used instead of a space for clarity.
        }
        std::cout << std::endl;
    }

}