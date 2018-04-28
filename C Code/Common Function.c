/* 공통적으로 많이 사용하는 함수들을 여기에 기록한다. */


/* 함수 사용에 필요한 전처리문 */
/*-------------------------------------*/
#include <stdio.h>
#include <Windows.h>
/*-------------------------------------*/

/* 함수 목록 */
/*----------------------------------------------------------------------------*/

// 콘솔 글자색 변경 코드
void textcolor(int color_number)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

// 커서를 옮겨주는 코드
void gotoxy(short x, short y)
{
	COORD position = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

// 키보드 버퍼 삭제
void clearInputBuffer(void)
{
	// 입력 버퍼에서 문자를 계속 꺼내고 \n를 꺼내면 반복을 중단
	while (getchar() != '\n');
}
/*----------------------------------------------------------------------------*/

/*  제작자: Lulin Pollux (Team Project member) */
/*  MIT License
	해당 C코드파일(.c)은 MIT License에 따라 이용할 수 있습니다. */