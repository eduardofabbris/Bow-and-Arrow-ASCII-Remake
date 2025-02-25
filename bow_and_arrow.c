/* BOW AND ARROW - Ascii Art Remake
 * Made by: Eduardo Fabbris
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //add boolean data type and define "true" and "false"
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <string.h>

//Keys
#define SPACE 32 //32 = space in ascii
#define ESC 27 //27 = esc in ascci
#define UP 72 //72 = H in ascci = arrow up
#define DOWN 80 //80 = P in ascci = arrow down
#define ENTER 13 //13 = return in ASCII 
#define NULL 0

//Special Use
#define SPECIAL_INTERFACE 0

/**********STANDARD PRESETS**********/ 

#define MAX_LEVEL 27
#define FPS_LIMIT 120

//arrow
#define MAX_ARROW_QUANTITY 30
#define ARROW_LEFT_POINTS 50
//balloon
#define BALLOON_QUANTITY 15
#define BALLOON_ARROW_QUANTITY 15
#define BALLOON_POINTS 100
//monster
#define MONSTER_QUANTITY 30
#define MONSTER_ARROW_QUANTITY 30
#define MONSTER_POINTS 200

/**********DIFFICULTY PRESETS**********/

/***********EASY***********/
//archer
#define E_ARCHER_HIT_DELAY 25//ms
//arrow
#define E_ARROW_STAGGER_DELAY 30//ms
#define E_ARROW_HIT_DELAY 250 //ms
//balloon
#define E_BALLOON_STAGGER_DELAY 300
#define E_BALLOON_SCATTERED_DELAY_MAX 300
#define E_BALLOON_SCATTERED_DELAY_MIN 60
//monster
#define E_MONSTER_STAGGER_DELAY 100 //ms
#define E_MONSTER_SPAWN_DELAY 3000 //ms

/**********NORMAL**********/
//archer
#define M_ARCHER_HIT_DELAY 50//ms
//arrow
#define M_ARROW_STAGGER_DELAY 37.5//ms
#define M_ARROW_HIT_DELAY 500 //ms
//balloon
#define M_BALLOON_STAGGER_DELAY 200
#define M_BALLOON_SCATTERED_DELAY_MAX 300
#define M_BALLOON_SCATTERED_DELAY_MIN 40
//monster
#define M_MONSTER_STAGGER_DELAY 50 //ms
#define M_MONSTER_SPAWN_DELAY 2000 //ms

/***********HARD***********/
//archer
#define H_ARCHER_HIT_DELAY 80//ms
//arrow
#define H_ARROW_STAGGER_DELAY 46//ms
#define H_ARROW_HIT_DELAY 1000 //ms
//balloon
#define H_BALLOON_STAGGER_DELAY 150
#define H_BALLOON_SCATTERED_DELAY_MAX 120
#define H_BALLOON_SCATTERED_DELAY_MIN 40
//monster
#define H_MONSTER_STAGGER_DELAY 40 //ms
#define H_MONSTER_SPAWN_DELAY 1500 //ms

/**********CANVAS**********/
#define CANVAS_SKIN_FILE "backgrounds\\game"
#define CANVAS_COLUMNS 81
#define CANVAS_ROWS 35
#define CANVAS_RIGHT_EDGE_Y 80
#define CANVAS_LEFT_EDGE_Y 0
#define CANVAS_UPPER_EDGE_X 0
#define CANVAS_LOWER_EDGE_X 34
#define CANVAS_MIDDLE_EDGE_X 4

/**********ARROW**********/
#define ARROW_SKIN_FILE "skins\\arrow_skin"
#define ARROW_COLUMNS 3
#define ARROW_ROW 1
#define ARROW_RIGHT_LIMIT 77

/**********ARCHER**********/
#define ARCHER_SKIN_FILE "skins\\archer_skin"
#define ARCHER_INITIAL_X 15
#define ARCHER_INITIAL_Y 1
#define ARCHER_UPPER_LIMIT 5
#define ARCHER_LOWER_LIMIT 30
#define ARCHER_COLUMNS 8
#define ARCHER_ROWS 4

/**********BALLOON**********/
#define BALLOON_SKIN_FILE "skins\\balloon_skin"
#define BALLOON_COLUMNS 3
#define BALLOON_ROWS 3
#define BALLOON_UPPER_LIMIT 4
#define BALLOON_LOWER_LIMIT 34
#define BALLOON_ROW_INITIAL_X 26
#define BALLOON_ROW_INITIAL_Y 18

/**********MONSTER**********/
#define MONSTER_SKIN_FILE "skins\\monster_skin"
#define MONSTER_COLUMNS 6
#define MONSTER_ROWS 5
#define MONSTER_UPPER_LIMIT 4
#define MONSTER_LOWER_LIMIT 29
#define MONSTER_RIGHT_LIMIT 79
#define MONSTER_LEFT_LIMIT 1
#define MONSTER_INITIAL_Y 80

/**********ARROW_LEFT_DISPLAY**********/
#define ARROW__LEFT_DISPLAY_X 3
#define ARROW__LEFT_DISPLAY_SYMBOL 25 //alt code 

/**********SCORE DISPLAY**********/
#define SCORE_DISPLAY_X 2
#define SCORE_DISPLAY_Y 8
#define HIGHSCORE_DISPLAY_X 3
#define HIGHSCORE_DISPLAY_Y 13

/**********HIGH SCORES PROMPT**********/
#define HIGH_SCORES_PROMPT_ROWS 7
#define HIGH_SCORES_PROMPT_COLUMNS 37
#define HIGH_SCORES_PROMPT_X 10
#define HIGH_SCORES_PROMPT_Y 24
#define HIGH_SCORES_PROMPT_FILE "prompts\\highscores_prompt"

/**********GAMEOVER PROMPT**********/
#define GAMEOVER_PROMPT_ROWS 15
#define GAMEOVER_PROMPT_COLUMNS 65
#define GAMEOVER_PROMPT_X 7
#define GAMEOVER_PROMPT_Y 8
#define GAMEOVER_PROMPT_FILE "prompts\\gameover_prompt"

/**********QUITGAME PROMPT**********/
#define QUITGAME_PROMPT_ROWS 7
#define QUITGAME_PROMPT_COLUMNS 37
#define QUITGAME_PROMPT_X 10
#define QUITGAME_PROMPT_Y 24
#define QUITGAME_PROMPT_FILE "prompts\\quitgame_prompt"

/**********HIGHSCORES MENU**********/
#define HIGHSCORES_MENU_ROWS 14
#define HIGHSCORES_MENU_COLUMNS 53
#define HIGHSCORES_MENU_X 7
#define HIGHSCORES_MENU_Y 14
#define HIGHSCORES_MENU_FILE "backgrounds\\highscores_menu"

/**********HIGHSCORES SAVE FILE**********/
#define HIGHSCORES_MAX_PLAYER_NAME 40
#define HIGHSCORES_MAX_SAVED_SCORES 5
#define HIGHSCORES_FILE "highscores"

/**********OPTIONS MENU**********/
#define OPTIONS_MENU_ROWS 21
#define OPTIONS_MENU_COLUMNS 70
#define OPTIONS_MENU_X 7
#define OPTIONS_MENU_Y 6
#define ARROW_OPTIONS_MENU_INITIAL_X 12
#define ARROW_OPTIONS_MENU_INITIAL_Y 20
#define ARROW_OPTIONS_MENU_UPPER_LIMIT_X 12
#define ARROW_OPTIONS_MENU_BOTTOM_LIMIT_X 19
#define OPTIONS_MENU_FILE "backgrounds\\options_menu"

/**********MAIN MENU**********/
#define MAIN_MENU_COLUMNS 81
#define MAIN_MENU_ROWS 35
#define ARROW_MAIN_MENU_INITIAL_POSITION_X 17
#define ARROW_MAIN_MENU_INITIAL_POSITION_Y 34
#define ARROW_MAIN_MENU_UPPER_LIMIT_X 17
#define ARROW_MAIN_MENU_BOTTOM_LIMIT_X 20 
#define ARROW_MENU_COLUMNS 2
#define MAIN_MENU_FILE "backgrounds\\main_menu"

/***************************************************************************/
//level type
    enum levelType{ balloonLevel = 1,
                    monsterLevel,
                    balloonScatteredLevel };

#define N_LEVEL_TYPES 3

//difficulty
enum difficulty{ easy,
                 normal,
                 hard };

//themes
    enum theme{ light,
                vanilla,
                dark,
                matrix };

//symbol
    enum symbolType{ symbArrow, 
                    symbX };


/***************************************************************************/

    typedef struct fpsLimit{
        double delay;
        int frames;
        LONGLONG startTimeDelay, startTimeOneSecod;
    } FPSLIMIT;

    typedef struct preSets{
        enum levelType levelType;
        //arrow
        short arrowQuantity;
        short arrowStaggerDelay, arrowHitDelay;
        bool  arrowConsumableArrows;
        //archer
        short archerHitDelay;
        //balloon
        short balloonInitialX;
        short balloonStaggerDelay;
        short balloonScatteredDelayMax, balloonScatteredDelayMin;
        //monster
        short monsterStaggerDelay, monsterSpawnDelay;
    } PRESETS;


    typedef struct HighScores{
        struct playerData{
            char name[HIGHSCORES_MAX_PLAYER_NAME];
            int score;
        } player[HIGHSCORES_MAX_SAVED_SCORES];
        int index;
        
    } HIGHSCORES;

    typedef struct entityPlayer{
        char name[HIGHSCORES_MAX_PLAYER_NAME];
        int score;
        enum difficulty difficulty;
        enum theme theme;
        int level;
        bool gameOver, levelOver;
        int arrowsLeft, balloonsDestroyed, monstersKilled;
    } PLAYER;

	typedef struct entityArcher {
        bool active, keyHitLimit;
        int x, y;
        LONGLONG startTimeKeyHitLimit;
	} ARCHER;
	
	typedef struct entityArrow {
		bool active[MAX_ARROW_QUANTITY];
        bool stagger, keyHitLimit;
        int x[MAX_ARROW_QUANTITY], y[MAX_ARROW_QUANTITY];
        int index, activeIndex;
        LONGLONG startTimeStagger, startTimeKeyHitLimit;
	} ARROW;

    typedef struct entityBalloon {
        bool active[BALLOON_QUANTITY];
        bool stagger, individualStagger[BALLOON_QUANTITY];
        int x[BALLOON_QUANTITY], y[BALLOON_QUANTITY];
        int activeIndex;
        int IndividualDelay[BALLOON_QUANTITY];
        LONGLONG startTimeStagger, startTimeIndividualStagger[BALLOON_QUANTITY];
    } BALLOON;

    typedef struct entityMonster {
        bool active[MONSTER_QUANTITY];
        bool stagger, spawn;
        int x[MONSTER_QUANTITY], y[MONSTER_QUANTITY];
        int index, activeIndex;
        LONGLONG startTimeStagger, startTimeSpawn;
    } MONSTER;

    typedef struct entitySkin{
        char archer[ARCHER_ROWS * ARCHER_COLUMNS];
        char arrow[ARROW_ROW * ARROW_COLUMNS];
        char balloon[BALLOON_ROWS * BALLOON_COLUMNS];
        char monster[MONSTER_ROWS * MONSTER_COLUMNS];
    } SKIN;

	typedef struct Backgrounds{
		char mainMenu[MAIN_MENU_ROWS * MAIN_MENU_COLUMNS];
		char optionsMenu[OPTIONS_MENU_ROWS * OPTIONS_MENU_COLUMNS];
		char game[CANVAS_ROWS * CANVAS_COLUMNS];
        char highScores[HIGHSCORES_MENU_ROWS * HIGHSCORES_MENU_COLUMNS];
	} BACKGROUND;

    typedef struct Prompts{
        char highScoresPrompt[HIGH_SCORES_PROMPT_ROWS * HIGH_SCORES_PROMPT_COLUMNS];
        char gameoverPrompt[GAMEOVER_PROMPT_ROWS * GAMEOVER_PROMPT_COLUMNS];
        char quitGamePrompt[QUITGAME_PROMPT_ROWS * QUITGAME_PROMPT_COLUMNS];
    } PROMPT;

/********************************************FUNCTION DECLARATION********************************************/
/*******SPECIAL FUNCTIONS*******/
void specialInterface(ARROW arrow, BALLOON balloon, MONSTER monster, bool printTags);
void gotoxy(int x,int y);
void showCursor(bool x);

/*******FILE FUNCTIONS*******/
bool readTxtFiles(char matrixObject[], int columns, char txtFileName[]);
bool loadFiles();
bool readHighScores();
void writeHightScores();

/*******MENU/PROMPT FUNCTIONS*******/
int symbolMenuMovement(int initialX, int initialY, int upperLimitX, int bottomLimitX, int leap, enum symbolType symbol);
void mainMenu();
void optionsMenu();
void highscoresMenu();
bool highscoresPrompt();
void rearrangeScores();
LONGLONG setQuitGamePrompt(char prompt[]);
void setGameOver(char prompt[]);
/********PRINT FUNCTIONS*******/
void printBackground(char background[], int rows, int columns, int startRow, int StartColumn);
void printPrompt(char prompt[], int rows, int columns, int startRow, int startColumn, bool clean);
void printSymbolMenu(bool clean, int x, int y, enum symbolType symbol);
void printNumberInGame(int value, int x, int y, char format[4]);
void printStringInGame(char string[15], int x, int y);
void draw();
/*******TIME FUNCTIONS*******/
double timeDiff(LONGLONG startTime);
bool keyHitControl(LONGLONG startTime, double delay);
bool staggerControl(LONGLONG *startTime, double delay);
void staggerControlScatteredBalloon(BALLOON *balloon);

/*******GAME FUNCTIONS*******/
void gameLoop();
//game screen
void show(ARCHER *archer, ARROW *arrow, BALLOON *balloon, MONSTER *monster);
//movement
void update(ARCHER *archer, ARROW *arrow, BALLOON *balloon, MONSTER *monster);
//level and difficulty
void setLevelPreset();
void setDifficultyPreset();
//archer
bool hitArcherDetector(ARCHER *archer, MONSTER *monster);
void archerMovUp(ARCHER *archer);
void archerMovDown(ARCHER *archer);
//arrow
void arrowShoot(ARCHER archer, ARROW *arrow);
//balloon
void setBalloonFirstRowPosition(BALLOON *balloon);
void setBalloon(BALLOON *balloon, int  i, int startRow, int endRow, bool clean);
void hitBalloonDetector(ARROW *arrow, BALLOON *balloon);
void setBalloonScatteredPostition(BALLOON *balloon);
//monster
void hitMonsterDetector(ARROW *arrow, MONSTER *monster);
void setMonsterFirstPosition(MONSTER *monster);
void setMonster(MONSTER *monster, int i, int startColumn, int endColumn, bool clean);
bool spawnRateMonster(MONSTER *monster, double delay);

/***************************************************************************/
//GLOBAL VARIABLES
char gameLayer[CANVAS_ROWS][CANVAS_COLUMNS];
HIGHSCORES highScore;
SKIN skin;
BACKGROUND backGround;
PROMPT prompt;
FPSLIMIT fps = { .delay = (1000/(double)FPS_LIMIT), //ms
                 .frames = NULL,
                 .startTimeDelay = NULL, 
                 .startTimeOneSecod = NULL };

PLAYER player = {   .name = {NULL},
                    .score = NULL,
                    .difficulty = normal,
                    .theme = vanilla,
                    .level = 1,
                    .gameOver = false,
                    .levelOver = false, 
                    .arrowsLeft = NULL, 
                    .balloonsDestroyed = NULL, 
                    .monstersKilled = NULL };
PRESETS preset;

int main(void){
	if(loadFiles()){
        system("MODE con cols=82 lines=36"); 
        readHighScores();
        //MENU
        mainMenu();
    }
	return 0;
}

bool loadFiles(){
	if( !readTxtFiles(backGround.optionsMenu, OPTIONS_MENU_COLUMNS, OPTIONS_MENU_FILE) ||
        !readTxtFiles(backGround.mainMenu, MAIN_MENU_COLUMNS, MAIN_MENU_FILE) ||
        !readTxtFiles(backGround.highScores, HIGHSCORES_MENU_COLUMNS, HIGHSCORES_MENU_FILE) ||
        !readTxtFiles(backGround.game, CANVAS_COLUMNS, CANVAS_SKIN_FILE) ||
        !readTxtFiles(skin.archer, ARCHER_COLUMNS, ARCHER_SKIN_FILE) ||
        !readTxtFiles(skin.arrow, ARROW_COLUMNS, ARROW_SKIN_FILE) ||
        !readTxtFiles(skin.balloon, BALLOON_COLUMNS, BALLOON_SKIN_FILE) ||
        !readTxtFiles(skin.monster, MONSTER_COLUMNS, MONSTER_SKIN_FILE) || 
        !readTxtFiles(prompt.highScoresPrompt, HIGH_SCORES_PROMPT_COLUMNS, HIGH_SCORES_PROMPT_FILE) ||
        !readTxtFiles(prompt.gameoverPrompt, GAMEOVER_PROMPT_COLUMNS, GAMEOVER_PROMPT_FILE) ||
        !readTxtFiles(prompt.quitGamePrompt, QUITGAME_PROMPT_COLUMNS, QUITGAME_PROMPT_FILE) ){
		
		return false;
	}
    return true;
}

bool readHighScores(){
	FILE *pont_arq;
    char buf[100];
	int i=0;

    snprintf(buf, sizeof(buf),"save\\\\%s.bin", HIGHSCORES_FILE);
	pont_arq = fopen(buf, "rb");
	
    if(pont_arq){
		while(!feof(pont_arq)){ 
			if(fread(&highScore.player[i], sizeof(highScore.player[NULL]), 1, pont_arq)){
                i++;
			}
		}
		fclose(pont_arq);
        highScore.index = i;
	}
	else{
        system("cls");
        gotoxy(0,0);
        printf("Error in the reading of: %s.bin\n", HIGHSCORES_FILE);
        printf("Press ENTER to continue...\n");
        getchar();
        return false;
	}
	return true; 
}

void writeHightScores(){
	FILE *pont_arq;
    char buf[100];
	int i;
	
    snprintf(buf, sizeof(buf),"save\\\\%s.bin", HIGHSCORES_FILE);
	pont_arq = fopen(buf, "wb");
	if(pont_arq){
		for(i = 0; i < highScore.index; i++){
			fwrite(&highScore.player[i], sizeof(highScore.player[NULL]), 1, pont_arq); 
		}
		fclose(pont_arq);
	}
	else{
        system("cls");
        gotoxy(0,0);
        printf("Error in saving: %s.bin\n", HIGHSCORES_FILE);
        printf("Press ENTER to continue...\n");
        getchar();
	}
}

void highscoresMenu(){

    system("cls");
    printBackground(backGround.highScores, HIGHSCORES_MENU_ROWS, HIGHSCORES_MENU_COLUMNS, HIGHSCORES_MENU_X, HIGHSCORES_MENU_Y);
        for(int i = 0; i < highScore.index; i++){
            gotoxy((HIGHSCORES_MENU_X + 5) + i, HIGHSCORES_MENU_Y + 9); printf("%s", highScore.player[i].name);
            gotoxy((HIGHSCORES_MENU_X + 5) + i, HIGHSCORES_MENU_Y + 39); printf("%07i", highScore.player[i].score);
        }

    char key = NULL;
    fflush(stdin);
    do{
        key = getch();
    } while(key != ESC);
}
//verify if the player score is greater than the ones in the highscores and print prompt
bool highscoresPrompt(){
    bool print = false;
    if(highScore.index < HIGHSCORES_MAX_SAVED_SCORES) highScore.index++;

    for(int i=0; i < highScore.index; i++){
        if(player.score > highScore.player[i].score){
            print = true; break;
        }
    }
     
    if(print){
        system("cls");
        printPrompt(prompt.highScoresPrompt, HIGH_SCORES_PROMPT_ROWS, HIGH_SCORES_PROMPT_COLUMNS, HIGH_SCORES_PROMPT_X, HIGH_SCORES_PROMPT_Y, false);
        gotoxy((HIGH_SCORES_PROMPT_X + 4), (HIGH_SCORES_PROMPT_Y +16) );
        fflush(stdin);
        fgets(player.name, HIGHSCORES_MAX_PLAYER_NAME, stdin);
        player.name[strlen(player.name)-1] = '\0'; //take out the \n
        return true;
    }
    return false;
}
//update highscores
void rearrangeScores(){
    int i;
    for(i=0 ; i < highScore.index ; i++){ //starts from the greater score
        if(player.score > highScore.player[i].score){
            //pull everyone one down starting from the end
            for(int j=(highScore.index-1); j > i ; j--){
                strcpy(highScore.player[j].name, highScore.player[j-1].name);
                highScore.player[j].score = highScore.player[j-1].score; 
            }
            break;
        }
    }
    //replace score
    strcpy(highScore.player[i].name, player.name);
    highScore.player[i].score = player.score;    
}

void gotoxy (int y, int x){ //posiciona o cursor
		COORD coord = {0, 0};
		coord.X = x; coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}

void showCursor(bool condition){ //esconde ou mostra o cursor
	if(condition == false){
		CONSOLE_CURSOR_INFO cursor = {1, false};
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
	}
	else{
		CONSOLE_CURSOR_INFO cursor = {1, true};
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
	}
}

void printSymbolMenu(bool clean, int x, int y, enum symbolType symbol){
	
    switch(symbol){
        case symbArrow:{
            char arrow[ARROW_MENU_COLUMNS] = "->";
            int i;
            gotoxy(x, y);
            if(clean){
                for(i = 0; i < ARROW_MENU_COLUMNS; i++){
                    printf(" ");
                }
            }
            else{ //clean = false
                for(i = 0; i < ARROW_MENU_COLUMNS; i++){
                    printf("%c", arrow[i]);
                }
            }
        } break;

        case symbX:{
            char symbolX = 'X';
            gotoxy(x, y);
            if(clean){
                printf(" ");
            }
            else{ //clean = false
                printf("%c", symbolX);
            }
        } break;
    }

}

int symbolMenuMovement(int initialX, int initialY, int upperLimitX, int bottomLimitX, int leap, enum symbolType symbol){
	char key = NULL;

	int i = initialX;
	int j = initialY;
    //print initial position
    if(symbol == symbArrow) printSymbolMenu(false, i, j, symbArrow);//arrow 

    //menu movement
    fflush(stdin);
	while(key != ENTER){
		if(kbhit()){ 
			key = getch();
            //clean symbol
            if(symbol == symbArrow) printSymbolMenu(true, i, j, symbArrow);
            else if(symbol == symbX) printSymbolMenu(true, i, j, symbX);
            //update the coords
			switch (key){
                case 'w': case 'W': case UP:{
					if(i > upperLimitX ){ //height limit
						i -= leap; //up 1
					}
					else{ // i = upperLimitX
						i = bottomLimitX;
					}
				} break;
                case 's': case 'S': case DOWN:{
					if(i < bottomLimitX){ //bottom limit 
						i += leap; //down 1
					}
					else{ // i = bottomLimitX
						i = upperLimitX;
					}
				} break;
                case ESC: return ESC; 
			}
            //reprint symbol
            if(symbol == symbArrow) printSymbolMenu(false, i, j, symbArrow);
            else if(symbol == symbX) printSymbolMenu(false, i, j, symbX);

		} 
		
	}
	
    //clean final position after the selection
    if(symbol == symbArrow) printSymbolMenu(true, i, j, symbArrow);//arrow 
	
	return ((i - upperLimitX)/leap); //return the option starting at 0
}

void printBackground(char background[], int rows, int columns, int startRow, int StartColumn){

	system("cls"); 	
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			if(background[ (i * columns) + j] != '\0'){
				gotoxy((i + startRow),(j + StartColumn));
				printf("%c", background[ (i * columns) + j]);
			}
		}
	}
}

/*************************@MAIN_MENU_CODE**************************************/
void mainMenu(){
	bool endMenu = false;
	int option;
	showCursor(false);
	

	while (!endMenu){
		printBackground(backGround.mainMenu  , MAIN_MENU_ROWS, MAIN_MENU_COLUMNS, 0, 0);
		option = symbolMenuMovement(ARROW_MAIN_MENU_INITIAL_POSITION_X, ARROW_MAIN_MENU_INITIAL_POSITION_Y, ARROW_MAIN_MENU_UPPER_LIMIT_X, ARROW_MAIN_MENU_BOTTOM_LIMIT_X, 1, symbArrow);
		
		switch(option){
			case 0:{ //play
				gameLoop();
			} break;
			case 1:{ //options
                optionsMenu();
			} break;
			case 2:{ //best scores
                highscoresMenu();				
			} break;
			case 3: case ESC: {// quit 
				gotoxy(35, 1); //in case of appearing a terminal message 
				endMenu = true;
			}
		}
	} 

} 

void optionsMenu(){
    enum difficulty difficulty;
    enum theme theme;
    bool endMenu = false;
    int option, initialX1, initialX2;
    

    while(!endMenu){
        printBackground(backGround.optionsMenu, OPTIONS_MENU_ROWS, OPTIONS_MENU_COLUMNS, OPTIONS_MENU_X, OPTIONS_MENU_Y);
        //print the already set difficulty or theme
        switch(player.difficulty){
            case easy: initialX1 = 12; printSymbolMenu(false, initialX1, 38, symbX); break;
            case normal: initialX1 = 14; printSymbolMenu(false, initialX1, 38, symbX); break;
            case hard: initialX1 = 16; printSymbolMenu(false, initialX1, 38, symbX); break;
        }
        switch(player.theme){
            case light: initialX2 = 19; printSymbolMenu(false, initialX2, 38, symbX); break;
            case vanilla: initialX2 = 21; printSymbolMenu(false, initialX2, 38, symbX); break;
            case dark: initialX2 = 23; printSymbolMenu(false, initialX2, 38, symbX); break;
            case matrix: initialX2 = 25; printSymbolMenu(false, initialX2, 38, symbX); break;
        }
        //gets the selection between difficulty and theme       
        option = symbolMenuMovement(ARROW_OPTIONS_MENU_INITIAL_X, ARROW_OPTIONS_MENU_INITIAL_Y, ARROW_OPTIONS_MENU_UPPER_LIMIT_X, ARROW_OPTIONS_MENU_BOTTOM_LIMIT_X, 7, symbArrow);
        switch(option){ 
            case 0: {
                //gets the selection of difficulty 
                difficulty = symbolMenuMovement(initialX1, 38, 12, 16, 2, symbX);
                switch(difficulty){
                    case easy: player.difficulty = easy; break; //x= 12, y=38
                    case normal: player.difficulty = normal; break;// x=14, y=38
                    case hard: player.difficulty = hard; break;// x=16, y=38
                }
            } break;
            case 1: {
                //gets the selection of theme
                theme = symbolMenuMovement(initialX2, 38, 19, 25, 2,symbX);
                switch(theme){	
                    case light: system("Color 71"); player.theme = light; break;//light //x=19, y=38
                    case vanilla: system("Color 07"); player.theme = vanilla; break; //vanilla //x=21, y=38
                    case dark: system("color 06"); player.theme = dark; break; //dark //x=23, y=38
                    case matrix: system("Color 0A"); player.theme = matrix; break; //martix //x=25, y=38
                }
            } break;
            case ESC: endMenu = true; break;
        }
    }
}


/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
                                    @GAME_PRINCIPAL_CODE
 */ 
//note: if you have '\0' in your matrix, it's not going to do spaces!! <- use gotoxy

void gameLoop(){
    int key = NULL;
    LARGE_INTEGER t;

    static ARCHER archer = {.active = true,
                            .keyHitLimit = false,
                            .x = ARCHER_INITIAL_X,
                            .y = ARCHER_INITIAL_Y, 
                            .startTimeKeyHitLimit = NULL };

    ARROW arrow = { .active = {false},
                    .stagger = false,
                    .keyHitLimit = false,
                    .x = {NULL},
                    .y = {NULL},
                    .index = NULL,
                    .activeIndex = NULL,
                    .startTimeStagger = NULL,
                    .startTimeKeyHitLimit = NULL };

    BALLOON balloon = { .active = {false}, 
                        .stagger  = false,
                        .individualStagger = {false}, 
                        .x = {NULL}, 
                        .y = {NULL}, 
                        .activeIndex = NULL,
                        .IndividualDelay = {NULL}, 
                        .startTimeStagger = NULL, 
                        .startTimeIndividualStagger = {NULL} };
    
    MONSTER monster = { .active = {NULL},
                        .stagger = false,
                        .spawn = false,
                        .x = {NULL},
                        .y = {NULL},
                        .index = NULL,
                        .activeIndex = NULL,
                        .startTimeStagger = NULL,
                        .startTimeSpawn = NULL };
    
    
    //just need to execute one time
    if(player.level == 1){ 
        //reset archer position and state
        archer.active = true; 
        archer.x = ARCHER_INITIAL_X; 
        archer.y = ARCHER_INITIAL_Y;

        printBackground(backGround.game, CANVAS_ROWS, CANVAS_COLUMNS, 0, 0);
        printNumberInGame(highScore.player[0].score, HIGHSCORE_DISPLAY_X, HIGHSCORE_DISPLAY_Y, "%06i");
    }
    printNumberInGame(player.score, SCORE_DISPLAY_X, SCORE_DISPLAY_Y, "%06i");
    printNumberInGame(player.level, 2, 39, "%03i"); //print the level number
    setLevelPreset();

    //SPECIAL INTERFACE
    #if SPECIAL_INTERFACE
        specialInterface(arrow, balloon, monster, true);
    #else //print arrows left
        for(int i=0; i < MAX_ARROW_QUANTITY; i++){ //erase arrows left
            gameLayer[ARROW__LEFT_DISPLAY_X][((CANVAS_RIGHT_EDGE_Y-1)-MAX_ARROW_QUANTITY)+ i] = ' ';
        }

        for(int i=0; i < preset.arrowQuantity; i++){ //print arrows left
            gameLayer[ARROW__LEFT_DISPLAY_X][((CANVAS_RIGHT_EDGE_Y-1)-preset.arrowQuantity)+ i] = ARROW__LEFT_DISPLAY_SYMBOL;
        }
    #endif

    QueryPerformanceCounter(&t); //take first time
    switch(preset.levelType){
        case balloonLevel: {
            setBalloonFirstRowPosition(&balloon);
            balloon.startTimeStagger = t.QuadPart; 
        } break;
        case monsterLevel: {
            setMonsterFirstPosition(&monster);
            monster.startTimeSpawn = t.QuadPart;
        } break;
        case balloonScatteredLevel: {
            setBalloonScatteredPostition(&balloon);
            for(int i=0; i < BALLOON_QUANTITY; i++){
                balloon.startTimeIndividualStagger[i] = t.QuadPart;
            }
        } break;
    }

    //time
    #if SPECIAL_INTERFACE
        fps.startTimeOneSecod = t.QuadPart;
    #endif
    fps.startTimeDelay = arrow.startTimeStagger = t.QuadPart;
    //getchar();
    while(!player.gameOver && !player.levelOver) {
        show(&archer, &arrow, &balloon, &monster);
 
        if(kbhit()){
            key = getch();
            
            switch(key){
                case 'w': case 'W': case UP: archerMovUp(&archer); break;
                case 's': case 'S': case DOWN: archerMovDown(&archer); break;
                case SPACE: arrowShoot(archer, &arrow); break;
                case ESC:{
                    //PAUSE MENU
                    LONGLONG spentTime;
                    spentTime =  setQuitGamePrompt(prompt.quitGamePrompt);
                    //update time
                    arrow.startTimeKeyHitLimit += spentTime;   
                    switch(preset.levelType){
                        case monsterLevel: monster.startTimeSpawn += spentTime; break;
                    }
                }  break;
            }   
        }
        
        //TIME CONTROL
        archer.keyHitLimit = keyHitControl(archer.startTimeKeyHitLimit, preset.archerHitDelay);
        arrow.stagger = staggerControl(&arrow.startTimeStagger, preset.arrowStaggerDelay);
        arrow.keyHitLimit = keyHitControl(arrow.startTimeKeyHitLimit, preset.arrowHitDelay);
        switch(preset.levelType){
            case balloonLevel: {
                balloon.stagger = staggerControl(&balloon.startTimeStagger, preset.balloonStaggerDelay);
            } break;
            case monsterLevel:{
                monster.stagger = staggerControl(&monster.startTimeStagger, preset.monsterStaggerDelay);
                spawnRateMonster(&monster, preset.monsterSpawnDelay);
            }break;
            case balloonScatteredLevel: {
                staggerControlScatteredBalloon(&balloon);
            }
        } 

        //SPECIAL INTERFACE
        #if SPECIAL_INTERFACE 
            specialInterface(arrow, balloon, monster, false);
        #endif    
        
    }
    player.arrowsLeft += (preset.arrowQuantity - arrow.index);
    player.score += (player.arrowsLeft * ARROW_LEFT_POINTS);
    //LEVELS
    if(!player.gameOver){    
        player.level++;
        player.levelOver = false;
        if(player.level <= MAX_LEVEL){
            gameLoop();
        }
    }
    else{
        setGameOver(prompt.gameoverPrompt); //reset player status
        if(highscoresPrompt()){
            rearrangeScores();
            writeHightScores();
        }
        player.score = NULL; //reset player score
        fflush(stdin);
    }
}

void printPrompt(char prompt[], int rows, int columns, int startRow, int startColumn, bool clean){
	
    if(!clean){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                gotoxy((i + startRow),(j + startColumn));
                printf("%c", prompt[ (i * columns) + j]);
            }
        }
    }
    else{
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                gotoxy((i + startRow),(j + startColumn));
                printf(" ");
            }
        }     
    }
}

LONGLONG setQuitGamePrompt(char prompt[]){
    LARGE_INTEGER t;
    LONGLONG startTime, endTime;
    
    QueryPerformanceCounter(&t);//gets the start clocks
    startTime = t.QuadPart;

    printPrompt(prompt, QUITGAME_PROMPT_ROWS, QUITGAME_PROMPT_COLUMNS, QUITGAME_PROMPT_X, QUITGAME_PROMPT_Y, false);
    char key = NULL;
    fflush(stdin);
    do{
        key = getch();
    } while(key != ENTER && key != ESC);
    
    switch(key){
        case ENTER: player.gameOver = true; break;
        case ESC: printPrompt(NULL, QUITGAME_PROMPT_ROWS, QUITGAME_PROMPT_COLUMNS, QUITGAME_PROMPT_X, QUITGAME_PROMPT_Y, true); break;
    }

    QueryPerformanceCounter(&t);
    endTime = t.QuadPart;

    //return the ticks spend in pause
    return (endTime - startTime);
}

void setGameOver(char prompt[]){
    system("cls");
    //balloon
    printPrompt(prompt, GAMEOVER_PROMPT_ROWS, GAMEOVER_PROMPT_COLUMNS, GAMEOVER_PROMPT_X, GAMEOVER_PROMPT_Y, false);
    gotoxy(11,41); printf("%03i", player.balloonsDestroyed);
    gotoxy(11,47); printf("%03i", BALLOON_POINTS);
    gotoxy(11,53); printf("%06i", player.balloonsDestroyed * BALLOON_POINTS);
    //monster
    gotoxy(13,41); printf("%03i", player.monstersKilled);
    gotoxy(13,47); printf("%03i", MONSTER_POINTS);
    gotoxy(13,53); printf("%06i", player.monstersKilled * MONSTER_POINTS);
    //arrows
    gotoxy(15,41); printf("%03i", player.arrowsLeft);
    gotoxy(15,47); printf("%03i", ARROW_LEFT_POINTS);
    gotoxy(15,53); printf("%06i", player.arrowsLeft * ARROW_LEFT_POINTS);
    //total score
    gotoxy(17,36); printf("%06i", player.score);
    
    //RESET PLAYER STATUS
    player.level = 1;
    player.gameOver = false;
    player.levelOver = false;
    player.balloonsDestroyed = NULL;
    player.monstersKilled = NULL;
    player.arrowsLeft = NULL;

    memset(gameLayer, '\0', sizeof(gameLayer)); //clean gameLayer

    char key = NULL;
    fflush(stdin);
    do{
        key = getch();
    } while(key != ENTER);

}

void setLevelPreset(){
    static int nBalloonLevel, nMonsterLevel, nBalloonScatteredLevel;

    if(player.level == 1){ //Reset
        nBalloonLevel = 0;
        nMonsterLevel = 0;
        nBalloonScatteredLevel = 0;
    }

    setDifficultyPreset(); //set the start status based on the difficulty
    for(int i=0; i <= (MAX_LEVEL-N_LEVEL_TYPES); i+=N_LEVEL_TYPES){
        if(player.level == (i+1)){ //BALLOON LEVEL
            preset.levelType = balloonLevel;
            if(nBalloonLevel == 0){
                preset.balloonInitialX = BALLOON_ROW_INITIAL_X;
            } 
            else{
                preset.balloonInitialX = BALLOON_LOWER_LIMIT;   
            }
            preset.balloonStaggerDelay -= nBalloonLevel*5;
            preset.arrowHitDelay += nBalloonLevel*5;
            preset.archerHitDelay += nBalloonLevel*5;
            nBalloonLevel++;
            break;
        }
        else if(player.level == (i+2)){ //MONSTER LEVEL
            preset.levelType = monsterLevel;
            preset.monsterStaggerDelay -= nMonsterLevel*5;
            preset.arrowHitDelay += nMonsterLevel*5;
            preset.archerHitDelay += nMonsterLevel*5;
            nMonsterLevel++;
            break;
        }
        else if(player.level == (i+3)){ //SCATTERED BALLOON LEVEL
            preset.levelType = balloonScatteredLevel;
            preset.balloonInitialX = BALLOON_LOWER_LIMIT;
            preset.balloonScatteredDelayMax -= nBalloonScatteredLevel*5;
            preset.balloonScatteredDelayMin -= nBalloonScatteredLevel*5;
            preset.arrowHitDelay += nBalloonScatteredLevel*5;
            preset.archerHitDelay += nBalloonScatteredLevel*5;
            nBalloonScatteredLevel++;
            break;
        }
    }

    switch(preset.levelType){
        case balloonLevel: case balloonScatteredLevel:{
            preset.arrowConsumableArrows = false;
            preset.arrowQuantity = BALLOON_ARROW_QUANTITY;
        } break;
        case monsterLevel:{
            preset.arrowConsumableArrows = true;
            preset.arrowQuantity = MONSTER_ARROW_QUANTITY;
        } break;
    }
}

void setDifficultyPreset(){

    switch(player.difficulty){
        case easy: {
            preset.archerHitDelay = E_ARCHER_HIT_DELAY;
            preset.arrowHitDelay = E_ARROW_HIT_DELAY;
            preset.arrowStaggerDelay = E_ARROW_STAGGER_DELAY;
            preset.balloonStaggerDelay = E_BALLOON_STAGGER_DELAY;
            preset.balloonScatteredDelayMax = E_BALLOON_SCATTERED_DELAY_MAX;
            preset.balloonScatteredDelayMin = E_BALLOON_SCATTERED_DELAY_MIN;
            preset.monsterStaggerDelay = E_MONSTER_STAGGER_DELAY;
            preset.monsterSpawnDelay = E_MONSTER_SPAWN_DELAY;
            printStringInGame("Easy", 1, 8);
        } break;
        case normal:{
            preset.archerHitDelay = M_ARCHER_HIT_DELAY;
            preset.arrowHitDelay = M_ARROW_HIT_DELAY;
            preset.arrowStaggerDelay = M_ARROW_STAGGER_DELAY;
            preset.balloonStaggerDelay = M_BALLOON_STAGGER_DELAY;
            preset.balloonScatteredDelayMax = M_BALLOON_SCATTERED_DELAY_MAX;
            preset.balloonScatteredDelayMin = M_BALLOON_SCATTERED_DELAY_MIN;
            preset.monsterStaggerDelay = M_MONSTER_STAGGER_DELAY;
            preset.monsterSpawnDelay = M_MONSTER_SPAWN_DELAY;
            printStringInGame("Normal", 1, 8);

        } break;
        case hard:{
            preset.archerHitDelay = H_ARCHER_HIT_DELAY;
            preset.arrowHitDelay = H_ARROW_HIT_DELAY;
            preset.arrowStaggerDelay = H_ARROW_STAGGER_DELAY;
            preset.balloonStaggerDelay = H_BALLOON_STAGGER_DELAY;
            preset.balloonScatteredDelayMax = H_BALLOON_SCATTERED_DELAY_MAX;
            preset.balloonScatteredDelayMin = H_BALLOON_SCATTERED_DELAY_MIN;
            preset.monsterStaggerDelay = H_MONSTER_STAGGER_DELAY;
            preset.monsterSpawnDelay = H_MONSTER_SPAWN_DELAY;
            printStringInGame("Hard", 1, 8);
        } break;
    }
}

void specialInterface(ARROW arrow, BALLOON balloon, MONSTER monster, bool printTags){
    
    if(printTags){
        showCursor(true);
        gotoxy(3,68); printf("FPS:");
        gotoxy(1,46); printf("Active Balloons:");
        gotoxy(2,46); printf("Active Monsters:");
        gotoxy(3,46); printf("Active Arrows:");
        gotoxy(1,23); printf("Arrows:");
        gotoxy(2,23); printf("Monsters:");
    }

    //active balloons
    printNumberInGame(balloon.activeIndex, 1, 62, "%02i");

    //active arrows
    printNumberInGame(arrow.activeIndex, 3, 60, "%02i");

    //active monsters
    printNumberInGame(monster.activeIndex, 2, 62, "%02i");

    //arrows left
    int arrowLeft = (preset.arrowQuantity - arrow.index);
    printNumberInGame(arrowLeft, 1, 30, "%02i");

    //monsters left
    int monsterLeft = (MONSTER_QUANTITY - monster.index);
    printNumberInGame(monsterLeft, 2, 32, "%02i");

}

void show(ARCHER *archer, ARROW *arrow, BALLOON *balloon, MONSTER *monster){
    LARGE_INTEGER t1;

    switch(preset.levelType){
        case balloonLevel: case balloonScatteredLevel: {
            hitBalloonDetector(&(*arrow), &(*balloon));
        } break;
        case monsterLevel:{
            hitMonsterDetector(&(*arrow), &(*monster));
            player.gameOver = hitArcherDetector(&(*archer), &(*monster));
        } break;
    }
    //update actions in game
    update(&(*archer), &(*arrow), &(*balloon), &(*monster));

    //FPS CONTROL to print screen    
    if(timeDiff(fps.startTimeDelay) >= fps.delay){ 
        QueryPerformanceCounter(&t1); //has to be the first, draw consumes time!
        #if SPECIAL_INTERFACE
            fps.frames++;
        #endif
        draw(); //print game screen
        memset(gameLayer, '\0', sizeof(gameLayer)); //clean gameLayer

        fps.startTimeDelay = t1.QuadPart;
    }
    #if SPECIAL_INTERFACE
        if(timeDiff(fps.startTimeOneSecod)  >= 1000){
            QueryPerformanceCounter(&t1);
            //print fps
            
            printNumberInGame(fps.frames, 3, 73, "%04i");
            fps.frames = 0; 
            fps.startTimeOneSecod = t1.QuadPart;
        }
    #endif
}

void update(ARCHER *archer, ARROW *arrow, BALLOON *balloon, MONSTER *monster){
//entities movement

/*************************ARROW*************************/
    if(arrow->activeIndex > 0 && !arrow->stagger){
        for(int i=0; i < arrow->index; i++){ 
            if(arrow->active[i] && (arrow->y[i] < ARROW_RIGHT_LIMIT ) ){
                gameLayer[arrow->x[i]][arrow->y[i]] = ' ';
                arrow->y[i]++;
                
                for(int j=0; j < ARROW_COLUMNS; j++){
                    gameLayer[arrow->x[i]][arrow->y[i] + j] = skin.arrow[j];
                }
            }
            else if(arrow->active[i]){
                arrow->active[i] = false;
                for(int j=0; j < ARROW_COLUMNS; j++){
                    gameLayer[arrow->x[i]][arrow->y[i] + j] = ' ';
                }
                arrow->activeIndex--;
            }
        }
    }
    if(arrow->activeIndex == 0 && arrow->index == preset.arrowQuantity && (balloon->activeIndex > 0 || monster->activeIndex > 0)){
        player.gameOver = true;
    } 

/*************************BALLOON*************************/
    if(preset.levelType == balloonLevel || preset.levelType == balloonScatteredLevel){
        if(balloon->activeIndex > 0 && !balloon->stagger){
            for(int i=0; i < BALLOON_QUANTITY; i++){
                if(balloon->active[i] && !balloon->individualStagger[i]){
                    balloon->x[i]--;
                    if(balloon->x[i] < (BALLOON_LOWER_LIMIT - BALLOON_ROWS)){
                        for(int i2=0; i2 <= BALLOON_ROWS; i2++){
                            if(balloon->x[i] > BALLOON_UPPER_LIMIT - i2){
                                setBalloon(&(*balloon), i, i2, BALLOON_ROWS, true);
                                break;
                            }
                            else if(i2 == BALLOON_ROWS) balloon->x[i] = BALLOON_LOWER_LIMIT - 1; //this one is why i3=1
                        }
                    }
                    //can't be else!**
                    if(balloon->x[i] >= (BALLOON_LOWER_LIMIT - BALLOON_ROWS)){
                        for(int i3=1; i3 <= BALLOON_ROWS; i3++){
                            if(balloon->x[i] == (BALLOON_LOWER_LIMIT - i3)){
                                setBalloon(&(*balloon), i, 0, i3, false);
                                break;
                            }
                        }
                    }
                }
                //gotoxy(2,20); printf("%3d", balloon->x[0]);
            }    
        }
        if(balloon->activeIndex == 0 && arrow->activeIndex == 0){
            player.levelOver = true;
        }
    }

/*************************MONSTER*************************/
    if(preset.levelType == monsterLevel){
        if(monster->activeIndex > 0 && !monster->stagger){
            for(int i=0; i < monster->index; i++){
                if(monster->active[i]){             
                    //gotoxy(2,20); printf("%3d", monster->y[0]);
                    monster->y[i]--;
                    //appearing from the right  
                    if(monster->y[i] > (MONSTER_RIGHT_LIMIT - MONSTER_COLUMNS)){
                        for(int i2=1; i2 <= MONSTER_COLUMNS; i2++){
                            if(monster->y[i] > (MONSTER_RIGHT_LIMIT - i2)){
                                setMonster(&(*monster), i, 0, i2, false);
                                break;
                            }
                        }
                    }
                    //in the middle of the screen
                    else if(monster->y[i] >= (MONSTER_LEFT_LIMIT)){
                        setMonster(&(*monster), i, 0, MONSTER_COLUMNS, true);
                    }
                    //disappearing from the left
                    else{ // < MONSTER_LEFT_LIMIT
                        for(int i3=0, i4=1; i3 > -MONSTER_COLUMNS; i3--, i4++){
                            if(monster->y[i] == i3){
                                
                                for(int m=0; m < MONSTER_ROWS; m++){
                                    for (int n=0, aux=i4; aux < MONSTER_COLUMNS; n++, aux++){
                                        gameLayer[monster->x[i] + m][MONSTER_LEFT_LIMIT + n] = skin.monster[(m * MONSTER_COLUMNS) + aux];
                                    } 
                                }
                                for(int j=0; j < MONSTER_ROWS; j++){
                                    gameLayer[monster->x[i] + j][MONSTER_COLUMNS+(i3)] = ' ';
                                }
                                if(i3 == -MONSTER_COLUMNS + 1){//turn off monster
                                    monster->active[i] = false;
                                    monster->activeIndex--;
                                }
                                break;
                            }

                        }
                    }  
                }
            }
            //getchar();
        }
        if(monster->activeIndex == 0 && monster->index == MONSTER_QUANTITY && arrow->activeIndex == 0){
            player.levelOver = true;
        }
    }

/*************************ARCHER*************************/
    if(archer->active){ 
        for(int i=0; i < ARCHER_ROWS; i++){
            for(int j=0; j < ARCHER_COLUMNS; j++){
                gameLayer[archer->x + i][archer->y + j] = skin.archer[(i*ARCHER_COLUMNS) + j]; 
            }
        }
        archer->active = false;
    }

}

void setMonster(MONSTER *monster, int i, int startColumn, int endColumn, bool clean){

    for(int m=0; m < MONSTER_ROWS; m++){
        for (int n=startColumn; n < endColumn; n++){
            gameLayer[monster->x[i] + m][monster->y[i] + n] = skin.monster[(m * MONSTER_COLUMNS) + n];
        } 
    }
    if(clean){
        for(int j=0; j < MONSTER_ROWS; j++){
            gameLayer[monster->x[i] + j][monster->y[i] + MONSTER_COLUMNS] = ' ';
        }
    }
}

void hitMonsterDetector(ARROW *arrow, MONSTER *monster){
    if(arrow->activeIndex > 0 && monster->activeIndex >0){
        for(int i=0; i < arrow->index; i++){
            if(arrow->active[i]){
                for(int j=0; j < monster->index; j++){
                    if(monster->active[j]){
                        // Y hitbox check  
                        for(int m=0; m < MONSTER_COLUMNS; m++){
                            if(arrow->y[i] + ARROW_COLUMNS == monster->y[j] + m){
                                // X hitbox check
                                for(int n=0; n < MONSTER_ROWS; n++){
                                    if(arrow->x[i] == monster->x[j] + n){
                                        //getchar();
                                        if(preset.arrowConsumableArrows){
                                            arrow->active[i] = false;
                                            for(int a=0; a < ARROW_COLUMNS; a++){
                                                gameLayer[arrow->x[i]][arrow->y[i] + a] = ' ';
                                            }
                                            arrow->activeIndex--;
                                        }
                                        for(int m1=0; m1 < MONSTER_ROWS; m1++){
                                            for(int m2=0; m2 < MONSTER_COLUMNS; m2++){
                                                if((monster->y[j] + m2) < CANVAS_RIGHT_EDGE_Y){ //border limit
                                                    gameLayer[monster->x[j] + m1][monster->y[j] + m2] = ' ';
                                                }
                                            }
                                        }
                                        monster->active[j] = false;
                                        monster->activeIndex--;
                                        player.monstersKilled++;
                                        //score
                                        player.score += MONSTER_POINTS;
                                        printNumberInGame(player.score, SCORE_DISPLAY_X, SCORE_DISPLAY_Y, "%06i");
                                        break;
                                    }
                                }
                                break;
                            }     
                        }
                    }
                }
            }
        }
    }
}

bool hitArcherDetector(ARCHER *archer, MONSTER *monster){
    if(monster->activeIndex > 0){
        for(int i=0; i < monster->index; i++){
            if(monster->active[i]){
                if(monster->y[i] < (ARCHER_COLUMNS+ARCHER_INITIAL_Y)){// Y hitbox 1
                    //now just check the X hitbox
                    for(int m=0; m < MONSTER_ROWS; m++){
                        for(int a=0; a < ARCHER_ROWS; a++){
                            if((monster->x[i] + m) == (archer->x + a)){
                                // Y hitbox 2 <- more precision
                                for(int m2=0; m2 < MONSTER_COLUMNS; m2++){
                                    for(int a2=0; a2 < ARCHER_COLUMNS; a2++){
                                        if((monster->y[i] + m2) == (archer->y + a2)){
                                            if(skin.monster[(m * MONSTER_COLUMNS) + m2] != ' ' && skin.archer[(a * ARCHER_COLUMNS) + a2] != ' '){
                                                //getchar();
                                                return true;
                                                //break;
                                            }
                                        }
                                    }
                                }
                                if(!archer->active) archer->active = true; //keep archer fresh even if it's not moving
                            }
                        }
                    }
                }
            }
        }
    }
    return false;


}

void hitBalloonDetector(ARROW *arrow, BALLOON *balloon){
    if(arrow->activeIndex > 0 && balloon->activeIndex >0){
        for(int i=0; i < arrow->index; i++){
            if(arrow->active[i]){
                for(int j=0; j < BALLOON_QUANTITY; j++){
                    if(balloon->active[j]){
                        // Y hitbox check  
                        for(int m=0; m < BALLOON_COLUMNS; m++){
                            if(arrow->y[i] + ARROW_COLUMNS == balloon->y[j] + m){
                                // X hitbox check
                                for(int n=0; n < BALLOON_ROWS; n++){
                                    if(arrow->x[i] == balloon->x[j] + n){
                                        //getchar();
                                        if(preset.arrowConsumableArrows){
                                            arrow->active[i] = false;
                                            for(int a=0; a < ARROW_COLUMNS; a++){
                                                gameLayer[arrow->x[i]][arrow->y[i] + a] = ' ';
                                            }
                                            arrow->activeIndex--;
                                        }
                                        for(int b1=0; b1 < BALLOON_ROWS; b1++){
                                            for(int b2=0; b2 < BALLOON_COLUMNS; b2++){
                                                gameLayer[balloon->x[j] + b1][balloon->y[j] + b2] = ' ';
                                            }
                                        }
                                        balloon->active[j] = false;
                                        balloon->activeIndex--;
                                        player.balloonsDestroyed++;
                                        //score
                                        player.score += BALLOON_POINTS;
                                        printNumberInGame(player.score, SCORE_DISPLAY_X, SCORE_DISPLAY_Y, "%06i");
                                        break;
                                    }
                                }
                                break;
                            }     
                        }
                    }
                }
            }
        }
    }
}

void printNumberInGame(int value, int x, int y, char format[4]){
    char buf[10] = {NULL};
    snprintf(buf, sizeof(buf),format, value); 
    for(int index=0; index < 10; index++){
        if(buf[index] != '\0') gameLayer[x][y + index] = buf[index];
    }
}

void printStringInGame(char string[10], int x, int y){
    char buf[10] = {NULL};
    snprintf(buf, sizeof(buf),"%s", string); 
    for(int index=0; index < 10; index++){
        if(buf[index] != '\0') gameLayer[x][y + index] = buf[index];
    }
}

void setBalloon(BALLOON *balloon, int  i, int startRow, int endRow, bool clean){
    
    for(int m=startRow; m < endRow; m++){
        for(int n=0; n < BALLOON_COLUMNS; n++){
            gameLayer[balloon->x[i] + m][balloon->y[i] + n] = skin.balloon[(m * BALLOON_COLUMNS) + n];
        }
    }
    if(clean){
        for(int j=0; j < BALLOON_COLUMNS; j++){
            gameLayer[balloon->x[i] + BALLOON_ROWS][balloon->y[i] + j] = ' ';
        }  
    }


}

void draw(){

    for(int i=0; i < CANVAS_ROWS; i++){
        if(i != CANVAS_UPPER_EDGE_X && i != CANVAS_MIDDLE_EDGE_X && i != CANVAS_LOWER_EDGE_X){
            for(int j=0; j < CANVAS_COLUMNS; j++){
                if(j != CANVAS_LEFT_EDGE_Y && j != CANVAS_RIGHT_EDGE_Y){
                    if(gameLayer[i][j] != '\0'){
                        gotoxy(i,j);
                        printf("%c", gameLayer[i][j]);                
                    }
                }
            }
        }
    }
    //getchar();
}

void archerMovUp(ARCHER *archer){
    LARGE_INTEGER t1;
    QueryPerformanceCounter(&t1);

    if(timeDiff(archer->startTimeKeyHitLimit) >= preset.archerHitDelay) archer->startTimeKeyHitLimit = t1.QuadPart;
    if(!archer->keyHitLimit){
        if(archer->x > ARCHER_UPPER_LIMIT){
            for(int i=0; i < ARCHER_COLUMNS; i++){
                gameLayer[archer->x + ARCHER_ROWS-1][archer->y + i] = ' ';
            }
            archer->x--;
            archer->active = true;
        }
    }
}

void archerMovDown(ARCHER *archer){
    LARGE_INTEGER t1;
    QueryPerformanceCounter(&t1);

    if(timeDiff(archer->startTimeKeyHitLimit) >= preset.archerHitDelay) archer->startTimeKeyHitLimit = t1.QuadPart;
    if(!archer->keyHitLimit){
        if(archer->x < ARCHER_LOWER_LIMIT){
            for(int i=0; i < ARCHER_COLUMNS; i++){
                gameLayer[archer->x][archer->y + i] = ' ';
            }
            archer->x++;
            archer->active = true;  
        }
    }
}

void arrowShoot(ARCHER archer, ARROW *arrow){ 
    LARGE_INTEGER t1;
    QueryPerformanceCounter(&t1);

    if(timeDiff(arrow->startTimeKeyHitLimit) >= preset.arrowHitDelay) arrow->startTimeKeyHitLimit = t1.QuadPart;
    if(!arrow->keyHitLimit){
        if(arrow->index < preset.arrowQuantity){
            if(!SPECIAL_INTERFACE) gameLayer[ARROW__LEFT_DISPLAY_X][((CANVAS_RIGHT_EDGE_Y-1)-preset.arrowQuantity) + arrow->index] = ' '; //-1 from display arrows left

            arrow->active[arrow->index] = true;
            arrow->activeIndex++;
            arrow->x[arrow->index] = archer.x + 1;
            arrow->y[arrow->index] = archer.y + ARCHER_COLUMNS;

            for(int i=0; i < ARROW_COLUMNS; i++){
                gameLayer[ arrow->x[arrow->index] ][ arrow->y[arrow->index] + i] = skin.arrow[i]; 
            }
            arrow->index++;

        }
    }

}   

bool readTxtFiles(char matrixObject[], int columns, char txtFileName[]){
    char buf[100];
	FILE *pont_arq;
	char read; 
	int i=0, j=0;
	
        snprintf(buf, sizeof(buf),"graphics\\\\%s.txt", txtFileName);
		pont_arq = fopen(buf, "r");
		if(pont_arq){
			while(feof(pont_arq) == false){
    			if(fread(&read, sizeof(char), 1, pont_arq)){ 
					//printf("%c", read);
                    if(j < columns){
                    	matrixObject[(i*columns) + j] = read;
                        j++;
                    }
                    else{
                        i++;
                        j=0;
                    }
				}
			}
			fclose(pont_arq);
		}
		else{
            system("cls");
            gotoxy(0,0);
            printf("Error in the opening of: %s.txt\n", txtFileName);
            printf("Press ENTER to continue...\n");
            getchar();
            return false;
		}

    return true;
}

double timeDiff(LONGLONG startTime){
    static LARGE_INTEGER freq;
    LARGE_INTEGER endTime;
    
    if(freq.QuadPart == NULL){ //just read the frequency one time
        QueryPerformanceFrequency(&freq);
    }

    QueryPerformanceCounter(&endTime);
    return 1000*( (double)(endTime.QuadPart - startTime)/ freq.QuadPart );  //milisegundos
    
}

bool keyHitControl(LONGLONG startTime, double delay){
    //double timeDifference= timeDiff(startTime, clock());
    //gotoxy(3,25); printf("%lf", timeDifference );   
    if(timeDiff(startTime) >= delay){
        return false;               
    }
    else{ 
        return true;
    }
}

bool staggerControl(LONGLONG *startTime, double delay){
    LARGE_INTEGER t1;    

	if(timeDiff(*startTime) >= delay){
        QueryPerformanceCounter(&t1);
        *startTime = t1.QuadPart;
		return false;
	}
	else{
		return true;
	}
}

void staggerControlScatteredBalloon(BALLOON *balloon){
    LARGE_INTEGER t1;

    for(int i=0; i < BALLOON_QUANTITY; i++){
        if(timeDiff(balloon->startTimeIndividualStagger[i]) >= balloon->IndividualDelay[i]){
            QueryPerformanceCounter(&t1);
            balloon->startTimeIndividualStagger[i] = t1.QuadPart;
            balloon->individualStagger[i] = false;
        }
        else{
            balloon->individualStagger[i] = true;
        }
    }
}

void setBalloonFirstRowPosition(BALLOON *balloon){
    
    balloon->activeIndex = BALLOON_QUANTITY;
    for(int i=0; i < BALLOON_QUANTITY; i++){
        balloon->x[i] = preset.balloonInitialX;
        balloon->y[i] = BALLOON_ROW_INITIAL_Y + (i * (BALLOON_COLUMNS + 1));
        balloon->active[i] = true;
    }
}

void setBalloonScatteredPostition(BALLOON *balloon){
    srand(time(NULL));
    // for random x begin
    /*int max1 = (BALLOON_LOWER_LIMIT-BALLOON_ROWS) - BALLOON_UPPER_LIMIT;
    balloon->x[i] = BALLOON_UPPER_LIMIT + ( (rand() % max1)  + 1)*/ 
    int max2 = preset.balloonScatteredDelayMax - preset.balloonScatteredDelayMin;

    balloon->activeIndex = BALLOON_QUANTITY;
    for(int i=0; i < BALLOON_QUANTITY; i++){
        balloon->x[i] = preset.balloonInitialX;
        balloon->y[i] = BALLOON_ROW_INITIAL_Y + (i * (BALLOON_COLUMNS + 1));
        balloon->active[i] = true;
        balloon->IndividualDelay[i] = preset.balloonScatteredDelayMin +  ( (rand() % max2)  + 1);
    }
}

void setMonsterFirstPosition(MONSTER *monster){

    int max = MONSTER_LOWER_LIMIT - MONSTER_UPPER_LIMIT;

    for(int i=0; i < MONSTER_QUANTITY; i++){
        monster->x[i] = MONSTER_UPPER_LIMIT + ( (rand() % max)  + 1);   
        monster->y[i] = MONSTER_INITIAL_Y;  
        //gotoxy(monster->x[i], monster->y[i]); printf("here"); getchar();      
    }

}

bool spawnRateMonster(MONSTER *monster, double delay){
    LARGE_INTEGER t1;   
    //gotoxy(3,20); printf("%lf", timeDifference );

    if(timeDiff(monster->startTimeSpawn) >= delay){
       
        if(monster->index < MONSTER_QUANTITY){
            //getchar();
            monster->active[monster->index] = true;
            monster->activeIndex++;
            monster->index++;
        }
         QueryPerformanceCounter(&t1); 
        monster->startTimeSpawn = t1.QuadPart;
        return true;
    }
    else{
        return false;
    }

}