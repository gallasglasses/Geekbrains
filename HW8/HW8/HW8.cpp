

#include <iostream>
#include <random>
#include <Windows.h>
#include <stdlib.h>
#include <chrono>

enum Cell
{
	CROSS = 'X',
	ZERO = '0',
	EMPTY = ' '
};

enum Progress
{
	IN_PROGRESS,
	WON_HUMAN,
	WON_AI,
	DRAW
};

const size_t LengthForWin1 = 3,
			 LengthForWin2 = 5;

struct Field
{
	Cell** ppField = nullptr;
	Cell human = EMPTY;
	Cell ai = EMPTY;

	size_t size{},
		   whoseMove = 0,
		   countMove = 0,
		   sizeLine;
	
	Progress progress = IN_PROGRESS;
};


struct Coord
{
	size_t y;
	size_t x;
};

struct LastCoord
{
	size_t y;
	size_t x;
};

Field GetSizeField(Field& f)
{
	std::cout << " Enter field size: ";
	std::cin >> f.size;

	if (f.size == 3 || f.size == 4)
		f.sizeLine = LengthForWin1;
	else f.sizeLine = LengthForWin2;
	return f;
}

void ClearScr()
{
	system("cls");
	std::cout << "\x1B[2J\x1B[H";
}

int32_t getRandomNum(int32_t min, int32_t max)
{
	const static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	static std::mt19937_64 generator(seed);
	std::uniform_int_distribution<int32_t> dis(min, max);
	return dis(generator);
}

void InitGame(Field& f)
{
	f.ppField = new Cell * [f.size];
	for (size_t y = 0; y < f.size; y++)
	{
		f.ppField[y] = new Cell[f.size];
	}

	for (size_t y = 0; y < f.size; y++)
	{
		for (size_t x = 0; x < f.size; x++)
		{
			f.ppField[y][x] = EMPTY;
		}
	}

	if (getRandomNum(0, 1000) > 500)
	{
		f.human = CROSS;
		f.ai = ZERO;
		f.whoseMove = 0;
		f.countMove = 0;
	}
	else
	{
		f.human = ZERO;
		f.ai = CROSS;
		f.whoseMove = 1;
		f.countMove = 0;
	}
}

void DenitGame(Field& f)
{
	for (size_t y = 0; y < f.size; y++)
	{
		delete[] f.ppField[y];
	}

	delete[] f.ppField;
}

void DrawField(const Field& f)
{
	std::cout << "\n";
	std::cout << "         ";
	for (size_t x = 0; x < f.size; x++)
	{
		std::cout << x + 1 << "   ";
	}
	std::cout << "\n";
	for (size_t y = 0; y < f.size; y++)
	{
		std::cout.width(6);
		std::cout << std::right << y + 1 << " | ";
		for (size_t x = 0; x < f.size; x++)
		{
			std::cout << (char)f.ppField[y][x] << " | ";
		}
		std::cout << "\n";
	}
	std::cout << "\n" << " Human: " << (char)f.human << "\n" << " Computer: " << (char)f.ai << "\n";
	std::cout << " Line is " << f.sizeLine << "\n";
}

Coord GetHumanCoord(Field& f)
{
	Coord c{};

	do
	{
		std::cout << " Enter coord X (1 .. " << f.size << "): ";
		std::cin >> c.x;
		std::cout << " Enter coord Y (1 .. " << f.size << "): ";
		std::cin >> c.y;

	} while (c.x < 1 || c.y < 1 || c.x > f.size || c.y > f.size || f.ppField[c.y-1][c.x-1] != EMPTY);

	c.x--;
	c.y--;
	return c;
}

Progress isWon(const Field& f)
{
	// y, x+1 right
	for (size_t y = 0; y < f.size; y++) 
	{
		for (size_t x = 0; x < f.size-1; x++)
		{
			if (f.ppField[y][x] != EMPTY)
			{
				size_t checkY = y,
					checkX = x,
					countEqualMoves = 0;
				char comparator = f.ppField[y][x];

				for (; checkX < f.size - 1; checkX++)
				{
					if (f.ppField[checkY][checkX + 1] == comparator)
					{
						countEqualMoves++;
					}
					else
					{
						countEqualMoves = 0;
						x = checkX + 1;
						break;
					}
					if (countEqualMoves == f.sizeLine - 1)
					{
						if (comparator == f.human)
						{
							return WON_HUMAN;
						}
						else if (comparator == f.ai)
						{
							return WON_AI;
						}
					}
				}
			}
		}
	}
	// y+1, x down
	for (size_t x = 0; x < f.size; x++)
	{
		for (size_t y = 0; y < f.size - 1; y++)
		{
			if (f.ppField[y][x] != EMPTY)
			{
				size_t checkY = y,
					checkX = x,
					countEqualMoves = 0;
				char comparator = f.ppField[y][x];

				for (; checkY < f.size - 1; checkY++)
				{
					if (f.ppField[checkY + 1][checkX] == comparator)
					{
						countEqualMoves++;
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
					if (countEqualMoves == f.sizeLine - 1)
					{
						if (comparator == f.human)
						{
							return WON_HUMAN;
						}
						else if (comparator == f.ai)
						{
							return WON_AI;
						}
					}
				}
			}
		}
	}
	// y+1+i, x+1 diagonal right down
	for (size_t i = 0; i <= (f.size - f.sizeLine); i++)
	{
		for (size_t y = 0; y < f.size - 1 - i; y++)
		{
			if (f.ppField[y + i][y] != EMPTY)
			{
				size_t checkY = y,
					countEqualMoves = 0;
				char comparator = f.ppField[y + i][y];

				for (; checkY < f.size - 1 - i; checkY++)
				{
					if (f.ppField[checkY + i + 1][checkY + 1] == comparator)
					{
						countEqualMoves++;
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
					if (countEqualMoves == f.sizeLine - 1)
					{
						if (comparator == f.human)
						{
							return WON_HUMAN;
						}
						else if (comparator == f.ai)
						{
							return WON_AI;
						}
					}
				}
			}
		}
	}
	// y+1, x+1+i diagonal right down
	for (size_t i = 1; i <= (f.size - f.sizeLine); i++)
	{
		for (size_t y = 0; y < f.size - 1 - i; y++)
		{
			if (f.ppField[y][y + i] != EMPTY)
			{
				size_t checkY = y,
					countEqualMoves = 0;
				char comparator = f.ppField[y][y + i];

				for (; checkY < f.size - 1 - i; checkY++)
				{
					if (f.ppField[checkY + 1][checkY + 1 + i] == comparator)
					{
						countEqualMoves++;
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
					if (countEqualMoves == f.sizeLine - 1)
					{
						if (comparator == f.human)
						{
							return WON_HUMAN;
						}
						else if (comparator == f.ai)
						{
							return WON_AI;
						}
					}
				}
			}
		}
	}
	// y+1, x-1-i diagonal left down
	for (size_t i = 0; i <= (f.size - f.sizeLine); i++)
	{
		for (size_t y = 0, x = f.size - 1; (y <= (f.size - f.sizeLine)) && (x >= (f.sizeLine - 1)); y++, x--)
		{
			if (f.ppField[y][x - i] != EMPTY)
			{
				size_t checkY = y,
					checkX = x,
					countEqualMoves = 0;
				char comparator = f.ppField[y][x - i];

				for (; ((checkY >= 0) && (checkY < f.size - 1 - i)) && ((checkX >= (f.sizeLine - 1)) && (checkX <= f.size - 1)); checkY++, checkX--)
				{
					if (f.ppField[checkY + 1][checkX - 1 - i] == comparator)
					{
						countEqualMoves++;
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
					if (countEqualMoves == f.sizeLine - 1)
					{
						if (comparator == f.human)
						{
							return WON_HUMAN;
						}
						else if (comparator == f.ai)
						{
							return WON_AI;
						}
					}
				}
			}
		}
	}
	// y+1+i, x-1 diagonal left down
	for (size_t i = 1; i <= (f.size - f.sizeLine); i++)
	{
		for (size_t y = 0, x = f.size - 1; (y < f.size - 1 - i) && (x >= (f.sizeLine - 1)); y++, x--)
		{
			if (f.ppField[y + i][x] != EMPTY)
			{
				size_t checkY = y,
					checkX = x,
					countEqualMoves = 0;
				char comparator = f.ppField[y + i][x];

				for (; ((checkY >= 0) && (checkY < f.size - 1 - i)) && ((checkX >= (f.sizeLine - 1)) && (checkX <= f.size - 1)); checkY++, checkX--)
				{
					if (f.ppField[checkY + i + 1][checkX - 1] == comparator)
					{
						countEqualMoves++;
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
					if (countEqualMoves == f.sizeLine - 1)
					{
						if (comparator == f.human)
						{
							return WON_HUMAN;
						}
						else if (comparator == f.ai)
						{
							return WON_AI;
						}
					}
				}
			}
		}
	}
	// y-1+i, x-1 diagonal left up +
	for (size_t i = 0; i <= (f.size - f.sizeLine); i++)
	{
		for (size_t y = f.size - 1 - i; y >= (f.sizeLine - 1); y--)
		{
			if (f.ppField[y + i][y] != EMPTY)
			{
				size_t checkY = y,
					countEqualMoves = 0;
				char comparator = f.ppField[y + i][y];

				for (; (checkY >= (f.sizeLine - 1)) && (checkY <= f.size - 1 - i); checkY--)
				{
					if (f.ppField[checkY - 1 + i][checkY - 1] == comparator)
					{
						countEqualMoves++;
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
					if (countEqualMoves == f.sizeLine - 1)
					{
						if (comparator == f.human)
						{
							return WON_HUMAN;
						}
						else if (comparator == f.ai)
						{
							return WON_AI;
						}
					}
				}
			}
		}
	}
	// y-1, x-1+i diagonal left up +
	for (size_t i = 1; i <= (f.size - f.sizeLine); i++)
	{
		for (size_t y = f.size - 1 - i; y >= (f.sizeLine - 1); y--)
		{

			if (f.ppField[y][y + i] != EMPTY)
			{
				size_t checkY = y,
					countEqualMoves = 0;
				char comparator = f.ppField[y][y + i];

				for (; (checkY >= (f.sizeLine - 1)) && (checkY <= f.size - 1 - i); checkY--)
				{
					if (f.ppField[checkY - 1][checkY - 1 + i] == comparator)
					{
						countEqualMoves++;
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
					if (countEqualMoves == f.sizeLine - 1)
					{
						if (comparator == f.human)
						{
							return WON_HUMAN;
						}
						else if (comparator == f.ai)
						{
							return WON_AI;
						}
					}
				}
			}
		}
	}
	// y, x-1 left
	for (size_t y = 0; y < f.size; y++)
	{
		for (size_t x = f.size - 1; x >= 1; x--)
		{
			if (f.ppField[y][x] != EMPTY)
			{
				size_t checkY = y,
					checkX = x,
					countEqualMoves = 0;
				char comparator = f.ppField[y][x];

				for (; ((checkY >= 0) && (checkY < f.size)) && ((checkX >= 1) && (checkX < f.size - 1)); checkX--)
				{
					if (f.ppField[checkY][checkX - 1] == comparator)
					{
						countEqualMoves++;
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
					if (countEqualMoves == f.sizeLine - 1)
					{
						if (comparator == f.human)
						{
							return WON_HUMAN;
						}
						else if (comparator == f.ai)
						{
							return WON_AI;
						}
					}
				}
			}
		}
	}
	// y-1, x up
	for (size_t x = 0; x < f.size; x++)
	{
		for (size_t y = f.size - 1; y >= 1; y--)
		{
			if (f.ppField[y][x] != EMPTY)
			{
				size_t checkY = y,
					checkX = x,
					countEqualMoves = 0;
				char comparator = f.ppField[y][x];

				for (; (checkY >= 1) && (checkY < f.size - 1); checkY--)
				{
					if (f.ppField[checkY - 1][checkX] == comparator)
					{
						countEqualMoves++;
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
					if (countEqualMoves == f.sizeLine - 1)
					{
						if (comparator == f.human)
						{
							return WON_HUMAN;
						}
						else if (comparator == f.ai)
						{
							return WON_AI;
						}
					}
				}
			}
		}
	}


	bool draw = true;
	for (size_t y = 0; y < f.size; y++)
	{
		for (size_t x = 0; x < f.size; x++)
		{
			if (f.ppField[y][x] == EMPTY)
			{
				draw = false;
				break;
			}
		}

		if (!draw)
		{
			break;
		}
	}

	if (draw)
	{
		return DRAW;
	}

	return IN_PROGRESS;
}

Coord GetAICoord(Field &f)
{
	Coord c{};
		
	do
	{

		Coord buf[100]{};

		size_t num = 0;
		
		if (f.countMove == 0 || f.countMove == 1)
		{
			if (f.size % 2 == 0)
			{
				if (f.ppField[f.size / 2 - 1][f.size / 2 - 1] == EMPTY)
				{
					buf[num] = { f.size / 2 - 1, f.size / 2 - 1 };
					num++;
				}
				else if (f.ppField[f.size / 2][f.size / 2 - 1] == EMPTY)
				{
					buf[num] = { f.size / 2, f.size / 2 - 1 };
					num++;
				}
				else if (f.ppField[f.size / 2 - 1][f.size / 2] == EMPTY)
				{
					buf[num] = { f.size / 2 - 1, f.size / 2 };
					num++;
				}
				else if (f.ppField[f.size / 2][f.size / 2] == EMPTY)
				{
					buf[num] = { f.size / 2, f.size / 2 };
					num++;
				}
				const size_t index1 = getRandomNum(0, 1000) % (f.size - 1);
				const size_t index2 = getRandomNum(0, 1000) % (f.size - 1);
				if (f.ppField[index1][index2] == EMPTY)
				{
					buf[num] = { index1, index2 };
					num++;
				}
				if (num != 0)
				{
					const size_t index = getRandomNum(0, 1000) % num;
					return { buf[index].y, buf[index].x };
				}
			}
			else
			{
				if (f.ppField[f.size / 2][f.size / 2] == EMPTY)
				{
					return { f.size / 2, f.size / 2 };
				}
				const size_t index1 = getRandomNum(0, 1000) % (f.size - 1);
				const size_t index2 = getRandomNum(0, 1000) % (f.size - 1);
				if (f.ppField[index1][index2] == EMPTY)
				{
					buf[num] = { index1, index2 };
					num++;
				}
				if (num != 0)
				{
					const size_t index = getRandomNum(0, 1000) % num;
					return { buf[index].y, buf[index].x };
				}
			}
		}

		num = 0;
		{
			
			size_t maxCountEqualMoves = 0,
				maxIndex = 0,
				countEqualMoves = 0;

			// y, x+1 right
			for (size_t y = 0; y < f.size; y++)
			{
				for (size_t x = 0; x < f.size - 1; x++)
				{

					if (f.ppField[y][x + 1] == f.human && f.ppField[y][x] == f.human)
					{
						countEqualMoves++;
					}
					else if (f.ppField[y][x + 1] == EMPTY && f.ppField[y][x] == f.human)
					{
						if (countEqualMoves == ((f.sizeLine - 1) - 1))
						{
							buf[num] = { y, x + 1 };
							num++;
						}
					}
					else
					{
						countEqualMoves = 0;
						x = x + 1;
						break;
					}
				}
			}

			// y+1, x down +
			for (size_t x = 0; x < f.size; x++)
			{
				for (size_t y = 0; y < f.size - 1; y++)
				{

					if (f.ppField[y + 1][x] == f.human && f.ppField[y][x] == f.human)
					{
						countEqualMoves++;
					}
					else if (f.ppField[y + 1][x] == EMPTY && f.ppField[y][x] == f.human)
					{
						if (countEqualMoves == ((f.sizeLine - 1) - 1))
						{
							buf[num] = { y + 1, x };
							num++;
						}
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
				}
			}

			// y+i+1, x+1 diagonal right down +
			for (size_t i = 0; i <= (f.size - f.sizeLine); i++)
			{
				for (size_t y = 0; y < f.size - 1 - i; y++)
				{

					if (f.ppField[y + 1 + i][y + 1] == f.human && f.ppField[y + i][y] == f.human)
					{
						countEqualMoves++;
					}
					else if (f.ppField[y + 1 + i][y + 1] == EMPTY && f.ppField[y + i][y] == f.human)
					{
						if (countEqualMoves == ((f.sizeLine - 1) - 1))
						{
							buf[num] = { y + 1 + i, y + 1 };
							num++;
						}
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
				}
			}
			// y+1, x+i+1 diagonal right down +
			for (size_t i = 1; i <= (f.size - f.sizeLine); i++)
			{
				for (size_t y = 0; y < f.size - 1 - i; y++)
				{

					if (f.ppField[y + 1][y + 1 + i] == f.human && f.ppField[y][y + i] == f.human)
					{
						countEqualMoves++;
					}
					else if (f.ppField[y + 1][y + 1 + i] == EMPTY && f.ppField[y][y + i] == f.human)
					{
						if (countEqualMoves == ((f.sizeLine - 1) - 1))
						{
							buf[num] = { y + 1 , y + 1 + i };
							num++;
						}
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
				}
			}

			// y+1, x-1-i diagonal left down +
			for (size_t i = 0; i <= (f.size - f.sizeLine); i++)
			{
				for (size_t y = 0, x = f.size - 1; (y <= f.size - 1 - i) && (x >= (f.sizeLine - 1)); y++, x--)
				{
					if (f.ppField[y + 1][x - 1 - i] == f.human && f.ppField[y][x - i] == f.human)
					{
						countEqualMoves++;
					}
					else if (f.ppField[y + 1][x - 1 - i] == EMPTY && f.ppField[y][x - i] == f.human)
					{
						if (countEqualMoves == ((f.sizeLine - 1) - 1))
						{
							buf[num] = { y + 1, x - 1 - i };
							num++;
						}
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
				}
			}

			// y+1+i, x-1 diagonal left down +
			for (size_t i = 1; i <= (f.size - f.sizeLine); i++)
			{
				for (size_t y = 0, x = f.size - 1; (y <= f.size - 1 - i) && (x >= (f.sizeLine - 1)); y++, x--)
				{
					if (f.ppField[y + 1 + i][x - 1] == f.human && f.ppField[y + i][x] == f.human)
					{
						countEqualMoves++;
					}
					else if (f.ppField[y + 1 + i][x - 1] == EMPTY && f.ppField[y + i][x] == f.human)
					{
						if (countEqualMoves == ((f.sizeLine - 1) - 1))
						{
							buf[num] = { y + 1 + i, x - 1 };
							num++;
						}
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
				}
			}

			// y-1+i, x-1 diagonal left up +
			for (size_t i = 0; i <= (f.size - f.sizeLine); i++)
			{
				for (size_t y = f.size - 1 - i; y >= (f.sizeLine - 1); y--)
				{

					if (f.ppField[y - 1 + i][y - 1] == f.human && f.ppField[y + i][y] == f.human)
					{
						countEqualMoves++;
					}
					else if (f.ppField[y + i][y] == f.human && f.ppField[y - 1 + i][y - 1] == EMPTY) //error
					{
						if (countEqualMoves == ((f.sizeLine - 1) - 1))
						{
							buf[num] = { y - 1 + i, y - 1 };
							num++;
						}
						else break;
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
				}
			}

			// y-1, x-1+i diagonal left up +
			for (size_t i = 1; i <= (f.size - f.sizeLine); i++)
			{
				for (size_t y = f.size - 1 - i; y >= (f.sizeLine - 1); y--)
				{

					if (f.ppField[y - 1][y - 1 + i] == f.human && f.ppField[y][y + i] == f.human)
					{
						countEqualMoves++;
					}
					else if (f.ppField[y][y + i] == f.human && f.ppField[y - 1][y - 1 + i] == EMPTY) //error
					{
						if (countEqualMoves == ((f.sizeLine - 1) - 1))
						{
							buf[num] = { y - 1, y - 1 + i };
							num++;
						}
						else break;
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
				}
			}

			// y, x-1 left
			for (size_t y = 0; y < f.size; y++)
			{
				for (size_t x = f.size - 1; x >= 1; x--)
				{
					if (f.ppField[y][x - 1] == f.human && f.ppField[y][x] == f.human)
					{
						countEqualMoves++;
					}
					else if (f.ppField[y][x - 1] == EMPTY && f.ppField[y][x] == f.human)
					{
						if (countEqualMoves == ((f.sizeLine - 1) - 1))
						{
							buf[num] = { y, x - 1 };
							num++;
						}
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
				}
			}

			// y-1, x up
			for (size_t x = 0; x < f.size; x++)
			{
				for (size_t y = f.size - 1; y >= 1; y--)
				{
					if (f.ppField[y - 1][x] == f.human && f.ppField[y][x] == f.human)
					{
						countEqualMoves++;
					}
					else if (f.ppField[y - 1][x] == EMPTY && f.ppField[y][x] == f.human)
					{
						if (countEqualMoves == ((f.sizeLine - 1) - 1))
						{
							buf[num] = { y - 1, x };
							num++;
						}
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
				}
			}

			if (num != 0)
			{
				const size_t index = getRandomNum(0, 1000) % num;
				return { buf[index].y, buf[index].x };
			}
			
			maxCountEqualMoves = 0;
			maxIndex = 0;
			countEqualMoves = 0;

			// y, x+1 right
			for (size_t y = 0; y < f.size; y++)
			{
				for (size_t x = 0; x < f.size - 1; x++)
				{

					if (f.ppField[y][x + 1] == f.ai && f.ppField[y][x] == f.ai)
					{
						countEqualMoves++;
					}
					else if (f.ppField[y][x + 1] == EMPTY && f.ppField[y][x] == f.ai)
					{
						if (countEqualMoves > 1 || countEqualMoves < f.sizeLine - 1)
						{
							buf[num] = { y, x + 1 };
							if (countEqualMoves > maxCountEqualMoves)
							{
								maxCountEqualMoves = countEqualMoves;
								maxIndex = num;
								countEqualMoves = 0;
							}
							num++;
						}
						break;
					}
					else
					{
						countEqualMoves = 0;
						x = x + 1;
						break;
					}
				}
			}

			// y+1, x down
			for (size_t x = 0; x < f.size; x++)
			{
				for (size_t y = 0; y < f.size - 1; y++)
				{

					if (f.ppField[y + 1][x] == f.ai && f.ppField[y][x] == f.ai)
					{
						countEqualMoves++;
					}
					else if (f.ppField[y + 1][x] == EMPTY && f.ppField[y][x] == f.ai)
					{
						if (countEqualMoves > 1 || countEqualMoves < f.sizeLine - 1)
						{
							buf[num] = { y + 1, x };
							if (countEqualMoves > maxCountEqualMoves)
							{
								maxCountEqualMoves = countEqualMoves;
								maxIndex = num;
								countEqualMoves = 0;
							}
							num++;
						}
						break;
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
				}
			}

			// y+1+i, x+1 diagonal right down
			for (size_t i = 0; i <= (f.size - f.sizeLine); i++)
			{
				for (size_t y = 0; y < f.size - 1 - i; y++)
				{
					if (f.ppField[y + 1 + i][y + 1] == f.ai && f.ppField[y + i][y] == f.ai)
					{
						countEqualMoves++;
					}
					else if (f.ppField[y + 1 + i][y + 1] == EMPTY && f.ppField[y + i][y] == f.ai)
					{
						if (countEqualMoves > 1 || countEqualMoves < f.sizeLine - 1)
						{
							buf[num] = { y + 1 + i, y + 1 };
							if (countEqualMoves > maxCountEqualMoves)
							{
								maxCountEqualMoves = countEqualMoves;
								maxIndex = num;
								countEqualMoves = 0;
							}
							num++;
						}
						break;
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
				}
			}

			// y+1, x+1+i diagonal right down
			for (size_t i = 1; i <= (f.size - f.sizeLine); i++)
			{
				for (size_t y = 0; y < f.size - 1 - i; y++)
				{
					if (f.ppField[y + 1][y + 1 + i] == f.ai && f.ppField[y][y + i] == f.ai)
					{
						countEqualMoves++;
					}
					else if (f.ppField[y + 1][y + 1 + i] == EMPTY && f.ppField[y][y + i] == f.ai)
					{
						if (countEqualMoves > 1 || countEqualMoves < f.sizeLine - 1)
						{
							buf[num] = { y + 1, y + 1 + i };
							if (countEqualMoves > maxCountEqualMoves)
							{
								maxCountEqualMoves = countEqualMoves;
								maxIndex = num;
								countEqualMoves = 0;
							}
							num++;
						}
						break;
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
				}
			}

			// y+1, x-1-i diagonal left down
			for (size_t i = 0; i <= (f.size - f.sizeLine); i++)
			{
				for (size_t y = 0, x = f.size - 1; (y < f.size - 1 - i) && (x >= (f.sizeLine - 1)); y++, x--)
				{
					if (f.ppField[y + 1][x - 1 - i] == f.ai && f.ppField[y][x - i] == f.ai)
					{
						countEqualMoves++;
					}
					else if (f.ppField[y + 1][x - 1 - i] == EMPTY && f.ppField[y][x - i] == f.ai)
					{
						if (countEqualMoves > 1 || countEqualMoves < f.sizeLine - 1)
						{
							buf[num] = { y + 1, x - 1 - i };
							if (countEqualMoves > maxCountEqualMoves)
							{
								maxCountEqualMoves = countEqualMoves;
								maxIndex = num;
								countEqualMoves = 0;
							}
							num++;
						}
						break;
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
				}
			}

			// y+1+i, x-1 diagonal left down
			for (size_t i = 1; i <= (f.size - f.sizeLine); i++)
			{
				for (size_t y = 0, x = f.size - 1; (y < f.size - 1 - i) && (x >= (f.sizeLine - 1)); y++, x--)
				{
					if (f.ppField[y + 1 + i][x - 1] == f.ai && f.ppField[y + i][x] == f.ai)
					{
						countEqualMoves++;
					}
					else if (f.ppField[y + 1 + i][x - 1] == EMPTY && f.ppField[y + i][x] == f.ai)
					{
						if (countEqualMoves > 1 || countEqualMoves < f.sizeLine - 1)
						{
							buf[num] = { y + 1 + i, x - 1 };
							if (countEqualMoves > maxCountEqualMoves)
							{
								maxCountEqualMoves = countEqualMoves;
								maxIndex = num;
								countEqualMoves = 0;
							}
							num++;
						}
						break;
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
				}
			}

			// y-1+i, x-1 diagonal left up
			for (size_t i = 0; i <= (f.size - f.sizeLine); i++)
			{
				for (size_t y = f.size - 1 - i; y >= (f.sizeLine - 1); y--)
				{
					if (f.ppField[y - 1 + i][y - 1] == f.ai && f.ppField[y + i][y] == f.ai)
					{
						countEqualMoves++;
					}
					else if (f.ppField[y - 1 + i][y - 1] == EMPTY && f.ppField[y + i][y] == f.ai)
					{
						if (countEqualMoves > 1 || countEqualMoves < f.sizeLine - 1)
						{
							buf[num] = { y - 1 + i, y - 1 };
							if (countEqualMoves > maxCountEqualMoves)
							{
								maxCountEqualMoves = countEqualMoves;
								maxIndex = num;
								countEqualMoves = 0;
							}
							num++;
						}
						break;
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
				}
			}

			// y-1, x-1+i diagonal left up
			for (size_t i = 0; i <= (f.size - f.sizeLine); i++)
			{
				for (size_t y = f.size - 1 - i; y >= (f.sizeLine - 1); y--)
				{
					if (f.ppField[y - 1][y - 1 + i] == f.ai && f.ppField[y][y + i] == f.ai)
					{
						countEqualMoves++;
					}
					else if (f.ppField[y - 1][y - 1 + i] == EMPTY && f.ppField[y][y + i] == f.ai)
					{
						if (countEqualMoves > 1 || countEqualMoves < f.sizeLine - 1)
						{
							buf[num] = { y - 1, y - 1 + i };
							if (countEqualMoves > maxCountEqualMoves)
							{
								maxCountEqualMoves = countEqualMoves;
								maxIndex = num;
								countEqualMoves = 0;
							}
							num++;
						}
						break;
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
				}
			}

			// y, x-1 left
			for (size_t y = 0; y < f.size; y++)
			{
				for (size_t x = f.size - 1; x >= 1; x--)
				{
					if (f.ppField[y][x - 1] == f.ai && f.ppField[y][x] == f.ai)
					{
						countEqualMoves++;
					}
					else if (f.ppField[y][x - 1] == EMPTY && f.ppField[y][x] == f.ai)
					{
						if (countEqualMoves > 1 || countEqualMoves < f.sizeLine - 1)
						{
							buf[num] = { y, x - 1 };
							if (countEqualMoves > maxCountEqualMoves)
							{
								maxCountEqualMoves = countEqualMoves;
								maxIndex = num;
								countEqualMoves = 0;
							}
							num++;
						}
						break;
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
				}
			}

			// y-1, x up
			for (size_t x = 0; x < f.size; x++)
			{
				for (size_t y = f.size - 1; y >= 1; y--)
				{
					if (f.ppField[y - 1][x] == f.ai && f.ppField[y][x] == f.ai)
					{
						countEqualMoves++;
					}
					else if (f.ppField[y - 1][x] == EMPTY && f.ppField[y][x] == f.ai)
					{
						if (countEqualMoves > 1 || countEqualMoves < f.sizeLine - 1)
						{
							buf[num] = { y - 1, x };
							if (countEqualMoves >= maxCountEqualMoves)
							{
								maxCountEqualMoves = countEqualMoves;
								maxIndex = num;
								countEqualMoves = 0;
							}
							num++;
						}
						break;
					}
					else
					{
						countEqualMoves = 0;
						break;
					}
				}
			}
			if (num != 0)
			{
				return { buf[maxIndex].y, buf[maxIndex].x };
			}
			
			else
			{
				for (size_t y = 0; y < f.size; y++)
				{
					for (size_t x = 0; x < f.size; x++)
					{
						if (f.ppField[y][x] == EMPTY)
						{
							buf[num] = { y, x };
							num++;
						}
					}
				}
				if (num != 0)
				{
					const size_t index = getRandomNum(0, 1000) % num;
					return { buf[index].y, buf[index].x };
				}
			}
		}
	} while ( c.x > f.size || c.y > f.size || f.ppField[c.y + 1][c.x + 1] != EMPTY);
	return c;
}

void Congrats(Field& f)
{
	if (f.progress == WON_HUMAN)
	{
		std::cout << " You won! Congrats!\n";
	}
	else if (f.progress == WON_AI)
	{
		std::cout << " Computer won!\n";
	}
	else std::cout << " Draw :(\n";
}

int main()
{
	Field f;
	GetSizeField(f);
	InitGame(f);
	DrawField(f);
	do
	{
		if (f.whoseMove % 2 == 0)
		{
			Coord c = GetHumanCoord(f);
			f.ppField[c.y][c.x] = f.human;
		}
		else
		{
			Coord c = GetAICoord(f);
			f.ppField[c.y][c.x] = f.ai;
		}

		f.whoseMove++;
		f.countMove++;
		ClearScr();
		DrawField(f);

		f.progress = isWon(f);

	} while (f.progress == IN_PROGRESS);
	
	Congrats(f);

	DenitGame(f);

	return 0;
}
