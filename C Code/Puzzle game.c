#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define LEFT    75
#define RIGHT   77
#define UP      72
#define DOWN    80

int get_directionkey()	//����Ű�� �Է¹޴� �Լ�
{
	printf("\n");
	printf("[ESC]Ű�� ������ ���� �����մϴ�. \n");
	printf("\n");
	printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�\n");
	printf("��                                              ��                          ��\n");
	printf("�� �Ǣ�   ��  ��               ��      �ǢǢ�   ��     ��  �Ǣ� �ǢǢ�      ��\n");
	printf("�� ��  �� ��  �� �ǢǢ� �ǢǢ� ��      ��       ��     ��    ��   ��        ��\n");
	printf("�� �Ǣ�   ��  ��    ��     ��  ��      �ǢǢ�   ��     ��   ��      ��      ��\n");
	printf("�� ��     ��  ��  ��     ��    ��      ��       ��     ��  �Ǣ� �ǢǢ�      ��\n");
	printf("�� ��       ��   �ǢǢ� �ǢǢ� �ǢǢ�  �ǢǢ�   ��                          ��\n");
	printf("��                                              ��      ���� �ٸ����ڿ�     ��\n");
	printf("��    �ǢǢ�        ��    ��      �� �ǢǢ�     ��       ���� �ٲٸ鼭      ��\n");
	printf("��   ��     ��    ��  ��  �Ǣ�  �Ǣ� ��         ��        1  2  3           ��\n");
	printf("��   ��   �ǢǢ� �� �� �� ��  ��  �� �ǢǢ�     ��        8  �� 4           ��\n");
	printf("��    ��     �� ��      �Ǣ�      �� ��         ��        7  6  5  �� ������\n");
	printf("��      �Ǣ� �Ǣ�         ��      �� �ǢǢ�     ��                          ��\n");
	printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�  �ǢǢǢǢǢǢǢǢǢǢǢǢǢ�\n");
	printf("                                                ��     * ����Ű ���� *      ��\n");  
	printf("                                                ��     ��   : TOP           ��\n");
	printf("                                                ��   ��  �� : Left / Right  ��\n"); 
	printf("                                                ��     ��   : BOTTOM        ��\n"); 
	printf("                                                �ǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�\n"); 
	
	int key;
	key = _getch();
	if (key == 224)//����Ű
	{
		return _getch(); //� ���� Ű���� ��ȯ
	}
	return 0;    //����Ű�� �ƴ�
}

void print_puzzle(int puzzle[][3])
{
	int w, c;

	system("cls"); //�ܼ� ȭ���� ����� ����
	for (w = 0; w<3; w++)//�� �ݺ�
	{
		
		for (c = 0; c<3; c++)//�� �ݺ�
		{
			if (puzzle[w][c])//���̸�(0�� �ƴϸ�)
			{
				printf("%4d", puzzle[w][c]);//������ ���� ���
			}
			else//����(0)�̸�
			{
				printf("  �� ");// �� ���
			}

		}
		printf("\n");//����
	}
}

int is_ending(int puzzle[][3])
{
	int w, c;

	for (w = 0; w<3; w++)//�� �ݺ�
	{
		for (c = 0; c<3; c++)//�� �ݺ�
		{
			if (puzzle[w][c] != w * 3 + c + 1)
			{
				return (w == 2) && (c == 2);
			}
		}
	}
	return 0;
}

int PuzzleGame()
{
	int puzzle[3][3] = { { 1,3,2 },{ 7,8,4 },{ 6,5,0 } };
	int row = 2;
	int col = 2;
	int key = 0;
	
	while (!is_ending(puzzle))
	{
		if (GetKeyState(VK_ESCAPE) & 0xFF00)
			return 0;

		print_puzzle(puzzle);
		key = get_directionkey();

		switch (key)
		{
		case RIGHT:
			if (col>0)
			{
				puzzle[row][col] = puzzle[row][col - 1];
				puzzle[row][col - 1] = 0;
				col--;
			}

			break;
		case LEFT:
			if (col<3 - 1)
			{
				puzzle[row][col] = puzzle[row][col + 1];
				puzzle[row][col + 1] = 0;
				col++;
			}
			break;
		case UP:
			if (row<3 - 1)
			{
				puzzle[row][col] = puzzle[row + 1][col];
				puzzle[row + 1][col] = 0;
				row++;
			}
			break;
		case DOWN:
			if (row>0)
			{
				puzzle[row][col] = puzzle[row - 1][col];
				puzzle[row - 1][col] = 0;
				row--;
			}
			break;
		}
	}
	return 0;
}

/*  ������: ������ (Team Project member) */
/*  MIT License
	�ش� C�ڵ�����(.c)�� MIT License�� ���� �̿��� �� �ֽ��ϴ�. */