#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#include "functionheader.h"
 
#pragma comment(lib, "winmm.lib")	// �������� ���� �ڿ� ��ũ�� �� winmm.lib������ �߰���
 
// ���ĺ��� ����Ǵ� ����ü�� ���� ����� 1����Ʈ ������ ��
// ������ ���� ����� ������ ����
#pragma pack(push,1)
 
// ª�� �̵�޽����� ����ü
typedef struct
{
    BYTE byteState;    // �̵� �޽���
    BYTE byteNote;     // �޽����� ���� ��
    BYTE byteVelocity; // Ű���带 �����ų� ������ �ӵ� 
    BYTE byteNULL;
}MJGRShortMidiMSG_ST;
 
// MJGRShortMidiMSG_ST ����ü�� ���� DWORD������ �ٲܶ� ����� ����ü
// DWORD�� unsigned long�Դϴ�.
typedef union  
{
    DWORD                dwMidi_Data;
    MJGRShortMidiMSG_ST  stMidi_Data;
}MJGRShortMidiMSG;
 
// ������ ����ü ���� ������� �ٲ�
#pragma pack(pop)
 
// �̵� ��� �ڵ�
// �� �ڵ� ������ �̿��� ������ �̵���ġ�� ��Ʈ�� �մϴ�.
HMIDIOUT     m_DevHandle;

// ������ ������� �����ڵ带 �����ϴ� ����
MMRESULT     m_MMErrCode;

// ���� �̵� ��¿� ���� ��ġ �Ӽ��� ������ ����ü ����
MIDIOUTCAPS  m_NowMidiOutCaps;


/* MIDI �Լ� ��� */
/*-----------------------------------------------------------------------------------------------------*/
// �̵� ��� �߿� �߻��ϴ� �޽����� ���� �ݹ� �Լ� (����ִ� �Լ�)
void CALLBACK MidiOutProc(HMIDIOUT MidiOut, UINT Msg, DWORD Instance, DWORD Param1, DWORD Param2)
{
}
 
// �̵� ���� �ڵ带 ���ڿ��� �ٲ㼭 ������ִ� �Լ�
void Midi_OutputError(MMRESULT mmrErrCode)
{
	// ���� ���ڿ��� ������ �迭
    char m_szErrMsg[128];
    
	// ���� �ڵ带 ���ڿ��� ��ȯ
    midiInGetErrorText(mmrErrCode, (char *)m_szErrMsg, sizeof(m_szErrMsg));
    
	// ��ȯ�� ���ڿ��� �޽��� �ڽ��� ���
    MessageBox(0, m_szErrMsg, "Midi Error!!!", MB_OK);
}
 
// �̵� ��ġ ��ȣ�� �˾� ���� �Լ�
// �̵���ġ�� �Ӽ��� �˾Ƴ��� �� �Լ��� �ʿ�
long Midi_GetDevID(HMIDIOUT m_DevOutHandle)
{
	// ��ġ ��ȣ�� ������ ����
    UINT uDeviceID;

	// �̵� ��� �ڵ鿡 �����ϴ� ��ġ ��ȣ�� �����ؼ� uDeviceID������ ����
    MMRESULT Result = midiOutGetID(m_DevOutHandle, &uDeviceID);
    
	// ��ġ�� �����ϴ� �߿� ������ ���� �����ϸ�...
    if(Result != MMSYSERR_NOERROR)
    {
		// ���� ��� �� ������ ����� ���ϰ����� �˸�
        Midi_OutputError(Result);
        return -1;
    }
    
	// ��ġ ��ȣ�� ����
    return (long)uDeviceID;
}
 
// �̵� �ڵ��� �̿��� �̵� ��ġ �Ӽ��� MIDIOUTCAPS����ü ������ �������ִ� �Լ�
void Midi_GetDevCaps(HMIDIOUT m_DevOutHandle, MIDIOUTCAPS *Caps)
{
	// ��ġ ��ȣ�� ������ ����
    long lDeviceID;

	// ���� �ڵ带 ������ ����
    MMRESULT Result;

	// �̵� �ڵ��� �̿��� ��ġ ��ȣ�� �����ؼ� lDeviceID������ ����
    lDeviceID=Midi_GetDevID(m_DevOutHandle);
 
	// lDeviceID�� ������ ������ �� ����̹Ƿ� �� �Լ��� ó���� ���̻� �������� �ʴ´�.
    if (lDeviceID < 0) return;
 
	// �̵� ��ġ�� �Ӽ��� MIDIOUTCAPS����ü ������ �����Ѵ�.
    Result = midiOutGetDevCaps((UINT)lDeviceID, Caps, sizeof(MIDIOUTCAPS));
    
	// ������ ���ٸ� �������ڿ��� ����Ѵ�.
    if(Result != MMSYSERR_NOERROR)
    {
        Midi_OutputError(Result);
    }
}
 
// ��ġ��ȣ�� �ش��ϴ� �̵���ġ�� ����.
HMIDIOUT Midi_Open(WORD wDevsNum)
{
    WORD      wMaxDevNum = 0;
    MMRESULT  uiMidiOpen = 0;
    HMIDIOUT  m_DevHandle = NULL;
    
	// ��밡���� ��ġ�� �� ������ wMaxDevNum������ ����
    wMaxDevNum = midiInGetNumDevs();
 
	// �Է��� ��ȣ�� �� �������� ���ų� ū ���̸� ������ ��ġ��ȣ�� 0���� �����Ѵ�.
    if (wDevsNum >= wMaxDevNum)
    {
        wDevsNum = 0;
    }
    
	// wDevsNum������ ����� ���� �ش��ϴ� �̵���ġ�� ���� �� ��ġ�ڵ鰪�� m_DevHandle�� ����
	// �����߿� �߻��ϴ� �޽����� �ݹ��Լ� MidiOutProc�� ����
    uiMidiOpen = midiOutOpen(&m_DevHandle, wDevsNum, (DWORD64)(MidiOutProc), (DWORD64)NULL, CALLBACK_FUNCTION);
    
	// ���� ���� ������ �߻��ϸ� 
    if(uiMidiOpen != MMSYSERR_NOERROR)
    {
		//�������ڿ��� ����Ѵ�.
        Midi_OutputError(uiMidiOpen);
		// NULL���� ����
        return NULL;
    }
    
	// ��ġ �ڵ��� ����
    return m_DevHandle;
}
 
// �ڵ鰪�� �ش��ϴ� �̵���ġ�� �ݽ��ϴ�.
LRESULT Midi_Close(HMIDIOUT m_DevOutHandle)
{
    MMRESULT Result;
    
	// �̵� �ڵ鰪�� �̿��� ��ġ�� �ݽ��ϴ�.
    Result = midiOutClose(m_DevOutHandle);
 
	// �ݴ� ���߿� ������ ����� 
    if(Result != MMSYSERR_NOERROR)
    {
		// ���� ���
        Midi_OutputError(Result);
		// �ݱ� ���и� ���ϰ����� �˸�
        return FALSE;
    }
    
	// �ݱ� ������ ���ϰ����� �˸�
    return TRUE;
}
 
// ª�� �̵� �޽����� �̵� ��ġ�� ������ �Լ�
void Midi_SendShortMsg(HMIDIOUT m_DevOutHandle, BYTE byteState, BYTE byteNote, BYTE byteValo)
{
    MJGRShortMidiMSG sMsg;
 
	// MJGRShortMidiMSG����ü�ȿ� �ִ�
	// MJGRShortMidiMSG_ST����ü ������ �� ��� ������ ���� ä���ִ´�.
    sMsg.stMidi_Data.byteVelocity = byteValo;
    sMsg.stMidi_Data.byteNote     = byteNote;
    sMsg.stMidi_Data.byteState    = byteState;
    sMsg.stMidi_Data.byteNULL     = 0;
    
	// ��� ��ġ�� ���� ä������ ����ü�� �����͸�
	// ������.
    midiOutShortMsg(m_DevOutHandle, sMsg.dwMidi_Data);
}
 
// �� �̵� �޽����� �̵� ��ġ�� ������ �Լ�
void Midi_SendLongMsg(HMIDIOUT m_DevOutHandle, BYTE *lpMsg, DWORD dwMsgLength)
{
    MIDIHDR  m_MIDIHdr;
    MMRESULT Result;
    
    ZeroMemory(&m_MIDIHdr, sizeof(MIDIHDR));    
    
    m_MIDIHdr.lpData         = (char *)lpMsg;
    m_MIDIHdr.dwBufferLength = dwMsgLength;
    m_MIDIHdr.dwFlags        = 0;
    
	// �� �̵����͸� ��ġ�� ������ ���� �غ��۾��� ��
    Result = midiOutPrepareHeader(m_DevOutHandle, &m_MIDIHdr, sizeof(MIDIHDR));
    
    if(Result != MMSYSERR_NOERROR)
    {
        Midi_OutputError(Result);
        return ;
    }
    
	// �� �̵����͸� ��ġ�� ����
    Result = midiOutLongMsg(m_DevOutHandle, &m_MIDIHdr, sizeof(MIDIHDR));
    
    if(Result != MMSYSERR_NOERROR)
    {
        Midi_OutputError(Result);
        return ;
    }
    
	// �� �̵����͸� ��ġ�� ������ ���� �۾��� ����
    midiOutUnprepareHeader(m_DevOutHandle, &m_MIDIHdr, sizeof(MIDIHDR));
}
 
// ��� ä���� �������� ���� �����ϰ� ����� �Լ�...
// ������ ���ߴ� ���� �ƴ�!
void Midi_AllChannelSoundOff(HMIDIOUT m_DevOutHandle)
{
    BYTE channel;
    
    for(channel = 0; channel < 16; channel++)
    {
        Midi_SendShortMsg(m_DevOutHandle, (BYTE)(0xB0+channel), 0x78, 0);
    }
}
/*-----------------------------------------------------------------------------------------------------*/

/* ���ø����̼� ���� �Լ� */
/*-----------------------------------------------------------------------------------------------------*/
int AsktoStart(void)
{
	char input = '0';

	textcolor(14);
	printf("\nŰ���� ���α׷� ����: \n");
	printf("�� ���ø����̼��� ��ǻ���� CPU�� ���� ����մϴ�. (i7 ���� 15.5%%) \n");
	textcolor(15);
	printf("���� �Ͻðڽ��ϱ�? Y/N : ");
	while (1)
	{
		scanf_s("%c", &input, 1);
		clearInputBuffer();

		if ((input == 'y') || (input == 'Y'))
			break;		//���α׷� ����
		else if ((input == 'n') || (input == 'N'))
		{
			textcolor(12);
			printf("\n������� ��û���� App�� �����߽��ϴ�. \n");
			textcolor(14);
			printf("���� �����մϴ�. \n\n");
			textcolor(15);
			system("pause");
			return 0;		//���α׷� ����
		}
		else
			printf("�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է����ּ���. : ");
	}
	return 1;
}

void PrintConsole(void)		// �ܼ�â�� �ؽ�Ʈ ���
{
	textcolor(14);
	printf("\n [ESC] Ű�� ������ �����մϴ�. \n");
	textcolor(15);
	printf("�Ʒ��� �ǾƳ� �ǹݿ� �ش��ϴ� Ű������ Ű�� ��Ÿ���ϴ�. \n");
	printf("[A]Ű���� �ǹ��� 'C4'�� �ش��ϴ� �Ҹ��� ���ϴ�. \n\n");

	printf("   [W]   [E]       [T]   [Y]   [U]       [O]   [P]\n\n");

	printf("[A]   [S]   [D] [F]   [G]   [H]   [J] [K]   [L]   [;] [\"]\n");
}
/*-----------------------------------------------------------------------------------------------------*/

void Keyboard(void)
{
	// ���� �����ϱ� ���� ���
	short start_input;
	start_input = AsktoStart();
	if (start_input == 0)
		return;

	int i, loop;
    BYTE szMusKey[18] = { 0x41,0x57,0x53,0x45,0x44,
                          0x46,0x54,0x47,0x59,0x48,
                          0x55,0x4A,0x4B,0x4F,0x4C,
                          0x50,0xBA,0xDE };		// �ǾƳ� �ǹݿ� ���� ���Ĺ�� A W S E D ...
    BYTE szMusKeyOnOff[18] = {0};
 
	// ��ġ ��ȣ�� 0���� �̵� ��ġ�� ����.
    m_DevHandle = Midi_Open(0);
 
	// ������ �߻��ϸ� ���α׷� ����
    if (m_DevHandle == NULL)
    {
        return ;
    }

	// �ܼ�â�� �ؽ�Ʈ ���
	PrintConsole();
 
	// Ȥ�� �������� ���� ������ �׸��ϰ� �ϰ�
    Midi_AllChannelSoundOff(m_DevHandle);
	// 1�� ä���� ������ 127�� ���� (0���� 127������ ���� ���� �� ����)
    Midi_SendShortMsg(m_DevHandle, 0xB0, 7, 127);
 
    loop = 1;
    while(loop) // loop������ 0�� �ƴϸ� ��� �ݺ� (���ѷ������� CPU ���ҽ��� ���� �Դ´�)
    {
		// ���� Ű�� ������...
		if (_kbhit())
		{
			// ESCŰ�� ������ loop������ ���� 0�� ����
			if (GetKeyState(VK_ESCAPE) & 0xFF00)
				loop = 0;
			else  // �� ���� Ű�� ���� ���� ���...
			{
				for (i = 0; i < 18; i++)
				{
					// szMusKey�迭�� i��° ���� �ش��ϴ� Ű�� ���� ���̶��...
					if (GetKeyState(szMusKey[i]) & 0xFF00)
					{
						// ������ �� Ű�� ���� ���� ���ٸ�
						if (szMusKeyOnOff[i] == 0)
						{
							// ������ �� Ű�� ������ ������ ���
							szMusKeyOnOff[i] = 1;

							/* ���� �����ϸ� �Ǻ����ְ� �����ϴ� */
							/*-----------------------------------------------------------------*/

							// ���� ���� Ű�� �ش��ϴ� �̵� ���� ����
							Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + i), 120);
							/*-----------------------------------------------------------------*/
						}
					}
				}
			}
		}

        for (i = 0; i < 18; i++)
        {
			// szMusKey�迭�� i��° ���� �ش��ϴ� Ű�� ���� ���� �ƴ϶��...
            if (!(GetKeyState(szMusKey[i]) & 0xFF00))
            {
				// �� Ű�� ���� ���� �ִ� Ű ���...
                if (szMusKeyOnOff[i] != 0)
                {
					// ���� ���� ���� �ɷ� ����ϰ� 
                    szMusKeyOnOff[i] = 0;
					// ���� ���� �Ҹ��� ����
                    Midi_SendShortMsg(m_DevHandle, 0x80, (BYTE)(0x30 + i), 120);
                }
            }
        }
    }

	/* ���⼭���ʹ� ��� ���ָ� �����Ѵ�. */
	/*-------------------------------------------------------------------------*/

	// ���� �������� �Ҹ��� ��� ����...
    for (i = 0; i < 18; i++)
    {
        if (szMusKeyOnOff[i] != 0)
        {       
            Midi_SendShortMsg(m_DevHandle, 0x80, (BYTE)(0x30 + i), 120);
        }   
    }
    Midi_AllChannelSoundOff(m_DevHandle);
 
	// ���� �̵� ��ġ�� �ݴ´�.
    Midi_Close(m_DevHandle);
	/*-------------------------------------------------------------------------*/
}

/*  ������: Lulin Pollux (Team Project member) */
/*  MIT License
	�ش� C�ڵ�����(.c)�� MIT License�� ���� �̿��� �� �ֽ��ϴ�.
	Ű���� �˰��� ��ó: http://blog.naver.com/mojigura/60050710954 */