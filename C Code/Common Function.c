/* ���������� ���� ����ϴ� �Լ����� ���⿡ ����Ѵ�. */


/* �Լ� ��뿡 �ʿ��� ��ó���� */
/*-------------------------------------*/
#include <stdio.h>
#include <Windows.h>
/*-------------------------------------*/

/* �Լ� ��� */
/*----------------------------------------------------------------------------*/

// �ܼ� ���ڻ� ���� �ڵ�
void textcolor(int color_number)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

// Ŀ���� �Ű��ִ� �ڵ�
void gotoxy(short x, short y)
{
	COORD position = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

// Ű���� ���� ����
void clearInputBuffer(void)
{
	// �Է� ���ۿ��� ���ڸ� ��� ������ \n�� ������ �ݺ��� �ߴ�
	while (getchar() != '\n');
}
/*----------------------------------------------------------------------------*/

/*  ������: Lulin Pollux (Team Project member) */
/*  MIT License
	�ش� C�ڵ�����(.c)�� MIT License�� ���� �̿��� �� �ֽ��ϴ�. */