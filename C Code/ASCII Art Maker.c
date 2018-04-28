#define _CRT_SECURE_NO_WARNINGS    // fopen ���� ���� ���� ������ ���� ����
#include <stdio.h>    // fopen, fread, fseek, fprintf, fclose �Լ��� ����� ��� ����
#include <stdlib.h>   // malloc, free �Լ��� ����� ��� ����
#include <string.h>   // gets_s, puts �Լ��� ����� ��� ����
#include "functionheader.h"

#define PIXEL_SIZE   3    // �ȼ� �� ���� ũ�� 3����Ʈ(24��Ʈ)
#define PIXEL_ALIGN  4    // �ȼ� ������ ���� �� ���� 4�� ��� ũ��� �����

#pragma pack(push, 1)                // ����ü�� 1����Ʈ ũ��� ����

typedef struct _BITMAPFILEHEADER     // BMP ��Ʈ�� ���� ��� ����ü
{
	unsigned short bfType;           // BMP ���� ���� �ѹ�
	unsigned int   bfSize;           // ���� ũ��
	unsigned short bfReserved1;      // ����
	unsigned short bfReserved2;      // ����
	unsigned int   bfOffBits;        // ��Ʈ�� �������� ���� ��ġ
} BITMAPFILEHEADER;

typedef struct _BITMAPINFOHEADER     // BMP ��Ʈ�� ���� ��� ����ü(DIB ���)
{
	unsigned int   biSize;           // ���� ����ü�� ũ��
	int            biWidth;          // ��Ʈ�� �̹����� ���� ũ��
	int            biHeight;         // ��Ʈ�� �̹����� ���� ũ��
	unsigned short biPlanes;         // ����ϴ� �������� ��
	unsigned short biBitCount;       // �ȼ� �ϳ��� ǥ���ϴ� ��Ʈ ��
	unsigned int   biCompression;    // ���� ���
	unsigned int   biSizeImage;      // ��Ʈ�� �̹����� �ȼ� ������ ũ��
	int            biXPelsPerMeter;  // �׸��� ���� �ػ�(���ʹ� �ȼ�)
	int            biYPelsPerMeter;  // �׸��� ���� �ػ�(���ʹ� �ȼ�)
	unsigned int   biClrUsed;        // ���� ���̺��� ���� ���Ǵ� ���� ��
	unsigned int   biClrImportant;   // ��Ʈ���� ǥ���ϱ� ���� �ʿ��� ���� �ε��� ��
} BITMAPINFOHEADER;

typedef struct _RGBTRIPLE            // 24��Ʈ ��Ʈ�� �̹����� �ȼ� ����ü
{
	unsigned char rgbtBlue;          // �Ķ�
	unsigned char rgbtGreen;         // �ʷ�
	unsigned char rgbtRed;           // ����
} RGBTRIPLE;

#pragma pack(pop)

char directory[512];		//���丮 �������� ����

int AskToStart()
{
	char input = '0';

	textcolor(14);
	printf("\n�ƽ�Ű ��Ʈ ���� ���α׷� ����: \n");
	printf("������ ���ϴ� ��Ʈ�� �̹��� ������ ������ exe������ ��ġ�� ������ �־��ֽñ� �ٶ��ϴ�. \n");
	textcolor(15);
	printf("������ �����ϰڽ��ϱ�? Y/N : ");
	while (1)
	{
		scanf_s("%c", &input, 1);
		clearInputBuffer();

		if ((input == 'y') || (input == 'Y'))
			break;		//���α׷� ����
		else if ((input == 'n') || (input == 'N'))
		{
			textcolor(12);
			printf("\n������ �ߴ��Ͽ����ϴ�. \n");
			textcolor(14);
			printf("���� �����մϴ�. \n\n");
			textcolor(15);
			return 0;		//���α׷� ����
		}
		else
			printf("�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է����ּ���. : ");
	}
	return 1;
}

void SetDirectory()
{
	textcolor(11);
	printf("\nexe������ �ִ� ���: ");
	pwd();			//exe���� ���丮 ���
	textcolor(15);
	printf("Tip: ���ϸ� �Է��ϸ� ");
	textcolor(11);
	printf("���� ���");
	textcolor(15);
	printf("�� image�� �ִ°����� �ν��մϴ�. Ex) picture.bmp \n");
	textcolor(12);
	printf("     ���� ���� �����ϰ� �ʹٸ� 'force quit'�� �Է����ּ���. \n");
	textcolor(15);
	printf("������ image�� ��� �Ǵ� �����̸��� �Է����ּ��� (�ݵ�� .bmp���� �Է�!!) \n");
}

int ASCIIArtMaker()
{
	short i;
	i = AskToStart();
	if (i == 0)
		return 0;

	// ������ ������ ����
	//-------------------------------------------------------------------------------------------------
		FILE *fpBmp;                    // ��Ʈ�� ���� ������
		FILE *fpTxt;                    // �ؽ�Ʈ ���� ������
		BITMAPFILEHEADER fileHeader;    // ��Ʈ�� ���� ��� ����ü ����
		BITMAPINFOHEADER infoHeader;    // ��Ʈ�� ���� ��� ����ü ����

		unsigned char *image;    // �ȼ� ������ ������
		int size;                // �ȼ� ������ ũ��
		int width, height;       // ��Ʈ�� �̹����� ����, ���� ũ��
		int padding;             // �ȼ� �������� ���� ũ�Ⱑ 4�� ����� �ƴ� �� ���� ������ ũ��

								 // �� �ȼ��� ǥ���� ASCII ����. �ε����� ���� ���� ������� ���� ǥ��
		char ascii[] = { '#', '#', '@', '%', '=', '+', '*', ':', '-', '.', ' ' };   // 11��
	//-------------------------------------------------------------------------------------------------

		SetDirectory();
		while (1)
		{
		printf(">>> ");
		gets_s(directory, sizeof(directory));

		if (strcmp(directory, "force quit") == 0)		//�� ��������
		{
			textcolor(12);
			printf("\n���� ���� ����Ǿ����ϴ�. \n");
			textcolor(15);
			return 0;
		}

		fpBmp = fopen(directory, "rb");    // ��Ʈ�� ������ ���̳ʸ� ���� ����
		if (fpBmp == NULL)    // ���� ���⿡ �����ϸ�
		{
			perror("��Ʈ�� ���� ���� ����");
			printf("������ �����ϰ� �ٽ� �Է����ּ���. \n");
			continue;
		}

		// ��Ʈ�� ���� ��� �б�. �б⿡ �����ϸ� ���� �����͸� �ݰ� ���α׷� ����
		if (fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fpBmp) < 1)
		{
			fclose(fpBmp);
			printf("��Ʈ�� ���� ��� �б⿡ �����Ͽ����ϴ�. \n");
			printf("������ �����ϰ� �ٽ� �Է����ּ���. \n");
			continue;
		}

		// ���� �ѹ��� MB�� �´��� Ȯ��(2����Ʈ ũ���� BM�� ��Ʋ ��������� �о����Ƿ� MB�� ��)
		// ���� �ѹ��� ���� ������ ���α׷� ����
		if (fileHeader.bfType != 'MB')
		{
			fclose(fpBmp);
			printf("���� �ѹ��� ���� �ʽ��ϴ�. \n");
			printf("������ �����ϰ� �ٽ� �Է����ּ���. \n");
			continue;
		}

		// ��Ʈ�� ���� ��� �б�. �б⿡ �����ϸ� ���� �����͸� �ݰ� ���α׷� ����
		if (fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fpBmp) < 1)
		{
			fclose(fpBmp);
			printf("��Ʈ�� ���� ��� �б⿡ �����Ͽ����ϴ�. \n");
			printf("������ �����ϰ� �ٽ� �Է����ּ���. \n");
			continue;
		}

		// 24��Ʈ ��Ʈ���� �ƴϸ� ���α׷� ����
		if (infoHeader.biBitCount != 24)
		{
			fclose(fpBmp);
			printf("24��Ʈ ��Ʈ���� �ƴմϴ�. \n");
			printf("������ �����ϰ� �ٽ� �Է����ּ���. \n");
			continue;
		}

		size = infoHeader.biSizeImage;    // �ȼ� ������ ũ��
		width = infoHeader.biWidth;       // ��Ʈ�� �̹����� ���� ũ��
		height = infoHeader.biHeight;     // ��Ʈ�� �̹����� ���� ũ��

										  // �̹����� ���� ũ�⿡ �ȼ� ũ�⸦ ���Ͽ� ���� �� ���� ũ�⸦ ���ϰ� 4�� �������� ����
										  // �׸��� 4���� �������� ���ָ� ���� ������ ���� �� ����.
										  // ���� ���� ������ 0�̶�� ���� ����� 4�� �ǹǷ� ���⼭ �ٽ� 4�� �������� ����
		padding = (PIXEL_ALIGN - ((width * PIXEL_SIZE) % PIXEL_ALIGN)) % PIXEL_ALIGN;

		if (size == 0)    // �ȼ� ������ ũ�Ⱑ 0�̶��
		{
			// �̹����� ���� ũ�� * �ȼ� ũ�⿡ ���� ������ �����ָ� ������ ���� �� �� ũ�Ⱑ ����
			// ���⿡ �̹����� ���� ũ�⸦ �����ָ� �ȼ� �������� ũ�⸦ ���� �� ����
			size = (width * PIXEL_SIZE + padding) * height;
		}

		image = malloc(size);    // �ȼ� �������� ũ�⸸ŭ ���� �޸� �Ҵ�

								 // ���� �����͸� �ȼ� �������� ���� ��ġ�� �̵�
		fseek(fpBmp, fileHeader.bfOffBits, SEEK_SET);

		// ���Ͽ��� �ȼ� ������ ũ�⸸ŭ ����. �б⿡ �����ϸ� ���� �����͸� �ݰ� ���α׷� ����
		if (fread(image, size, 1, fpBmp) < 1)
		{
			fclose(fpBmp);
			printf("�ȼ� ������ �б⿡ �����Ͽ����ϴ�. \n");
			printf("������ �����ϰ� �ٽ� �Է����ּ���. \n");
			continue;
		}

		fclose(fpBmp);    // ��Ʈ�� ���� �ݱ�

		char savefilename[100];		// ���� ���� �̸�
		printf("\n������ �ؽ�Ʈ ���� �̸� �Է� ( .txt �Է� �ʼ�!!) \n");
		printf(">>> ");
		gets_s(savefilename, sizeof(savefilename));

		fpTxt = fopen(savefilename, "w");    // ��� ��¿� �ؽ�Ʈ ���� ����
		if (fpTxt == NULL)    // ���� ���⿡ �����ϸ�
		{
			free(image);      // �ȼ� �����͸� ������ ���� �޸� ����
			perror("��� ��¿� �ؽ�Ʈ ���� ���⿡ �����Ͽ����ϴ�. �������� ������ �߻��Ͽ����ϴ�. \n");
			printf("���� ���������մϴ�. \n");
			return 0;         // ���α׷� ����
		}

		// �ȼ� �����ʹ� �Ʒ� ���� �������� ����ǹǷ� �Ʒ��ʺ��� �ݺ�
		// ���� ũ�⸸ŭ �ݺ�
		for (int y = height - 1; y >= 0; y--)
		{
			// ���� ũ�⸸ŭ �ݺ�
			for (int x = 0; x < width; x++)
			{
				// �Ϸķ� �� �迭�� �����ϱ� ���� �ε����� ���
				// (x * �ȼ� ũ��)�� �ȼ��� ���� ��ġ
				// (y * (���� ũ�� * �ȼ� ũ��))�� �ȼ��� �� ��° ������ ���
				// ���� ���� * y�� �ٺ��� ������ ���� ����
				int index = (x * PIXEL_SIZE) + (y * (width * PIXEL_SIZE)) + (padding * y);

				// ���� �ȼ��� �ּҸ� RGBTRIPLE �����ͷ� ��ȯ�Ͽ� RGBTRIPLE �����Ϳ� ����
				RGBTRIPLE *pixel = (RGBTRIPLE *)&image[index];

				// RGBTRIPLE ����ü�� �Ķ�, �ʷ�, �������� ������
				unsigned char blue = pixel->rgbtBlue;
				unsigned char green = pixel->rgbtGreen;
				unsigned char red = pixel->rgbtRed;

				// �Ķ�, �ʷ�, �������� ����� ���ϸ� ��� �̹����� ���� �� ����
				unsigned char gray = (red + green + blue) / PIXEL_SIZE;

				// ��鰪�� ASCII ������ ������ ���� �� 256���� ������ ��鰪�� ���� 
				// ASCII ������ �ε����� ���� �� ����
				char c = ascii[gray * sizeof(ascii) / 256];

				// ��Ʈ�� �̹��������� �ȼ��� ����, ���� ũ�Ⱑ �Ȱ�����
				// ���� ASCII ���ڴ� ���η� ������ �����̹Ƿ� ���簢�� ���� ����ϰ� �����ֱ� ����
				// ���� ���ڸ� �� �� ��������
				fprintf(fpTxt, "%c%c", c, c);    // �ؽ�Ʈ ���Ͽ� ���� ���
			}
			fprintf(fpTxt, "\n");    // ���� �ȼ� ������ �������� �ٹٲ��� ����
		}

		fclose(fpTxt);    // �ؽ�Ʈ ���� �ݱ�

		textcolor(10);
		printf("\n�ƽ�Ű ��Ʈ ������ �Ϸ�Ǿ����ϴ�. \n");
		textcolor(11);
		printf("���۵� ������ �������� �ȿ� '%s' �̸����� ����Ǿ� �ֽ��ϴ�. \n\n", savefilename);
		textcolor(15);

		free(image);      // �ȼ� �����͸� ������ ���� �޸� ����
		break;
	}
	return 0;
}

/*  ������: Lulin Pollux (Team Project member) */
/*  MIT License
	�ش� C �ҽ�����(.c)�� MIT License�� ���� �̿��� �� �ֽ��ϴ�.
	�ƽ�Ű ��Ʈ ��ȯ �˰��� ��ó: https://dojang.io/mod/page/view.php?id=704 */