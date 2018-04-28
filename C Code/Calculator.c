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
		printf("\n������ �Է��ϼ���: ");
		textcolor(15);
		scanf_s("%lld %c %lld", &num1, &a, 1, &num2);
		clearInputBuffer();

		switch (a)	//char a�� ���� ���� case�� ����
		{
		case '+':	//char a�� ���� +�ϰ�� +������ �Ѵ�.
			result = num1 + num2;
			printf("\n %lld %c %lld = %lld \n", num1, a, num2, result);
			break;
		case '-':	//char a�� ���� -�ϰ�� -������ �Ѵ�.
			result = num1 - num2;
			printf("\n %lld %c %lld = %lld \n", num1, a, num2, result);
			break;
		case '*':	//char a�� ���� *�ϰ�� *������ �Ѵ�.
			result = num1 * num2;
			printf("\n %lld %c %lld = %lld \n", num1, a, num2, result);
			break;
		case '/':	//char a�� ���� /�ϰ�� /������ �Ѵ�.
			if (num2 != 0)
			{
				result = num1 / num2;
				printf("\n %lld / %lld = %.5lf \n", num1, num2, (long double) result);
			}
			else
				printf("\n 0���� ������ �ȵ˴ϴ�\n");
			break;
		default:
			printf(" ����� �� ����");
			break;
		}
		//-------------------------------------------------------------------------------

		textcolor(14);
		printf("\n��� ���⸦ ����Ϸ��� 'Enter key'�� �����ֽð� \n");
		printf("���� �����Ϸ��� 'quit'�� �Է����ּ��� : ");
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
				printf("������� 'Enter'�� �ȴ�����, 'enter key'�� ġ�ٴ�... OTL ");
				textcolor(15);
			}
			else
				printf("�߸��� ����� �Է��߽��ϴ�. �ٽ� �Է����ּ���. ");
		}
	}
}

/*  ������: ��û��û (Team Project member) */
/*  MIT License
	�ش� C�ڵ�����(.c)�� MIT License�� ���� �̿��� �� �ֽ��ϴ�. */