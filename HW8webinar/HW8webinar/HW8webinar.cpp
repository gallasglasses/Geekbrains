// HW8webinar.cpp 


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

struct Field
{
	Cell** ppField = nullptr;
	const size_t size = 3;
	size_t move = 0;
	Cell human = EMPTY;
	Cell ai = EMPTY;
	Progress progress = IN_PROGRESS;
};

struct Coord
{
	size_t y;
	size_t x;
};

void ClearScr()
{
	//system("cls");
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
		f.move = 0;
	}
	else
	{
		f.human = ZERO;
		f.ai = CROSS;
		f.move = 1;
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
	std::cout << "     ";
	for (size_t x = 0; x < f.size; x++)
	{
		std::cout << x + 1 << "   ";
	}
	std::cout << "\n";
	for (size_t y = 0; y < f.size; y++)
	{
		std::cout << " " << y + 1 << " | ";
		for (size_t x = 0; x < f.size; x++)
		{
			std::cout << (char)f.ppField[y][x] << " | ";
		}
		std::cout << "\n";
	}
	std::cout << "\n" << " Human: " << (char)f.human << "\n" << " Computer: " << (char)f.ai << "\n";
}

Coord GetHumanCoord(Field& f)
{
	Coord c{};

	do
	{
		std::cout << " Enter coord X (1 .. 3): ";
		std::cin >> c.x;
		std::cout << " Enter coord Y (1 .. 3): ";
		std::cin >> c.y;

	} while (c.x == 0 || c.y == 0 || c.x > f.size || c.y > f.size || f.ppField[c.y - 1][c.x - 1] != EMPTY);

	c.x--;
	c.y--;

	return c;
}

Progress isWon(const Field& f)
{

	for (size_t y = 0; y < f.size; y++)
	{
		if (f.ppField[y][0] == f.ppField[y][1] && f.ppField[y][0] == f.ppField[y][2])
		{
			if (f.ppField[y][0] == f.human)
			{
				return WON_HUMAN;
			}
			else if (f.ppField[y][0] == f.ai)
			{
				return WON_AI;
			}
		}
	}

	for (size_t x = 0; x < f.size; x++)
	{
		if (f.ppField[0][x] == f.ppField[1][x] && f.ppField[0][x] == f.ppField[2][x])
		{
			if (f.ppField[0][x] == f.human)
			{
				return WON_HUMAN;
			}
			else if (f.ppField[0][x] == f.ai)
			{
				return WON_AI;
			}
		}
	}

	if (f.ppField[0][0] == f.ppField[1][1] && f.ppField[0][0] == f.ppField[2][2])
	{
		if (f.ppField[1][1] == f.human)
		{
			return WON_HUMAN;
		}
		else if (f.ppField[1][1] == f.ai)
		{
			return WON_AI;
		}
	}

	if (f.ppField[2][0] == f.ppField[1][1] && f.ppField[2][0] == f.ppField[0][2])
	{
		if (f.ppField[1][1] == f.human)
		{
			return WON_HUMAN;
		}
		else if (f.ppField[1][1] == f.ai)
		{
			return WON_AI;
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

Coord GetAICoord(Field& f)
{
	Coord c{};

	for (size_t y = 0; y < f.size; y++)
	{
		for (size_t x = 0; x < f.size; x++)
		{
			if (f.ppField[y][x] == EMPTY)
			{
				f.ppField[y][x] = f.ai;
				if (isWon(f) == WON_AI)
				{
					f.ppField[y][x] = EMPTY;
					return { y, x };
				}
				f.ppField[y][x] = EMPTY;
			}
		}
	}

	for (size_t y = 0; y < f.size; y++)
	{
		for (size_t x = 0; x < f.size; x++)
		{
			if (f.ppField[y][x] == EMPTY)
			{
				f.ppField[y][x] = f.human;
				if (isWon(f) == WON_HUMAN)
				{
					f.ppField[y][x] = EMPTY;
					return { y, x };
				}
				f.ppField[y][x] = EMPTY;
			}
		}
	}

	//center
	if (f.ppField[1][1] == EMPTY)
	{
		return { 1, 1 };
	}

	Coord buf[4];
	size_t num = 0;

	//corner
	if (f.ppField[0][0] == EMPTY)
	{
		buf[num] = { 0, 0 };
		num++;
	}
	if (f.ppField[2][2] == EMPTY)
	{
		buf[num] = { 2, 2 };
		num++;
	}
	if (f.ppField[0][2] == EMPTY)
	{
		buf[num] = { 0, 2 };
		num++;
	}
	if (f.ppField[2][0] == EMPTY)
	{
		buf[num] = { 2, 0 };
		num++;
	}
	if (num != 0)
	{
		const size_t index = getRandomNum(0, 1000) % num;
		return buf[index];
	}

	//not corner
	num = 0;
	if (f.ppField[0][1] == EMPTY)
	{
		buf[num] = { 0, 1 };
		num++;
	}
	if (f.ppField[2][1] == EMPTY)
	{
		buf[num] = { 2, 1 };
		num++;
	}
	if (f.ppField[1][0] == EMPTY)
	{
		buf[num] = { 1, 0 };
		num++;
	}
	if (f.ppField[1][2] == EMPTY)
	{
		buf[num] = { 1, 2 };
		num++;
	}
	if (num != 0)
	{
		const size_t index = getRandomNum(0, 1000) % num;
		return buf[index];
	}

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
	InitGame(f);
	DrawField(f);
	do
	{
		if (f.move % 2 == 0)
		{
			Coord c = GetHumanCoord(f);
			f.ppField[c.y][c.x] = f.human;
		}
		else
		{
			Coord c = GetAICoord(f);
			f.ppField[c.y][c.x] = f.ai;
		}

		f.move++;
		ClearScr();
		DrawField(f);

		f.progress = isWon(f);

	} while (f.progress == IN_PROGRESS);

	Congrats(f);

	DenitGame(f);

	return 0;
}
