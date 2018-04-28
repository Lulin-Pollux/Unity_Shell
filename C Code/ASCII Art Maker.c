#define _CRT_SECURE_NO_WARNINGS    // fopen 보안 경고로 인한 컴파일 에러 방지
#include <stdio.h>    // fopen, fread, fseek, fprintf, fclose 함수가 선언된 헤더 파일
#include <stdlib.h>   // malloc, free 함수가 선언된 헤더 파일
#include <string.h>   // gets_s, puts 함수가 선언된 헤더 파일
#include "functionheader.h"

#define PIXEL_SIZE   3    // 픽셀 한 개의 크기 3바이트(24비트)
#define PIXEL_ALIGN  4    // 픽셀 데이터 가로 한 줄은 4의 배수 크기로 저장됨

#pragma pack(push, 1)                // 구조체를 1바이트 크기로 정렬

typedef struct _BITMAPFILEHEADER     // BMP 비트맵 파일 헤더 구조체
{
	unsigned short bfType;           // BMP 파일 매직 넘버
	unsigned int   bfSize;           // 파일 크기
	unsigned short bfReserved1;      // 예약
	unsigned short bfReserved2;      // 예약
	unsigned int   bfOffBits;        // 비트맵 데이터의 시작 위치
} BITMAPFILEHEADER;

typedef struct _BITMAPINFOHEADER     // BMP 비트맵 정보 헤더 구조체(DIB 헤더)
{
	unsigned int   biSize;           // 현재 구조체의 크기
	int            biWidth;          // 비트맵 이미지의 가로 크기
	int            biHeight;         // 비트맵 이미지의 세로 크기
	unsigned short biPlanes;         // 사용하는 색상판의 수
	unsigned short biBitCount;       // 픽셀 하나를 표현하는 비트 수
	unsigned int   biCompression;    // 압축 방식
	unsigned int   biSizeImage;      // 비트맵 이미지의 픽셀 데이터 크기
	int            biXPelsPerMeter;  // 그림의 가로 해상도(미터당 픽셀)
	int            biYPelsPerMeter;  // 그림의 세로 해상도(미터당 픽셀)
	unsigned int   biClrUsed;        // 색상 테이블에서 실제 사용되는 색상 수
	unsigned int   biClrImportant;   // 비트맵을 표현하기 위해 필요한 색상 인덱스 수
} BITMAPINFOHEADER;

typedef struct _RGBTRIPLE            // 24비트 비트맵 이미지의 픽셀 구조체
{
	unsigned char rgbtBlue;          // 파랑
	unsigned char rgbtGreen;         // 초록
	unsigned char rgbtRed;           // 빨강
} RGBTRIPLE;

#pragma pack(pop)

char directory[512];		//디렉토리 전역변수 선언

int AskToStart()
{
	char input = '0';

	textcolor(14);
	printf("\n아스키 아트 제작 프로그램 도움말: \n");
	printf("제작을 원하는 비트맵 이미지 파일은 가급적 exe파일이 위치한 폴더에 넣어주시기 바랍니다. \n");
	textcolor(15);
	printf("제작을 시작하겠습니까? Y/N : ");
	while (1)
	{
		scanf_s("%c", &input, 1);
		clearInputBuffer();

		if ((input == 'y') || (input == 'Y'))
			break;		//프로그램 시작
		else if ((input == 'n') || (input == 'N'))
		{
			textcolor(12);
			printf("\n제작을 중단하였습니다. \n");
			textcolor(14);
			printf("앱을 종료합니다. \n\n");
			textcolor(15);
			return 0;		//프로그램 종료
		}
		else
			printf("잘못된 값을 입력했습니다. 다시 입력해주세요. : ");
	}
	return 1;
}

void SetDirectory()
{
	textcolor(11);
	printf("\nexe파일이 있는 경로: ");
	pwd();			//exe파일 디렉토리 출력
	textcolor(15);
	printf("Tip: 파일명만 입력하면 ");
	textcolor(11);
	printf("위의 경로");
	textcolor(15);
	printf("에 image가 있는것으로 인식합니다. Ex) picture.bmp \n");
	textcolor(12);
	printf("     앱을 강제 종료하고 싶다면 'force quit'를 입력해주세요. \n");
	textcolor(15);
	printf("제작할 image의 경로 또는 파일이름를 입력해주세요 (반드시 .bmp까지 입력!!) \n");
}

int ASCIIArtMaker()
{
	short i;
	i = AskToStart();
	if (i == 0)
		return 0;

	// 변수와 포인터 선언
	//-------------------------------------------------------------------------------------------------
		FILE *fpBmp;                    // 비트맵 파일 포인터
		FILE *fpTxt;                    // 텍스트 파일 포인터
		BITMAPFILEHEADER fileHeader;    // 비트맵 파일 헤더 구조체 변수
		BITMAPINFOHEADER infoHeader;    // 비트맵 정보 헤더 구조체 변수

		unsigned char *image;    // 픽셀 데이터 포인터
		int size;                // 픽셀 데이터 크기
		int width, height;       // 비트맵 이미지의 가로, 세로 크기
		int padding;             // 픽셀 데이터의 가로 크기가 4의 배수가 아닐 때 남는 공간의 크기

								 // 각 픽셀을 표현할 ASCII 문자. 인덱스가 높을 수록 밝아지는 것을 표현
		char ascii[] = { '#', '#', '@', '%', '=', '+', '*', ':', '-', '.', ' ' };   // 11개
	//-------------------------------------------------------------------------------------------------

		SetDirectory();
		while (1)
		{
		printf(">>> ");
		gets_s(directory, sizeof(directory));

		if (strcmp(directory, "force quit") == 0)		//앱 강제종료
		{
			textcolor(12);
			printf("\n앱이 강제 종료되었습니다. \n");
			textcolor(15);
			return 0;
		}

		fpBmp = fopen(directory, "rb");    // 비트맵 파일을 바이너리 모드로 열기
		if (fpBmp == NULL)    // 파일 열기에 실패하면
		{
			perror("비트맵 파일 열기 실패");
			printf("오류를 검토하고 다시 입력해주세요. \n");
			continue;
		}

		// 비트맵 파일 헤더 읽기. 읽기에 실패하면 파일 포인터를 닫고 프로그램 종료
		if (fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fpBmp) < 1)
		{
			fclose(fpBmp);
			printf("비트맵 파일 헤더 읽기에 실패하였습니다. \n");
			printf("오류를 검토하고 다시 입력해주세요. \n");
			continue;
		}

		// 매직 넘버가 MB가 맞는지 확인(2바이트 크기의 BM을 리틀 엔디언으로 읽었으므로 MB가 됨)
		// 매직 넘버가 맞지 않으면 프로그램 종료
		if (fileHeader.bfType != 'MB')
		{
			fclose(fpBmp);
			printf("매직 넘버가 맞지 않습니다. \n");
			printf("오류를 검토하고 다시 입력해주세요. \n");
			continue;
		}

		// 비트맵 정보 헤더 읽기. 읽기에 실패하면 파일 포인터를 닫고 프로그램 종료
		if (fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fpBmp) < 1)
		{
			fclose(fpBmp);
			printf("비트맵 정보 헤더 읽기에 실패하였습니다. \n");
			printf("오류를 검토하고 다시 입력해주세요. \n");
			continue;
		}

		// 24비트 비트맵이 아니면 프로그램 종료
		if (infoHeader.biBitCount != 24)
		{
			fclose(fpBmp);
			printf("24비트 비트맵이 아닙니다. \n");
			printf("오류를 검토하고 다시 입력해주세요. \n");
			continue;
		}

		size = infoHeader.biSizeImage;    // 픽셀 데이터 크기
		width = infoHeader.biWidth;       // 비트맵 이미지의 가로 크기
		height = infoHeader.biHeight;     // 비트맵 이미지의 세로 크기

										  // 이미지의 가로 크기에 픽셀 크기를 곱하여 가로 한 줄의 크기를 구하고 4로 나머지를 구함
										  // 그리고 4에서 나머지를 빼주면 남는 공간을 구할 수 있음.
										  // 만약 남는 공간이 0이라면 최종 결과가 4가 되므로 여기서 다시 4로 나머지를 구함
		padding = (PIXEL_ALIGN - ((width * PIXEL_SIZE) % PIXEL_ALIGN)) % PIXEL_ALIGN;

		if (size == 0)    // 픽셀 데이터 크기가 0이라면
		{
			// 이미지의 가로 크기 * 픽셀 크기에 남는 공간을 더해주면 완전한 가로 한 줄 크기가 나옴
			// 여기에 이미지의 세로 크기를 곱해주면 픽셀 데이터의 크기를 구할 수 있음
			size = (width * PIXEL_SIZE + padding) * height;
		}

		image = malloc(size);    // 픽셀 데이터의 크기만큼 동적 메모리 할당

								 // 파일 포인터를 픽셀 데이터의 시작 위치로 이동
		fseek(fpBmp, fileHeader.bfOffBits, SEEK_SET);

		// 파일에서 픽셀 데이터 크기만큼 읽음. 읽기에 실패하면 파일 포인터를 닫고 프로그램 종료
		if (fread(image, size, 1, fpBmp) < 1)
		{
			fclose(fpBmp);
			printf("픽셀 데이터 읽기에 실패하였습니다. \n");
			printf("오류를 검토하고 다시 입력해주세요. \n");
			continue;
		}

		fclose(fpBmp);    // 비트맵 파일 닫기

		char savefilename[100];		// 저장 파일 이름
		printf("\n저장할 텍스트 파일 이름 입력 ( .txt 입력 필수!!) \n");
		printf(">>> ");
		gets_s(savefilename, sizeof(savefilename));

		fpTxt = fopen(savefilename, "w");    // 결과 출력용 텍스트 파일 열기
		if (fpTxt == NULL)    // 파일 열기에 실패하면
		{
			free(image);      // 픽셀 데이터를 저장한 동적 메모리 해제
			perror("결과 출력용 텍스트 파일 열기에 실패하였습니다. 잠재적인 오류가 발생하였습니다. \n");
			printf("앱을 강제종료합니다. \n");
			return 0;         // 프로그램 종료
		}

		// 픽셀 데이터는 아래 위가 뒤집혀서 저장되므로 아래쪽부터 반복
		// 세로 크기만큼 반복
		for (int y = height - 1; y >= 0; y--)
		{
			// 가로 크기만큼 반복
			for (int x = 0; x < width; x++)
			{
				// 일렬로 된 배열에 접근하기 위해 인덱스를 계산
				// (x * 픽셀 크기)는 픽셀의 가로 위치
				// (y * (세로 크기 * 픽셀 크기))는 픽셀이 몇 번째 줄인지 계산
				// 남는 공간 * y는 줄별로 누적된 남는 공간
				int index = (x * PIXEL_SIZE) + (y * (width * PIXEL_SIZE)) + (padding * y);

				// 현재 픽셀의 주소를 RGBTRIPLE 포인터로 변환하여 RGBTRIPLE 포인터에 저장
				RGBTRIPLE *pixel = (RGBTRIPLE *)&image[index];

				// RGBTRIPLE 구조체로 파랑, 초록, 빨강값을 가져옴
				unsigned char blue = pixel->rgbtBlue;
				unsigned char green = pixel->rgbtGreen;
				unsigned char red = pixel->rgbtRed;

				// 파랑, 초록, 빨강값의 평균을 구하면 흑백 이미지를 얻을 수 있음
				unsigned char gray = (red + green + blue) / PIXEL_SIZE;

				// 흑백값에 ASCII 문자의 개수를 곱한 뒤 256으로 나누면 흑백값에 따라 
				// ASCII 문자의 인덱스를 얻을 수 있음
				char c = ascii[gray * sizeof(ascii) / 256];

				// 비트맵 이미지에서는 픽셀의 가로, 세로 크기가 똑같지만
				// 보통 ASCII 문자는 세로로 길쭉한 형태이므로 정사각형 모양과 비슷하게 보여주기 위해
				// 같은 문자를 두 번 저장해줌
				fprintf(fpTxt, "%c%c", c, c);    // 텍스트 파일에 문자 출력
			}
			fprintf(fpTxt, "\n");    // 가로 픽셀 저장이 끝났으면 줄바꿈을 해줌
		}

		fclose(fpTxt);    // 텍스트 파일 닫기

		textcolor(10);
		printf("\n아스키 아트 제작이 완료되었습니다. \n");
		textcolor(11);
		printf("제작된 파일은 실행폴더 안에 '%s' 이름으로 저장되어 있습니다. \n\n", savefilename);
		textcolor(15);

		free(image);      // 픽셀 데이터를 저장한 동적 메모리 해제
		break;
	}
	return 0;
}

/*  개발자: Lulin Pollux (Team Project member) */
/*  MIT License
	해당 C 소스파일(.c)은 MIT License에 따라 이용할 수 있습니다.
	아스키 아트 변환 알고리즘 출처: https://dojang.io/mod/page/view.php?id=704 */