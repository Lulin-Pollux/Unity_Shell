#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "functionheader.h"

#define RED 12
#define WHITE 15
#define LINE 8			// 라인수를 증가 시킬 수 있습니다.
#define MAX (LINE*4)

//----------------------------------------------------------------
// ladder game 내부 함수 목록
int baserand(int x, int y)		// 랜덤 범위 지정
{
	static int z = 0;
	int tmp;

	if (z == 0)
	{
		srand((int)time(NULL));
		rand(); rand(); rand(); rand();
		srand(rand());

		z = 1;
	}
	tmp = rand() % (y - x + 1) + x;
	return tmp;
}

void VerticalSet(int MAP[20][MAX])
{
	int i, j;

	for (i = 0; i < 20; i++)		//수직선 긋기
	{
		for (j = 0; j < MAX; j++)
		{
			if ((j % 4 == 0))
				MAP[i][j] = 5;
			else
				MAP[i][j] = 0;
		}
	}
}

void HorizonSet(int MAP[20][MAX])
{
	int i, j;
	int x, y;

	for (i = 0; i<20; i++)		//수평선 긋기
	{
		x = baserand(0, LINE - 2) * 4;
		y = baserand(1, 19);

		if (MAP[y][x + 4] == 5 && MAP[y][x - 4] == 5)
		{
			j = x;

			MAP[y][j++] = 25;

			for (; j<x + 4; j++)
			{
				MAP[y][j] = 6;
			}

			MAP[y][j] = 23;
		}
	}
}

void PrintLine(int MAP[20][MAX])
{
	int i, j;

	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < MAX; j++)
		{
			switch (MAP[i][j])
			{
			case 0:
				printf(" ");
				break;
			case 6:
				printf("%c", MAP[i][j]);
				break;
			default:
				printf("%c", MAP[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");

	for (i = 1; i < LINE + 1; i++)
	{
		printf("%-4d", i);
	}
	printf("\n\n");
}

void LadderStart(int MAP[20][MAX], int Select)
{
	int i;
	int x, y;

	x = Select * 4;
	y = 0;

	for (y = 0; y < 20; y++)
	{
		if (MAP[y][x] == 25)
		{
			for (i = x; i < x + 4; i++)
			{
				Sleep(200);
				gotoxy(i, y);
				textcolor(RED);

				printf("%c", MAP[y][i]);
			}
			x = i;
		}
		else if (MAP[y][x] == 23)
		{
			for (i = x; i > x - 4; i--)
			{
				Sleep(200);
				gotoxy(i, y);
				textcolor(RED);

				printf("%c", MAP[y][i]);
			}
			x = i;
		}
		Sleep(200);
		gotoxy(x, y);
		textcolor(RED);

		printf("%c", MAP[y][x]);
	}
	textcolor(WHITE);
	gotoxy(0, 22);

	textcolor(14);
	printf("\n%d 번 당첨 \n", (x / 4) + 1);
	textcolor(15);
}
//----------------------------------------------------------------

void LadderGame(void)
{
	int MAP[20][MAX];
	int Select;
	char input[100];

	while (1)
	{
		printf("\n출발점 설정 ( 1 ~ %d ) : ", LINE);
		while (1)
		{
			scanf_s("%d", &Select);
			clearInputBuffer();

			if ((Select <= 0) || (Select > LINE))
			{
				printf("다시 입력하세요: ");
			}
			else
				break;
		}

		Select--;
		system("cls");

		VerticalSet(MAP);		// 세로선 설정
		HorizonSet(MAP);		// 가로선 설정
		PrintLine(MAP);
		LadderStart(MAP, Select);

		printf("다시 하고 싶다면 'start'를, 앱을 종료하고 싶다면 'quit'를 입력해주세요: ");
		while (1)
		{
			gets_s(input, sizeof(input));

			if (strcmp(input, "start") == 0)
			{
				system("cls");
				break;
			}
			else if (strcmp(input, "quit") == 0)
				return;
			else
				printf("잘못된 명령을 입력했습니다. 다시 입력해주세요. ");
		}
	}
}

/*  제작자: 오광준 (Team Project member) */
/*  MIT License
	해당 C코드파일(.c)은 MIT License에 따라 이용할 수 있습니다. */