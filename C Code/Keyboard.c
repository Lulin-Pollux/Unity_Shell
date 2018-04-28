#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#include "functionheader.h"
 
#pragma comment(lib, "winmm.lib")	// 컴파일이 끝난 뒤에 링크할 때 winmm.lib파일을 추가함
 
// 이후부터 선언되는 구조체의 정렬 방식을 1바이트 단위로 함
// 원래의 정렬 방식을 저장해 놓음
#pragma pack(push,1)
 
// 짧은 미디메시지의 구조체
typedef struct
{
    BYTE byteState;    // 미디 메시지
    BYTE byteNote;     // 메시지에 대한 값
    BYTE byteVelocity; // 키보드를 누르거나 뗄때의 속도 
    BYTE byteNULL;
}MJGRShortMidiMSG_ST;
 
// MJGRShortMidiMSG_ST 구조체의 값을 DWORD형으로 바꿀때 사용할 공용체
// DWORD는 unsigned long입니다.
typedef union  
{
    DWORD                dwMidi_Data;
    MJGRShortMidiMSG_ST  stMidi_Data;
}MJGRShortMidiMSG;
 
// 원래의 구조체 정렬 방식으로 바꿈
#pragma pack(pop)
 
// 미디 출력 핸들
// 이 핸들 변수를 이용해 지정된 미디장치를 컨트롤 합니다.
HMIDIOUT     m_DevHandle;

// 에러가 났을경우 에러코드를 저장하는 변수
MMRESULT     m_MMErrCode;

// 현재 미디 출력에 관한 장치 속성을 저장할 구조체 변수
MIDIOUTCAPS  m_NowMidiOutCaps;


/* MIDI 함수 목록 */
/*-----------------------------------------------------------------------------------------------------*/
// 미디 출력 중에 발생하는 메시지를 받을 콜백 함수 (비어있는 함수)
void CALLBACK MidiOutProc(HMIDIOUT MidiOut, UINT Msg, DWORD Instance, DWORD Param1, DWORD Param2)
{
}
 
// 미디 에러 코드를 문자열로 바꿔서 출력해주는 함수
void Midi_OutputError(MMRESULT mmrErrCode)
{
	// 에러 문자열을 저장할 배열
    char m_szErrMsg[128];
    
	// 에러 코드를 문자열로 변환
    midiInGetErrorText(mmrErrCode, (char *)m_szErrMsg, sizeof(m_szErrMsg));
    
	// 변환된 문자열을 메시지 박스로 출력
    MessageBox(0, m_szErrMsg, "Midi Error!!!", MB_OK);
}
 
// 미디 장치 번호를 알아 내는 함수
// 미디장치의 속성을 알아낼때 이 함수가 필요
long Midi_GetDevID(HMIDIOUT m_DevOutHandle)
{
	// 장치 번호를 저장할 변수
    UINT uDeviceID;

	// 미디 출력 핸들에 대응하는 장치 번호를 조사해서 uDeviceID변수에 저장
    MMRESULT Result = midiOutGetID(m_DevOutHandle, &uDeviceID);
    
	// 장치를 조사하던 중에 에러가 나서 실패하면...
    if(Result != MMSYSERR_NOERROR)
    {
		// 에러 출력 및 에러난 사실을 리턴값으로 알림
        Midi_OutputError(Result);
        return -1;
    }
    
	// 장치 번호를 리턴
    return (long)uDeviceID;
}
 
// 미디 핸들을 이용해 미디 장치 속성을 MIDIOUTCAPS구조체 변수에 저장해주는 함수
void Midi_GetDevCaps(HMIDIOUT m_DevOutHandle, MIDIOUTCAPS *Caps)
{
	// 장치 번호를 저장할 변수
    long lDeviceID;

	// 에러 코드를 저장할 변수
    MMRESULT Result;

	// 미디 핸들을 이용해 장치 번호를 조사해서 lDeviceID변수에 저장
    lDeviceID=Midi_GetDevID(m_DevOutHandle);
 
	// lDeviceID가 음수면 에러가 난 경우이므로 이 함수의 처리를 더이상 진행하지 않는다.
    if (lDeviceID < 0) return;
 
	// 미디 장치의 속성을 MIDIOUTCAPS구조체 변수에 저장한다.
    Result = midiOutGetDevCaps((UINT)lDeviceID, Caps, sizeof(MIDIOUTCAPS));
    
	// 에러가 났다면 에러문자열을 출력한다.
    if(Result != MMSYSERR_NOERROR)
    {
        Midi_OutputError(Result);
    }
}
 
// 장치번호에 해당하는 미디장치를 연다.
HMIDIOUT Midi_Open(WORD wDevsNum)
{
    WORD      wMaxDevNum = 0;
    MMRESULT  uiMidiOpen = 0;
    HMIDIOUT  m_DevHandle = NULL;
    
	// 사용가능한 장치의 총 갯수를 wMaxDevNum변수에 저장
    wMaxDevNum = midiInGetNumDevs();
 
	// 입력한 번호가 총 갯수보다 같거나 큰 값이면 오픈할 장치번호를 0으로 조정한다.
    if (wDevsNum >= wMaxDevNum)
    {
        wDevsNum = 0;
    }
    
	// wDevsNum변수에 저장된 값에 해당하는 미디장치를 열고 그 장치핸들값을 m_DevHandle에 저장
	// 연주중에 발생하는 메시지는 콜백함수 MidiOutProc로 보냄
    uiMidiOpen = midiOutOpen(&m_DevHandle, wDevsNum, (DWORD64)(MidiOutProc), (DWORD64)NULL, CALLBACK_FUNCTION);
    
	// 열기 도중 에러가 발생하면 
    if(uiMidiOpen != MMSYSERR_NOERROR)
    {
		//에러문자열을 출력한다.
        Midi_OutputError(uiMidiOpen);
		// NULL값을 리턴
        return NULL;
    }
    
	// 장치 핸들을 리턴
    return m_DevHandle;
}
 
// 핸들값에 해당하는 미디장치를 닫습니다.
LRESULT Midi_Close(HMIDIOUT m_DevOutHandle)
{
    MMRESULT Result;
    
	// 미디 핸들값을 이용해 장치를 닫습니다.
    Result = midiOutClose(m_DevOutHandle);
 
	// 닫는 도중에 에러가 생기면 
    if(Result != MMSYSERR_NOERROR)
    {
		// 에러 출력
        Midi_OutputError(Result);
		// 닫기 실패를 리턴값으로 알림
        return FALSE;
    }
    
	// 닫기 성공을 리턴값으로 알림
    return TRUE;
}
 
// 짧은 미디 메시지를 미디 장치로 보내는 함수
void Midi_SendShortMsg(HMIDIOUT m_DevOutHandle, BYTE byteState, BYTE byteNote, BYTE byteValo)
{
    MJGRShortMidiMSG sMsg;
 
	// MJGRShortMidiMSG구조체안에 있는
	// MJGRShortMidiMSG_ST구조체 변수의 각 멤버 변수에 값을 채워넣는다.
    sMsg.stMidi_Data.byteVelocity = byteValo;
    sMsg.stMidi_Data.byteNote     = byteNote;
    sMsg.stMidi_Data.byteState    = byteState;
    sMsg.stMidi_Data.byteNULL     = 0;
    
	// 출력 장치로 값을 채워넣은 구조체의 데이터를
	// 보낸다.
    midiOutShortMsg(m_DevOutHandle, sMsg.dwMidi_Data);
}
 
// 긴 미디 메시지를 미디 장치로 보내는 함수
void Midi_SendLongMsg(HMIDIOUT m_DevOutHandle, BYTE *lpMsg, DWORD dwMsgLength)
{
    MIDIHDR  m_MIDIHdr;
    MMRESULT Result;
    
    ZeroMemory(&m_MIDIHdr, sizeof(MIDIHDR));    
    
    m_MIDIHdr.lpData         = (char *)lpMsg;
    m_MIDIHdr.dwBufferLength = dwMsgLength;
    m_MIDIHdr.dwFlags        = 0;
    
	// 긴 미디데이터를 장치로 보내기 위한 준비작업을 함
    Result = midiOutPrepareHeader(m_DevOutHandle, &m_MIDIHdr, sizeof(MIDIHDR));
    
    if(Result != MMSYSERR_NOERROR)
    {
        Midi_OutputError(Result);
        return ;
    }
    
	// 긴 미디데이터를 장치로 보냄
    Result = midiOutLongMsg(m_DevOutHandle, &m_MIDIHdr, sizeof(MIDIHDR));
    
    if(Result != MMSYSERR_NOERROR)
    {
        Midi_OutputError(Result);
        return ;
    }
    
	// 긴 미디데이터를 장치로 보내기 위한 작업을 끝냄
    midiOutUnprepareHeader(m_DevOutHandle, &m_MIDIHdr, sizeof(MIDIHDR));
}
 
// 모든 채널의 연주중인 음을 종료하게 만드는 함수...
// 볼륨을 낮추는 것이 아님!
void Midi_AllChannelSoundOff(HMIDIOUT m_DevOutHandle)
{
    BYTE channel;
    
    for(channel = 0; channel < 16; channel++)
    {
        Midi_SendShortMsg(m_DevOutHandle, (BYTE)(0xB0+channel), 0x78, 0);
    }
}
/*-----------------------------------------------------------------------------------------------------*/

/* 애플리케이션 관련 함수 */
/*-----------------------------------------------------------------------------------------------------*/
int AsktoStart(void)
{
	char input = '0';

	textcolor(14);
	printf("\n키보드 프로그램 도움말: \n");
	printf("이 애플리케이션은 컴퓨터의 CPU를 많이 사용합니다. (i7 기준 15.5%%) \n");
	textcolor(15);
	printf("실행 하시겠습니까? Y/N : ");
	while (1)
	{
		scanf_s("%c", &input, 1);
		clearInputBuffer();

		if ((input == 'y') || (input == 'Y'))
			break;		//프로그램 시작
		else if ((input == 'n') || (input == 'N'))
		{
			textcolor(12);
			printf("\n사용자의 요청으로 App을 중지했습니다. \n");
			textcolor(14);
			printf("앱을 종료합니다. \n\n");
			textcolor(15);
			system("pause");
			return 0;		//프로그램 종료
		}
		else
			printf("잘못된 값을 입력했습니다. 다시 입력해주세요. : ");
	}
	return 1;
}

void PrintConsole(void)		// 콘솔창에 텍스트 출력
{
	textcolor(14);
	printf("\n [ESC] 키를 누르면 종료합니다. \n");
	textcolor(15);
	printf("아래는 피아노 건반에 해당하는 키보드의 키를 나타냅니다. \n");
	printf("[A]키부터 건반의 'C4'에 해당하는 소리가 납니다. \n\n");

	printf("   [W]   [E]       [T]   [Y]   [U]       [O]   [P]\n\n");

	printf("[A]   [S]   [D] [F]   [G]   [H]   [J] [K]   [L]   [;] [\"]\n");
}
/*-----------------------------------------------------------------------------------------------------*/

void Keyboard(void)
{
	// 앱을 실행하기 전에 물어봄
	short start_input;
	start_input = AsktoStart();
	if (start_input == 0)
		return;

	int i, loop;
    BYTE szMusKey[18] = { 0x41,0x57,0x53,0x45,0x44,
                          0x46,0x54,0x47,0x59,0x48,
                          0x55,0x4A,0x4B,0x4F,0x4C,
                          0x50,0xBA,0xDE };		// 피아노 건반에 따른 알파뱃들 A W S E D ...
    BYTE szMusKeyOnOff[18] = {0};
 
	// 장치 번호가 0번인 미디 장치를 연다.
    m_DevHandle = Midi_Open(0);
 
	// 에러가 발생하면 프로그램 종료
    if (m_DevHandle == NULL)
    {
        return ;
    }

	// 콘솔창에 텍스트 출력
	PrintConsole();
 
	// 혹시 연주중인 것이 있으면 그만하게 하고
    Midi_AllChannelSoundOff(m_DevHandle);
	// 1번 채널의 볼륨을 127로 세팅 (0부터 127까지의 값을 가질 수 있음)
    Midi_SendShortMsg(m_DevHandle, 0xB0, 7, 127);
 
    loop = 1;
    while(loop) // loop변수가 0이 아니면 계속 반복 (무한루프여서 CPU 리소스를 많이 먹는다)
    {
		// 눌린 키가 있으면...
		if (_kbhit())
		{
			// ESC키가 눌리면 loop변수의 값을 0을 만듬
			if (GetKeyState(VK_ESCAPE) & 0xFF00)
				loop = 0;
			else  // 그 외의 키가 눌린 것이 라면...
			{
				for (i = 0; i < 18; i++)
				{
					// szMusKey배열의 i번째 값에 해당하는 키가 눌린 것이라면...
					if (GetKeyState(szMusKey[i]) & 0xFF00)
					{
						// 이전에 이 키를 누른 적이 없다면
						if (szMusKeyOnOff[i] == 0)
						{
							// 이전에 이 키가 눌렀던 것으로 기록
							szMusKeyOnOff[i] = 1;

							/* 여길 수정하면 악보연주가 가능하다 */
							/*-----------------------------------------------------------------*/

							// 현재 눌린 키에 해당하는 미디 음을 연주
							Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + i), 120);
							/*-----------------------------------------------------------------*/
						}
					}
				}
			}
		}

        for (i = 0; i < 18; i++)
        {
			// szMusKey배열의 i번째 값에 해당하는 키가 눌린 것이 아니라면...
            if (!(GetKeyState(szMusKey[i]) & 0xFF00))
            {
				// 그 키가 누른 적이 있는 키 라면...
                if (szMusKeyOnOff[i] != 0)
                {
					// 누른 적이 없는 걸로 기록하고 
                    szMusKeyOnOff[i] = 0;
					// 연주 중인 소리를 끈다
                    Midi_SendShortMsg(m_DevHandle, 0x80, (BYTE)(0x30 + i), 120);
                }
            }
        }
    }

	/* 여기서부터는 모든 연주를 중지한다. */
	/*-------------------------------------------------------------------------*/

	// 현재 연주중인 소리를 모두 끈다...
    for (i = 0; i < 18; i++)
    {
        if (szMusKeyOnOff[i] != 0)
        {       
            Midi_SendShortMsg(m_DevHandle, 0x80, (BYTE)(0x30 + i), 120);
        }   
    }
    Midi_AllChannelSoundOff(m_DevHandle);
 
	// 열린 미디 장치를 닫는다.
    Midi_Close(m_DevHandle);
	/*-------------------------------------------------------------------------*/
}

/*  개발자: Lulin Pollux (Team Project member) */
/*  MIT License
	해당 C코드파일(.c)은 MIT License에 따라 이용할 수 있습니다.
	키보드 알고리즘 출처: http://blog.naver.com/mojigura/60050710954 */