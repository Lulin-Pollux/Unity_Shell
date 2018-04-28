#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <time.h>
#include <Windows.h>
#include "functionheader.h"

char terminal[1024];		// 명령어 최대 길이: 1023자

char exe_directory[512];		// 현재 디렉토리 저장 배열
char directory[512];			// 터미널 디렉토리 출력에 사용하는 배열
char recent_directory[512];		// 가장 최근에 이동했던 디렉토리 저장

char developername[16];		// 개발자 이름

//--------------------------------------------------------
// 터미널 관련 함수 목록
void Initializing()
{
	system("title Unity Shell");				//CMD 제목
	system("mode con cols=110 lines=45");			// 가로 110, 세로 40

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);	//코드가 길어서 핸들을 밖으로 빼줌
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);		//콘솔창 화면 버퍼정보 받아옴
	COORD new_size =
	{
		info.srWindow.Right + 1,
		info.srWindow.Bottom + 5000
	};
	SetConsoleScreenBufferSize(handle, new_size);		//콘솔창 화면 버퍼 크기 지정
}

void AppLoadingMessage()
{
	system("cls");
	textcolor(14);
	printf("\n");
	printf("개발자: %s \n", developername);
	printf("해당 앱의 버그는 개발자에게 문의하세요. \n");
	textcolor(15);
	system("pause");
	system("cls");
}

void AppClosedMessage()
{
	textcolor(14);
	printf("App이 종료되었습니다. \n\n");
	textcolor(15);
}

void AppExecution()
{
	if (strcmp(terminal, "exec ascii art maker") == 0)
	{
		strcpy_s(developername, sizeof(developername), "Lulin Pollux");
		AppLoadingMessage();
		_chdir(exe_directory);	//이 앱에서만 쓰이는 함수
		ASCIIArtMaker();
		system("pause");	//이 앱에서만 쓰이는 함수

		Initializing();
		AppClosedMessage();
	}
	else if (strcmp(terminal, "exec calculator") == 0)
	{
		strcpy_s(developername, sizeof(developername), "대청대청");
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
		strcpy_s(developername, sizeof(developername), "오광준");
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
		strcpy_s(developername, sizeof(developername), "이찬휘");
		AppLoadingMessage();
		PuzzleGame();

		Initializing();
		AppClosedMessage();
	}
	else
		printf("해당 제목의 App은 존재하지 않습니다. \n\n");
}
//--------------------------------------------------------

//--------------------------------------------------------
// 명령어 함수 목록
void app_list()
{
	printf("App 목록: \n");
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
	printf("자세한 설명이 필요하다면 첨부된 매뉴얼을 읽어보세요. (App_설명.txt) \n\n");
	textcolor(15);
	printf(" 1. ASCII Art Maker: 소프트웨어적으로 아스키 아트를 그려줍니다. \n");
	printf(" 2. Calculator: 사칙연산 계산기 \n");
	printf(" 3. Keyboard: 피아노 건반 소프트웨어 \n");
	printf(" 4. Ladder Game: 사다리 게임\n");
	printf(" 5. Music Player: 음악 플레이어 \n");
	printf(" 6. Puzzle Game: 퍼즐 맞추기 게임 \n");
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
	printf("Unity Shell 개발자: Lulin Pollux \n");
	printf("2017 Team Project. Copyright(c) \n\n");

	textcolor(14);
	printf(" 'help'를 입력하면 명령어를 확인할 수 있습니다. \n");
	app_list();
	textcolor(15);
}

void help()
{
	printf("GNU bash CUSTOM, version 2.1.01(1) - relase (x86_64-pc-linux-gnu) \n");
	printf("These shell commands are defined internally. Type 'help' to see this list. \n");
	printf("자세한 설명은 첨부된 매뉴얼을 읽어보세요. (Command.txt) \n\n");

	printf("A star (*) next to a name means that the command is disabled. \n\n");

	puts("↑/↓ \t\t 이전에(↑) / 다음에(↓) 입력했던 명령어");
	puts("app \t\t 애플리케이션의 정보를 출력합니다. -Custom 명령어-");
	puts("clear \t\t 터미널 내용을 모두 지웁니다.");
	puts("cd \t\t directory 변경");
	puts("date \t\t 현재 날짜와 시각을 표시합니다.");
	puts("easymode \t 이지모드를 실행합니다. -Custom 명령어-");
	puts("exec \t\t 애플리케이션을 실행합니다.");
	puts("exit \t\t 터미널을 종료합니다.");
	puts("frontpage \t 처음 터미널을 실행시켰을 때와 같은 화면을 출력합니다. -Custom 명령어-");
	puts("ifconfig \t 컴퓨터의 IP정보를 표시합니다.");
	puts("ls \t\t 현재 위치한 directory의 파일과 하위 directory 목록 출력");
	puts("ping \t\t Ping을 수행합니다.");
	puts("pwd \t\t 현재 directory를 출력합니다.");
	puts("ver \t\t 소프트웨어 버전을 표시합니다. -Custom 명령어- \n");
}

void pwd()
{
	char pwd[512];

	_getcwd(pwd, sizeof(pwd));
	printf("%s\n\n", pwd);
}
//--------------------------------------------------------

//--------------------------------------------------------
// 사용자 모드 관련 함수 목록
int UserModeSelect()
{
	/* 모드 지정화면 설정*/
	/*-----------------------------------------------------------------------------------------*/
	system("title Unity Shell");				//CMD 제목
	system("mode con cols=90 lines=30");			// 가로 90, 세로 30

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);	//코드가 길어서 핸들을 밖으로 빼줌
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);		//콘솔창 화면 버퍼정보 받아옴
	COORD new_size =
	{
		info.srWindow.Right + 1,
		info.srWindow.Bottom + 500
	};
	SetConsoleScreenBufferSize(handle, new_size);		//콘솔창 화면 버퍼 크기 지정
	/*-----------------------------------------------------------------------------------------*/
	int input;

	puts("");
	textcolor(11);
	puts("*-- 사용자 모드를 선택해주세요. ------*");
	puts("|                                     |");
	puts("|     1. 이지모드 (비전공자 전용)     |");
	puts("|     2. 표준모드                     |");
	puts("*-------------------------------------*");
	textcolor(15);

	printf("\n번호 입력 >>> ");

	//-----------------------------------------------------
	// 사용자 입력을 받는 코드
	while (1)
	{
		scanf_s("%d", &input);
		clearInputBuffer();

		if ((input >= 1) && (input <= 2))
			break;
		else
			printf("다시 입력해주세요: ");
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
	/* 이지모드 설명 */
	/*-------------------------------------------------------------------*/
	system("cls");
	textcolor(14);
	printf("\n");
	printf("도움말: 이지모드는 앱 실행 및 종료만 가능합니다. \n");
	printf("	Shell 관련 작업은 표준모드에서 할 수 있습니다. \n\n");
	textcolor(15);
	system("pause");
	Initializing();	// 화면 크기 조정
	printf("\n");
	/*-------------------------------------------------------------------*/

	/* Easy Mode */
	/*-------------------------------------------------------------------*/
	int input1;	// 이지모드에서 사용

	while (1)
	{
		textcolor(14);
		puts("*-- Easy Mode ------------------------*");
		puts("|                                     |");
		puts("|     1. 앱 실행                      |");
		puts("|     2. 표준모드로 변경하기          |");
		puts("|     3. 프로그램 종료                |");
		puts("*-------------------------------------*");
		textcolor(15);

		printf("\n번호 입력 >>> ");

		//-----------------------------------------------------
		// 사용자 입력을 받는 코드
		while (1)
		{
			scanf_s("%d", &input1);
			clearInputBuffer();

			if ((input1 >= 1) && (input1 <= 3))
				break;
			else
				printf("다시 입력해주세요: ");
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
			printf("실행하고 싶은 앱의 번호를 입력해주세요. \n");
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
					printf("\n해당 번호의 앱이 존재하지 않습니다. \n");
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
	/* 이스터 에그 실행 여부 확인 */
	/*----------------------------------------------------------------------*/
	const char *check[12] = { "-stillalive" };	//실행 매개변수 확인
	//파라미터 조건 만족시 이스터 에그 실행
	if ((argc == 2) && (strcmp(*check, argv[1]) == 0))
	{
		stillalive();
		return 0;
	}
	/*----------------------------------------------------------------------*/

	/* 사용자 모드 선택 */
	/*----------------------------------------------------------------------*/
	short mode_select;
	short easymode_input = 0;

	mode_select = UserModeSelect();

	if (mode_select == 1)
		easymode_input = EasyMode();
	else if (mode_select == 0)
	{
		textcolor(12);
		printf("잠재적 오류발생!! \n");
		textcolor(14);
		printf("프로그램을 종료합니다. \n");
		textcolor(15);
		system("pause");
		return 0;
	}

	if (easymode_input == 3)
	{
		textcolor(14);
		printf("\n프로그램을 종료합니다. \n\n");
		textcolor(15);
		system("pause");
		return 0;
	}
	/*----------------------------------------------------------------------*/

	/* 쉘 초기설정 하는 중 */
	/*---------------------------------------------------------------------------------------------*/
	Initializing();		//터미널 초기설정
	frontpage();		//시작 메시지 표시
	_getcwd(exe_directory, sizeof(exe_directory));		//exe 파일의 디렉토리를 저장해둔다.
	strcpy_s(directory, sizeof(directory), exe_directory);		//directory 변수에 복사한다.
	/*---------------------------------------------------------------------------------------------*/

	while (1)
	{
		_getcwd(directory, sizeof(directory));	//현재 설정된 디렉토리 확인
		
		/* 디렉토리 표시 코드 */
		//-----------------------------------------------------------------------
			// *.exe 파일이 있는 경로와 현재 설정된 경로가 같으면...
		if (strcmp(directory, exe_directory) == 0)
		{
			directory[0] = '~';		// ~ 표시를 함
			directory[1] = '\0';	// 'NULL'문자 삽입
		}

		textcolor(10);
		printf("ubuntu@lulin:");		//컴퓨터 이름@사용자 이름:
		textcolor(11);
		printf("%s", directory);		//현재경로
		textcolor(15);
		printf("$ ");					//권한
		//-----------------------------------------------------------------------

		gets_s(terminal, sizeof(terminal));		//명령어 입력

		/* 명령어 분기 시작. 명령어는 abc순으로 작성한다. */
		/*-------------------------------------------------------------------------------------*/
		if (strcmp(terminal, "") == 0)
		{
			//다시 입력을 받는다.
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
				printf("해당 옵션은 존재하지 않습니다. \n\n");
		}

		else if (strcmp(terminal, "clear") == 0)
		{
			system("cls");
		}

		else if (strncmp(terminal, "cd", 2) == 0)		//디렉토리 변경
		{
			if (strcmp(terminal, "cd") == 0)
			{
				//다시 명령어 입력받음
			}
			else if (strcmp(terminal, "cd ~") == 0)		//exe 디렉토리로 변경
			{
				_chdir(exe_directory);
			}
			else if (strcmp(terminal, "cd -") == 0)		//이전 디렉토리로 변경
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
			// 이지모드 실행
			easymode_input = EasyMode();
			// 만약 표준모드로 변경하기를 선택했으면...
			if (easymode_input == 2)
			{
				system("cls");
				frontpage();
			}
			// 만약 프로그램 종료를 선택했으면...
			else if (easymode_input == 3)
			{
				textcolor(14);
				printf("\n프로그램을 종료합니다. \n\n");
				textcolor(15);
				system("pause");
				return 0;
			}
		}

		else if (strncmp(terminal, "exec", 4) == 0)
		{
			if (strcmp(terminal, "exec") == 0)
			{
				printf("실행시키고 싶은 App의 이름을 입력해주세요. \n");
				textcolor(14);
				printf("주의: Command에서의 App 이름은 대문자를 인식하지 않습니다. \n");
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
			return 0;		//프로그램 종료
		}

		else if (strcmp(terminal, "help") == 0)
		{
			help();		//도움말 불러오기
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
			system("dir");		//현재 디렉토리의 파일과 하위 디렉토리 목록 보여줌
		}

		else if (strncmp(terminal, "ping", 4) == 0)
		{
			if (strcmp(terminal, "ping") == 0)
			{
				printf("IP주소나 Domain Name을 입력해주세요.\n");
			}
			else
			{
				system(terminal);
				printf("\n");
			}
		}

		else if (strcmp(terminal, "pwd") == 0)
		{
			pwd();		//exe파일 경로 불러오기
		}

		else if (strcmp(terminal, "frontpage") == 0)
		{
			system("cls");
			frontpage();		//시작화면 불러오기
		}

		else if (strcmp(terminal, "ver") == 0)
		{
			printf("\n");
			printf("Lulin Laboratory's Unity Shell [Version 2.1.01] \n");
			printf("\n");
		}

		else if (strcmp(terminal, "vi") == 0)
		{
			printf("Sorry, vi editer has been disabled... \n");		//vi 편집기 비활성화
		}

		else	// 명령어 목록에 없는 입력 시 알림
			printf("%s: command not found \n", terminal);
		/*-------------------------------------------------------------------------------------*/
	}
}

/*  제작자: Lulin Pollux (Team Project member) */
/*  MIT License
	해당 C코드파일(.c)은 MIT License에 따라 이용할 수 있습니다. */