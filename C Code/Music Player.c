#include <stdio.h>
#include <string.h>
#include <Windows.h>	//WinAPI
#include <mmsystem.h>
#include "functionheader.h"

#pragma comment(lib, "winmm.lib")	//PlaySound �Լ� ȣ���� ���� winmm.lib ���̺귯���� �ε��մϴ�.

char musicfile[512];
char app_control[256];

// �ܼ�â ���
void PrintConsole2()
{
	textcolor(11);
	printf("\n  Lulin Laboratory's Music Player \n");
	textcolor(14);
	printf("********************************************************************************\n");
	printf("����: ���������� *.wav���ϸ� �ν��ϸ� ��������(.exe) ������ �־��ֽñ� �ٶ��ϴ�.\n");
	printf("\t���������� ���������� ��ġ�� ������ ������ ���ϸ� ��� �˴ϴ�. \n\n");
	printf("\t�ƽ��Ե� �Ͻ����� ����� ���� ������ �����մϴ�. \n");
	printf("********************************************************************************\n\n");
	textcolor(15);
}

// �÷��̾� ��Ʈ�� ����
void Commandmessage()
{
	textcolor(7);
	printf("��ɾ� ����: \n");
	printf("\t'new' ���ο� ���������� ����մϴ�. \n");
	printf("\t'stop' ������ �����մϴ�. \n");
	printf("\t'quit' ������ �����ϰ� ���� �����մϴ�. \n");
	printf("\t'force quit' ���� ����� ������ ä ���� �����մϴ�. \n\n");
	textcolor(15);
}

//------------------------------------------------------------------------
// ��ɾ� �Լ� ���
void _new()
{
	printf("�����ų ������ ��� �Ǵ� ���ϸ��� �Է����ּ���( .wav���� �Է�!!) : ");
	gets_s(musicfile, sizeof(musicfile));

	/* PlaySound �Լ��� ȣ���Ѵ�. �÷��׷δ� SND_FILENAME(ù��° �Ű������� ���ϸ����� �ν�), SND_ASYNC(�񵿱������� ���)��
	����ϸ� ���ϴ� �÷��׵��� OR�� �����Ѵ�. */
	sndPlaySoundA(musicfile, SND_FILENAME | SND_ASYNC);
}
//------------------------------------------------------------------------

int MusicPlayer(void)
{
	PrintConsole2();
	Commandmessage();

	while (1)
	{
		printf("Control ��ɾ� �Է�: ");
		gets_s(app_control, sizeof(app_control));

		if (strcmp(app_control, "") == 0)
		{
			//��ɾ� �ٽ� �Է¹���
		}
		else if (strcmp(app_control, "new") == 0)
		{
			system("cls");
			PrintConsole2();
			Commandmessage();
			_new();
			textcolor(10);
			printf("\n ��� �� ~~~ \n\n");
			textcolor(15);
		}
		else if (strcmp(app_control, "stop") == 0)
		{
			sndPlaySound(NULL, 0);
			textcolor(14);
			printf("\n ����\n\n");
			textcolor(15);
		}
		else if (strcmp(app_control, "quit") == 0)
		{
			sndPlaySound(NULL, 0);
			textcolor(14);
			printf(" ���� �����մϴ�. \n");
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
			printf("�� �� ���� ��ɾ��Դϴ�. \n\n");
	}
}

/*  ������: Lulin Pollux (Team Project member) */
/*  MIT License
	�ش� C�ڵ�����(.c)�� MIT License�� ���� �̿��� �� �ֽ��ϴ�.
	Ű���� �˰��� ��ó: http://blog.naver.com/mojigura/60050710954 */