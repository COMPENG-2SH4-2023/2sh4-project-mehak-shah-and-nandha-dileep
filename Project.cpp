#include <iostream>
#include "MacUILib.h"
#include "objPos.h"


using namespace std;

# define DELAY_CONST 100000
//# define ROW_SIZE 18 // y-coordinates
//# define COL_SIZE 36 // x-coordinates

GameMechs* myGM;
Player* myPlayer;

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(exitFlag == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    exitFlag = false;
}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 
    
    /*// Builds game board
    for (i = 0; i < ROW_SIZE; i++){
        for (j = 0; j < COL_SIZE; j++){
            if (i == 0 || i == (ROW_SIZE - 1) || j == 0 || j == (COL_SIZE - 1))
            {
                gameBoard[i][j] = '#';
            }
            else
            {
                gameBoard[i][j] = ' ';
            }
        }
    }  */ 

    int i, j;
    for (i = 0; i < myGM->getBoardSizeY(); i++) {
        for (j = 0; j < myGM->getBoardSizeX(); j++) {
    //  3. For every visited character location on the game board
    //      If on border on the game board, print a special character
            if (i == 0 || i == myGM->getBoardSizeY() - 1 || j == 0 || j == myGM->getBoardSizeX() - 1) 
            {
                MacUILib_printf("#");
    //          If at the player object position, print the player symbol
            } 
            else if (i == tempPos.y && j == tempPos.x) 
            { //the character key
                MacUILib_printf("%c", tempPos.symbol);
    //          Otherwise, print the space character
            } 
            else 
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();

    delete myGM;
    delete myPlayer;
}
