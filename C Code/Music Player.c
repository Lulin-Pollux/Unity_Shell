#include <stdio.h>
#include <string.h>
#include <Windows.h>	//WinAPI
#include <mmsystem.h>
#include "functionheader.h"

#pragma comment(lib, "winmm.lib")	//PlaySound 함수 호출을 위한 winmm.lib 라이브러리를 로드합니다.

char musicfile[512];
char app_control[256];

// 콘솔창 출력
void PrintConsole2()
{
	textcolor(11);
	printf("\n  Lulin Laboratory's Music Player \n");
	textcolor(14);
	printf("********************************************************************************\n");
	printf("도움말: 음악파일은 *.wav파일만 인식하며 실행파일(.exe) 폴더에 넣어주시기 바랍니다.\n");
	printf("\t음악파일이 실행파일이 위치한 폴더에 있으면 파일명만 적어도 됩니다. \n\n");
	printf("\t아쉽게도 일시정지 기능이 없어 정지만 가능합니다. \n");
	printf("********************************************************************************\n\n");
	textcolor(15);
}

// 플레이어 컨트롤 설명
void Commandmessage()
{
	textcolor(7);
	printf("명령어 설명: \n");
	printf("\t'new' 새로운 음악파일을 재생합니다. \n");
	printf("\t'stop' 음악을 정지합니다. \n");
	printf("\t'quit' 음악을 정지하고 앱을 종료합니다. \n");
	printf("\t'force quit' 음악 재생을 유지한 채 앱을 종료합니다. \n\n");
	textcolor(15);
}

//------------------------------------------------------------------------
// 명령어 함수 목록
void _new()
{
	printf("재생시킬 음악의 경로 또는 파일명을 입력해주세요( .wav까지 입력!!) : ");
	gets_s(musicfile, sizeof(musicfile));

	/* PlaySound 함수를 호출한다. 플래그로는 SND_FILENAME(첫번째 매개변수를 파일명으로 인식), SND_ASYNC(비동기적으로 재생)을
	사용하며 원하는 플래그들을 OR로 연결한다. */
	sndPlaySoundA(musicfile, SND_FILENAME | SND_ASYNC);
}
//------------------------------------------------------------------------

int MusicPlayer(void)
{
	PrintConsole2();
	Commandmessage();

	while (1)
	{
		printf("Control 명령어 입력: ");
		gets_s(app_control, sizeof(app_control));

		if (strcmp(app_control, "") == 0)
		{
			//명령어 다시 입력받음
		}
		else if (strcmp(app_control, "new") == 0)
		{
			system("cls");
			PrintConsole2();
			Commandmessage();
			_new();
			textcolor(10);
			printf("\n 재생 중 ~~~ \n\n");
			textcolor(15);
		}
		else if (strcmp(app_control, "stop") == 0)
		{
			sndPlaySound(NULL, 0);
			textcolor(14);
			printf("\n 정지\n\n");
			textcolor(15);
		}
		else if (strcmp(app_control, "quit") == 0)
		{
			sndPlaySound(NULL, 0);
			textcolor(14);
			printf(" 앱을 종료합니다. \n");
			system("pause");
			textcolor(15);
			return 0;
		}
		else if (strcmp(app_control, "force quit") == 0)
		{
			return 0;
		}
		else if (strcmp(app_control, "clear") == 0)
		{
			system("cls");
			PrintConsole2();
			Commandmessage();
		}
		else
			printf("알 수 없는 명령어입니다. \n\n");
	}
}

/*  개발자: Lulin Pollux (Team Project member) */
/*  MIT License
	해당 C코드파일(.c)은 MIT License에 따라 이용할 수 있습니다.
	키보드 알고리즘 출처: http://blog.naver.com/mojigura/60050710954 */