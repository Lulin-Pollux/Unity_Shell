/*다른 "C 소스파일"에서 사용하는 함수들만 모두 여기에 명시해둔다. */

//Common Function.c에 위치함
void gotoxy(short x, short y);
void textcolor(int color_number);
void clearInputBuffer(void);

//Still alive.c에 위치함
void stillalive(void);


/* App에서 쓰이는 함수들 */
/*-------------------------------------------------------------------*/
//Terminal.c에 위치함
void Initializing(void);
void pwd(void);

// ASCII Art Maker.c에 위치함
int ASCIIArtMaker(void);

// Calculator.c에 위치함
void Calculator(void);

// Keyboard.c에 위치함
void Keyboard(void);

// Ladder game.c에 위치함
void LadderGame(void);

// Music Player.c에 위치함
int MusicPlayer(void);

// Puzzle game.c에 위치함
int PuzzleGame(void);
/*-------------------------------------------------------------------*/