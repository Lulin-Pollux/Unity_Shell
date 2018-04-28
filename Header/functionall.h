/* C소스파일에서 사용하는 모든 함수들을 여기에 기록한다. */

//Common Function.c
void textcolor(int color_number);
void gotoxy(short x, short y);
void clearInputBuffer();

//Terminal.c
//main() 함수도 사용중입니다.
void Initializing();
void AppLoadingMessage();
void AppClosedMessage();
void AppExecution();
void app_list();
void app_disc();
void cd(char *s);
void date();
void frontpage();
void help();
void pwd();
int UserModeSelect();
int EasyMode();

//ASCII Art Maker.c
int AskToStart();
void SetDirectory();
int ASCIIArtMaker();

//Calculator.c
void Calculator();

//Keyboard.c
int AsktoStart();
void PrintConsole();
void Keyboard();

//Ladder game.c
#define LINE 6
#define MAX (LINE*4)

int baserand(int x, int y);
void VerticalSet(int MAP[20][MAX]);
void HorizonSet(int MAP[20][MAX]);
void PrintLine(int MAP[20][MAX]);
void LadderStart(int MAP[20][MAX], int Select);
void LadderGame();

// Music Player.c
void PrintConsole2();
void Commandmessage();
void _new();
int MusicPlayer(void);

// Puzzle game.c
int get_directionkey();
void print_puzzle(int puzzle[][3]);
int is_ending(int puzzle[][3]);
int PuzzleGame();

//Stillalive.c
void stillalive();