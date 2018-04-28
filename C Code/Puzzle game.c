#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define LEFT    75
#define RIGHT   77
#define UP      72
#define DOWN    80

int get_directionkey()	//방향키를 입력받는 함수
{
	printf("\n");
	printf("[ESC]키를 누르면 앱을 종료합니다. \n");
	printf("\n");
	printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤\n");
	printf("▤                                              ▤                          ▤\n");
	printf("▤ ▤▤   ▤  ▤               ▤      ▤▤▤   ▤     ▤  ▤▤ ▤▤▤      ▤\n");
	printf("▤ ▤  ▤ ▤  ▤ ▤▤▤ ▤▤▤ ▤      ▤       ▤     ▤    ▤   ▤        ▤\n");
	printf("▤ ▤▤   ▤  ▤    ▤     ▤  ▤      ▤▤▤   ▤     ▤   ▤      ▤      ▤\n");
	printf("▤ ▤     ▤  ▤  ▤     ▤    ▤      ▤       ▤     ▤  ▤▤ ▤▤▤      ▤\n");
	printf("▤ ▤       ▤   ▤▤▤ ▤▤▤ ▤▤▤  ▤▤▤   ▤                          ▤\n");
	printf("▤                                              ▤      ☆을 다른숫자와     ▤\n");
	printf("▤    ▤▤▤        ▤    ▤      ▤ ▤▤▤     ▤       서로 바꾸면서      ▤\n");
	printf("▤   ▤     ▤    ▤  ▤  ▤▤  ▤▤ ▤         ▤        1  2  3           ▤\n");
	printf("▤   ▤   ▤▤▤ ▤ ▤ ▤ ▤  ▤  ▤ ▤▤▤     ▤        8  ☆ 4           ▤\n");
	printf("▤    ▤     ▤ ▤      ▤▤      ▤ ▤         ▤        7  6  5  로 만들기▤\n");
	printf("▤      ▤▤ ▤▤         ▤      ▤ ▤▤▤     ▤                          ▤\n");
	printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤  ▤▤▤▤▤▤▤▤▤▤▤▤▤▤\n");
	printf("                                                ▤     * 방향키 선택 *      ▤\n");  
	printf("                                                ▤     △   : TOP           ▤\n");
	printf("                                                ▤   ◁  ▷ : Left / Right  ▤\n"); 
	printf("                                                ▤     ▽   : BOTTOM        ▤\n"); 
	printf("                                                ▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤\n"); 
	
	int key;
	key = _getch();
	if (key == 224)//방향키
	{
		return _getch(); //어떤 방향 키인지 반환
	}
	return 0;    //방향키가 아님
}

void print_puzzle(int puzzle[][3])
{
	int w, c;

	system("cls"); //콘솔 화면을 지우기 휴휴
	for (w = 0; w<3; w++)//열 반복
	{
		
		for (c = 0; c<3; c++)//행 반복
		{
			if (puzzle[w][c])//참이면(0이 아니면)
			{
				printf("%4d", puzzle[w][c]);//퍼즐의 수를 출력
			}
			else//거짓(0)이면
			{
				printf("  ☆ ");// 별 출력
			}

		}
		printf("\n");//개행
	}
}

int is_ending(int puzzle[][3])
{
	int w, c;

	for (w = 0; w<3; w++)//열 반복
	{
		for (c = 0; c<3; c++)//행 반복
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

/*  제작자: 이찬휘 (Team Project member) */
/*  MIT License
	해당 C코드파일(.c)은 MIT License에 따라 이용할 수 있습니다. */