#include <stdio.h>
#include <math.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define KEY_ESC 27


double man(int x1, int x2, int y1, int y2)
{
	return fabs(x1 - x2) + fabs(y1 - y2);
}

double eu(int x1, int x2, int y1, int y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void q1()
{
	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;

	while (1)
	{
		printf("*** 첫 번쨰 좌표 입력:");
		scanf_s("%d %d", &x1, &y1);
		printf("*** 두 번쨰 좌표 입력:");
		scanf_s("%d %d", &x2, &y2);
		if (x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0)
		{
			printf("* 프로그램을 종료합니다. *");
			break;
		}
		else
		{
			printf(">>> 맨허튼 거리: %f\n", man(x1, y1, x2, y2));
			printf(">>> 직선 거리: %f", eu(x1, y1, x2, y2));
		}
		printf("\n");
	}
}

//--------------------------------------------------------------------------------

void GotoXY(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Draw(int x, int y, int symbol)
{
	GotoXY(x, y);
	printf("%c", symbol);
}

void Erase(int x, int y)
{
	GotoXY(x, y);
	printf(" ");
}

double GetElapsedTime(clock_t initial_clock, clock_t current_clock)
{
	return (double)(current_clock - initial_clock) / CLOCKS_PER_SEC;
}

int Move(int x, int y, char symbol)
{
	int prevX = x;
	int move_distance = rand() % 3 + 1;
	x += move_distance;
	Draw(x, y, symbol);
	Erase(prevX, y);
	return x;
}

void q2()
{
	system("mode CON COLS=110 LINES=25");
	for (int i = 0; i <= 15; i++)
	{
		GotoXY(100, i);
		printf("│");
	}

	int X1 = 0, Y1 = 3;
	int X2 = 0, Y2 = 6;
	int X3 = 0, Y3 = 9;
	int X4 = 0, Y4 = 12;

	GotoXY(X1, Y1); printf("1");
	GotoXY(X2, Y2); printf("2");
	GotoXY(X3, Y3); printf("3");
	GotoXY(X4, Y4); printf("4");

	clock_t initial_clock = clock();
	int rank = 1;
	while (1)
	{
		clock_t current_clock = clock();
		if (GetElapsedTime(initial_clock, current_clock) >= 0.5)
		{
			if (X1 < 100)
			{
				X1 = Move(X1, Y1, '1');
				if (X1 >= 100)
				{
					GotoXY(0, 13 + rank);
					printf("%d등은 '%d'입니다.", rank++, 1);
				}
			}
			if (X2 < 100)
			{
				X2 = Move(X2, Y2, '2');
				if (X2 >= 100)
				{
					GotoXY(0, 13 + rank);
					printf("%d등은 '%d'입니다.", rank++, 2);
				}
			}
			if (X3 < 100)
			{
				X3 = Move(X3, Y3, '3');
				if (X3 >= 100)
				{
					GotoXY(0, 13 + rank);
					printf("%d등은 '%d'입니다.", rank++, 3);
				}
			}
			if (X4 < 100)
			{
				X4 = Move(X4, Y4, '4');
				if (X4 >= 100)
				{
					GotoXY(0, 13 + rank);
					printf("%d등은 '%d'입니다.", rank++, 4);
				}
			}
			initial_clock = clock();
		}
		if (_kbhit())
			if (_getch() == KEY_ESC)
				break;
		if (rank == 5)
			break;
	}
}

int main(void)
{
	srand(time(NULL));
	q1();
	q2();
}