#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <time.h>
#include <Windows.h>
#include "functionheader.h"

char terminal[1024];		// ��ɾ� �ִ� ����: 1023��

char exe_directory[512];		// ���� ���丮 ���� �迭
char directory[512];			// �͹̳� ���丮 ��¿� ����ϴ� �迭
char recent_directory[512];		// ���� �ֱٿ� �̵��ߴ� ���丮 ����

char developername[16];		// ������ �̸�

//--------------------------------------------------------
// �͹̳� ���� �Լ� ���
void Initializing()
{
	system("title Unity Shell");				//CMD ����
	system("mode con cols=110 lines=45");			// ���� 110, ���� 40

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);	//�ڵ尡 �� �ڵ��� ������ ����
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);		//�ܼ�â ȭ�� �������� �޾ƿ�
	COORD new_size =
	{
		info.srWindow.Right + 1,
		info.srWindow.Bottom + 5000
	};
	SetConsoleScreenBufferSize(handle, new_size);		//�ܼ�â ȭ�� ���� ũ�� ����
}

void AppLoadingMessage()
{
	system("cls");
	textcolor(14);
	printf("\n");
	printf("������: %s \n", developername);
	printf("�ش� ���� ���״� �����ڿ��� �����ϼ���. \n");
	textcolor(15);
	system("pause");
	system("cls");
}

void AppClosedMessage()
{
	textcolor(14);
	printf("App�� ����Ǿ����ϴ�. \n\n");
	textcolor(15);
}

void AppExecution()
{
	if (strcmp(terminal, "exec ascii art maker") == 0)
	{
		strcpy_s(developername, sizeof(developername), "Lulin Pollux");
		AppLoadingMessage();
		_chdir(exe_directory);	//�� �ۿ����� ���̴� �Լ�
		ASCIIArtMaker();
		system("pause");	//�� �ۿ����� ���̴� �Լ�

		Initializing();
		AppClosedMessage();
	}
	else if (strcmp(terminal, "exec calculator") == 0)
	{
		strcpy_s(developername, sizeof(developername), "��û��û");
		AppLoadingMessage();
		Calculator();

		Initializing();
		AppClosedMessage();
	}
	else if (strcmp(terminal, "exec keyboard") == 0)
	{
		strcpy_s(developername, sizeof(developername), "Lulin Pollux");
		AppLoadingMessage();
		Keyboard();

		Initializing();
		AppClosedMessage();
	}
	else if (strcmp(terminal, "exec ladder game") == 0)
	{
		strcpy_s(developername, sizeof(developername), "������");
		AppLoadingMessage();
		LadderGame();

		Initializing();
		AppClosedMessage();
	}
	else if (strcmp(terminal, "exec music player") == 0)
	{
		strcpy_s(developername, sizeof(developername), "Lulin Pollux");
		AppLoadingMessage();
		MusicPlayer();

		Initializing();
		AppClosedMessage();
	}
	else if (strcmp(terminal, "exec puzzle game") == 0)
	{
		strcpy_s(developername, sizeof(developername), "������");
		AppLoadingMessage();
		PuzzleGame();

		Initializing();
		AppClosedMessage();
	}
	else
		printf("�ش� ������ App�� �������� �ʽ��ϴ�. \n\n");
}
//--------------------------------------------------------

//--------------------------------------------------------
// ��ɾ� �Լ� ���
void app_list()
{
	printf("App ���: \n");
	printf("\t 1. ASCII Art Maker \n");
	printf("\t 2. Calculator \n");
	printf("\t 3. Keyboard \n");
	printf("\t 4. Ladder Game \n");
	printf("\t 5. Music Player \n");
	printf("\t 6. Puzzle Game \n\n");
}

void app_disc()
{
	textcolor(14);
	printf("�ڼ��� ������ �ʿ��ϴٸ� ÷�ε� �Ŵ����� �о����. (App_����.txt) \n\n");
	textcolor(15);
	printf(" 1. ASCII Art Maker: ����Ʈ���������� �ƽ�Ű ��Ʈ�� �׷��ݴϴ�. \n");
	printf(" 2. Calculator: ��Ģ���� ���� \n");
	printf(" 3. Keyboard: �ǾƳ� �ǹ� ����Ʈ���� \n");
	printf(" 4. Ladder Game: ��ٸ� ����\n");
	printf(" 5. Music Player: ���� �÷��̾� \n");
	printf(" 6. Puzzle Game: ���� ���߱� ���� \n");
}

void cd(char* s)
{
	_chdir(s);
}

void date()
{
	struct tm local;
	time_t now;
	char buf[256];
	time(&now);

	localtime_s(&local, &now);
	asctime_s(buf, sizeof(buf), &local);
	printf(" %s", buf);
}

void frontpage()
{
	textcolor(7);
	printf("Unity Shell ������: Lulin Pollux \n");
	printf("2017 Team Project. Copyright(c) \n\n");

	textcolor(14);
	printf(" 'help'�� �Է��ϸ� ��ɾ Ȯ���� �� �ֽ��ϴ�. \n");
	app_list();
	textcolor(15);
}

void help()
{
	printf("GNU bash CUSTOM, version 2.1.01(1) - relase (x86_64-pc-linux-gnu) \n");
	printf("These shell commands are defined internally. Type 'help' to see this list. \n");
	printf("�ڼ��� ������ ÷�ε� �Ŵ����� �о����. (Command.txt) \n\n");

	printf("A star (*) next to a name means that the command is disabled. \n\n");

	puts("��/�� \t\t ������(��) / ������(��) �Է��ߴ� ��ɾ�");
	puts("app \t\t ���ø����̼��� ������ ����մϴ�. -Custom ��ɾ�-");
	puts("clear \t\t �͹̳� ������ ��� ����ϴ�.");
	puts("cd \t\t directory ����");
	puts("date \t\t ���� ��¥�� �ð��� ǥ���մϴ�.");
	puts("easymode \t ������带 �����մϴ�. -Custom ��ɾ�-");
	puts("exec \t\t ���ø����̼��� �����մϴ�.");
	puts("exit \t\t �͹̳��� �����մϴ�.");
	puts("frontpage \t ó�� �͹̳��� ��������� ���� ���� ȭ���� ����մϴ�. -Custom ��ɾ�-");
	puts("ifconfig \t ��ǻ���� IP������ ǥ���մϴ�.");
	puts("ls \t\t ���� ��ġ�� directory�� ���ϰ� ���� directory ��� ���");
	puts("ping \t\t Ping�� �����մϴ�.");
	puts("pwd \t\t ���� directory�� ����մϴ�.");
	puts("ver \t\t ����Ʈ���� ������ ǥ���մϴ�. -Custom ��ɾ�- \n");
}

void pwd()
{
	char pwd[512];

	_getcwd(pwd, sizeof(pwd));
	printf("%s\n\n", pwd);
}
//--------------------------------------------------------

//--------------------------------------------------------
// ����� ��� ���� �Լ� ���
int UserModeSelect()
{
	/* ��� ����ȭ�� ����*/
	/*-----------------------------------------------------------------------------------------*/
	system("title Unity Shell");				//CMD ����
	system("mode con cols=90 lines=30");			// ���� 90, ���� 30

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);	//�ڵ尡 �� �ڵ��� ������ ����
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);		//�ܼ�â ȭ�� �������� �޾ƿ�
	COORD new_size =
	{
		info.srWindow.Right + 1,
		info.srWindow.Bottom + 500
	};
	SetConsoleScreenBufferSize(handle, new_size);		//�ܼ�â ȭ�� ���� ũ�� ����
	/*-----------------------------------------------------------------------------------------*/
	int input;

	puts("");
	textcolor(11);
	puts("*-- ����� ��带 �������ּ���. ------*");
	puts("|                                     |");
	puts("|     1. ������� (�������� ����)     |");
	puts("|     2. ǥ�ظ��                     |");
	puts("*-------------------------------------*");
	textcolor(15);

	printf("\n��ȣ �Է� >>> ");

	//-----------------------------------------------------
	// ����� �Է��� �޴� �ڵ�
	while (1)
	{
		scanf_s("%d", &input);
		clearInputBuffer();

		if ((input >= 1) && (input <= 2))
			break;
		else
			printf("�ٽ� �Է����ּ���: ");
	}
	//-----------------------------------------------------

	switch (input)
	{
	case 1:
		return 1;
	case 2:
		return 2;
	}
	return 0;
}

int EasyMode()
{
	/* ������� ���� */
	/*-------------------------------------------------------------------*/
	system("cls");
	textcolor(14);
	printf("\n");
	printf("����: �������� �� ���� �� ���Ḹ �����մϴ�. \n");
	printf("	Shell ���� �۾��� ǥ�ظ�忡�� �� �� �ֽ��ϴ�. \n\n");
	textcolor(15);
	system("pause");
	Initializing();	// ȭ�� ũ�� ����
	printf("\n");
	/*-------------------------------------------------------------------*/

	/* Easy Mode */
	/*-------------------------------------------------------------------*/
	int input1;	// ������忡�� ���

	while (1)
	{
		textcolor(14);
		puts("*-- Easy Mode ------------------------*");
		puts("|                                     |");
		puts("|     1. �� ����                      |");
		puts("|     2. ǥ�ظ��� �����ϱ�          |");
		puts("|     3. ���α׷� ����                |");
		puts("*-------------------------------------*");
		textcolor(15);

		printf("\n��ȣ �Է� >>> ");

		//-----------------------------------------------------
		// ����� �Է��� �޴� �ڵ�
		while (1)
		{
			scanf_s("%d", &input1);
			clearInputBuffer();

			if ((input1 >= 1) && (input1 <= 3))
				break;
			else
				printf("�ٽ� �Է����ּ���: ");
		}
		//-----------------------------------------------------

		switch (input1)
		{
		case 1:
		{
			system("cls");
			printf("\n");
			app_list();
			textcolor(14);
			printf("�����ϰ� ���� ���� ��ȣ�� �Է����ּ���. \n");
			textcolor(15);

			while (1)
			{
				printf(">>> ");
				scanf_s("%d", &input1);
				clearInputBuffer();

				if (input1 == 1)
				{
					strcpy_s(terminal, sizeof(terminal), "exec ascii art maker");
					AppExecution();
					break;
				}
				else if (input1 == 2)
				{
					strcpy_s(terminal, sizeof(terminal), "exec calculator");
					AppExecution();
					break;
				}
				else if (input1 == 3)
				{
					strcpy_s(terminal, sizeof(terminal), "exec keyboard");
					AppExecution();
					break;
				}
				else if (input1 == 4)
				{
					strcpy_s(terminal, sizeof(terminal), "exec ladder game");
					AppExecution();
					break;
				}
				else if (input1 == 5)
				{
					strcpy_s(terminal, sizeof(terminal), "exec music player");
					AppExecution();
					break;
				}
				else if (input1 == 6)
				{
					strcpy_s(terminal, sizeof(terminal), "exec puzzle game");
					AppExecution();
					break;
				}
				else
					printf("\n�ش� ��ȣ�� ���� �������� �ʽ��ϴ�. \n");
			}
			break;
		}
		case 2:
			return 2;
		case 3:
			return 3;
		}
	}
	/*-------------------------------------------------------------------*/
}
//--------------------------------------------------------

int main(int argc, char* argv[])
{
	/* �̽��� ���� ���� ���� Ȯ�� */
	/*----------------------------------------------------------------------*/
	const char *check[12] = { "-stillalive" };	//���� �Ű����� Ȯ��
	//�Ķ���� ���� ������ �̽��� ���� ����
	if ((argc == 2) && (strcmp(*check, argv[1]) == 0))
	{
		stillalive();
		return 0;
	}
	/*----------------------------------------------------------------------*/

	/* ����� ��� ���� */
	/*----------------------------------------------------------------------*/
	short mode_select;
	short easymode_input = 0;

	mode_select = UserModeSelect();

	if (mode_select == 1)
		easymode_input = EasyMode();
	else if (mode_select == 0)
	{
		textcolor(12);
		printf("������ �����߻�!! \n");
		textcolor(14);
		printf("���α׷��� �����մϴ�. \n");
		textcolor(15);
		system("pause");
		return 0;
	}

	if (easymode_input == 3)
	{
		textcolor(14);
		printf("\n���α׷��� �����մϴ�. \n\n");
		textcolor(15);
		system("pause");
		return 0;
	}
	/*----------------------------------------------------------------------*/

	/* �� �ʱ⼳�� �ϴ� �� */
	/*---------------------------------------------------------------------------------------------*/
	Initializing();		//�͹̳� �ʱ⼳��
	frontpage();		//���� �޽��� ǥ��
	_getcwd(exe_directory, sizeof(exe_directory));		//exe ������ ���丮�� �����صд�.
	strcpy_s(directory, sizeof(directory), exe_directory);		//directory ������ �����Ѵ�.
	/*---------------------------------------------------------------------------------------------*/

	while (1)
	{
		_getcwd(directory, sizeof(directory));	//���� ������ ���丮 Ȯ��
		
		/* ���丮 ǥ�� �ڵ� */
		//-----------------------------------------------------------------------
			// *.exe ������ �ִ� ��ο� ���� ������ ��ΰ� ������...
		if (strcmp(directory, exe_directory) == 0)
		{
			directory[0] = '~';		// ~ ǥ�ø� ��
			directory[1] = '\0';	// 'NULL'���� ����
		}

		textcolor(10);
		printf("ubuntu@lulin:");		//��ǻ�� �̸�@����� �̸�:
		textcolor(11);
		printf("%s", directory);		//������
		textcolor(15);
		printf("$ ");					//����
		//-----------------------------------------------------------------------

		gets_s(terminal, sizeof(terminal));		//��ɾ� �Է�

		/* ��ɾ� �б� ����. ��ɾ�� abc������ �ۼ��Ѵ�. */
		/*-------------------------------------------------------------------------------------*/
		if (strcmp(terminal, "") == 0)
		{
			//�ٽ� �Է��� �޴´�.
		}
		else if (strncmp(terminal, "app", 3) == 0)
		{
			if (strcmp(terminal, "app") == 0)
			{
				app_list();
			}
			else if (strcmp(terminal, "app -disc") == 0)
			{
				app_disc();
			}
			else if (strcmp(terminal, "app -list") == 0)
			{
				app_list();
			}
			else
				printf("�ش� �ɼ��� �������� �ʽ��ϴ�. \n\n");
		}

		else if (strcmp(terminal, "clear") == 0)
		{
			system("cls");
		}

		else if (strncmp(terminal, "cd", 2) == 0)		//���丮 ����
		{
			if (strcmp(terminal, "cd") == 0)
			{
				//�ٽ� ��ɾ� �Է¹���
			}
			else if (strcmp(terminal, "cd ~") == 0)		//exe ���丮�� ����
			{
				_chdir(exe_directory);
			}
			else if (strcmp(terminal, "cd -") == 0)		//���� ���丮�� ����
			{
				_chdir(recent_directory);
			}
			else
			{
				_getcwd(recent_directory, sizeof(recent_directory));
				char temp[1024];
				strcpy_s(temp, sizeof(terminal) - 3, &terminal[3]);
				cd(temp);
			}
		}

		else if (strcmp(terminal, "date") == 0)
		{
			date();
		}

		else if (strcmp(terminal, "easymode") == 0)
		{
			// ������� ����
			easymode_input = EasyMode();
			// ���� ǥ�ظ��� �����ϱ⸦ ����������...
			if (easymode_input == 2)
			{
				system("cls");
				frontpage();
			}
			// ���� ���α׷� ���Ḧ ����������...
			else if (easymode_input == 3)
			{
				textcolor(14);
				printf("\n���α׷��� �����մϴ�. \n\n");
				textcolor(15);
				system("pause");
				return 0;
			}
		}

		else if (strncmp(terminal, "exec", 4) == 0)
		{
			if (strcmp(terminal, "exec") == 0)
			{
				printf("�����Ű�� ���� App�� �̸��� �Է����ּ���. \n");
				textcolor(14);
				printf("����: Command������ App �̸��� �빮�ڸ� �ν����� �ʽ��ϴ�. \n");
				textcolor(15);
				printf("Ex) exec ascii art maker, ladder game. . . \n");
				printf("\n");
			}
			else
			{
				AppExecution();
			}
		}

		else if (strcmp(terminal, "exit") == 0)
		{
			return 0;		//���α׷� ����
		}

		else if (strcmp(terminal, "help") == 0)
		{
			help();		//���� �ҷ�����
		}

		else if (strcmp(terminal, "ifconfig") == 0)
		{
			system("ipconfig");
		}

		else if (strcmp(terminal, "ifconfig -a") == 0)
		{
			system("ipconfig /all");
		}

		else if (strcmp(terminal, "ls") == 0)
		{
			system("dir");		//���� ���丮�� ���ϰ� ���� ���丮 ��� ������
		}

		else if (strncmp(terminal, "ping", 4) == 0)
		{
			if (strcmp(terminal, "ping") == 0)
			{
				printf("IP�ּҳ� Domain Name�� �Է����ּ���.\n");
			}
			else
			{
				system(terminal);
				printf("\n");
			}
		}

		else if (strcmp(terminal, "pwd") == 0)
		{
			pwd();		//exe���� ��� �ҷ�����
		}

		else if (strcmp(terminal, "frontpage") == 0)
		{
			system("cls");
			frontpage();		//����ȭ�� �ҷ�����
		}

		else if (strcmp(terminal, "ver") == 0)
		{
			printf("\n");
			printf("Lulin Laboratory's Unity Shell [Version 2.1.01] \n");
			printf("\n");
		}

		else if (strcmp(terminal, "vi") == 0)
		{
			printf("Sorry, vi editer has been disabled... \n");		//vi ������ ��Ȱ��ȭ
		}

		else	// ��ɾ� ��Ͽ� ���� �Է� �� �˸�
			printf("%s: command not found \n", terminal);
		/*-------------------------------------------------------------------------------------*/
	}
}

/*  ������: Lulin Pollux (Team Project member) */
/*  MIT License
	�ش� C�ڵ�����(.c)�� MIT License�� ���� �̿��� �� �ֽ��ϴ�. */