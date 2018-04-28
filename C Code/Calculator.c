#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functionheader.h"

void Calculator(void)
{
	long long num1;
	long long num2;
	long long result;
	char a;
	char input[100];
	
	while (1)
	{
		textcolor(11);
		printf("\n수식을 입력하세요: ");
		textcolor(15);
		scanf_s("%lld %c %lld", &num1, &a, 1, &num2);
		clearInputBuffer();

		switch (a)	//char a의 값에 따라서 case를 설정
		{
		case '+':	//char a의 값이 +일경우 +연산을 한다.
			result = num1 + num2;
			printf("\n %lld %c %lld = %lld \n", num1, a, num2, result);
			break;
		case '-':	//char a의 값이 -일경우 -연산을 한다.
			result = num1 - num2;
			printf("\n %lld %c %lld = %lld \n", num1, a, num2, result);
			break;
		case '*':	//char a의 값이 *일경우 *연산을 한다.
			result = num1 * num2;
			printf("\n %lld %c %lld = %lld \n", num1, a, num2, result);
			break;
		case '/':	//char a의 값이 /일경우 /연산을 한다.
			if (num2 != 0)
			{
				result = num1 / num2;
				printf("\n %lld / %lld = %.5lf \n", num1, num2, (long double) result);
			}
			else
				printf("\n 0으로 나누면 안됩니다\n");
			break;
		default:
			printf(" 계산할 수 없음");
			break;
		}
		//-------------------------------------------------------------------------------

		textcolor(14);
		printf("\n계속 계산기를 사용하려면 'Enter key'를 눌러주시고 \n");
		printf("앱을 종료하려면 'quit'를 입력해주세요 : ");
		textcolor(15);
		while (1)
		{
			gets_s(input, sizeof(input));

			if (strcmp(input, "") == 0)
			{
				system("cls");
				break;
			}
			else if (strcmp(input, "quit") == 0)
				return;
			else if (strcmp(input, "enter key") == 0)
			{
				textcolor(7);
				printf("누르라는 'Enter'는 안누르고, 'enter key'를 치다니... OTL ");
				textcolor(15);
			}
			else
				printf("잘못된 명령을 입력했습니다. 다시 입력해주세요. ");
		}
	}
}

/*  제작자: 대청대청 (Team Project member) */
/*  MIT License
	해당 C코드파일(.c)은 MIT License에 따라 이용할 수 있습니다. */