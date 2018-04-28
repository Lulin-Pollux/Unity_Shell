#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "functionheader.h"

#define RED 12
#define WHITE 15
#define LINE 8			// ���μ��� ���� ��ų �� �ֽ��ϴ�.
#define MAX (LINE*4)

//----------------------------------------------------------------
// ladder game ���� �Լ� ���
int baserand(int x, int y)		// ���� ���� ����
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

	for (i = 0; i < 20; i++)		//������ �߱�
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

	for (i = 0; i<20; i++)		//���� �߱�
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
	printf("\n%d �� ��÷ \n", (x / 4) + 1);
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
		printf("\n����� ���� ( 1 ~ %d ) : ", LINE);
		while (1)
		{
			scanf_s("%d", &Select);
			clearInputBuffer();

			if ((Select <= 0) || (Select > LINE))
			{
				printf("�ٽ� �Է��ϼ���: ");
			}
			else
				break;
		}

		Select--;
		system("cls");

		VerticalSet(MAP);		// ���μ� ����
		HorizonSet(MAP);		// ���μ� ����
		PrintLine(MAP);
		LadderStart(MAP, Select);

		printf("�ٽ� �ϰ� �ʹٸ� 'start'��, ���� �����ϰ� �ʹٸ� 'quit'�� �Է����ּ���: ");
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
				printf("�߸��� ����� �Է��߽��ϴ�. �ٽ� �Է����ּ���. ");
		}
	}
}

/*  ������: ������ (Team Project member) */
/*  MIT License
	�ش� C�ڵ�����(.c)�� MIT License�� ���� �̿��� �� �ֽ��ϴ�. */