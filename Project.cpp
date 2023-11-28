#include <iostream>
#include "MacUILib.h"
#include "objPos.h"


using namespace std;

# define DELAY_CONST 100000
# define ROW_SIZE 18 // y-coordinates
# define COL_SIZE 36 // x-coordinates

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

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();
}
