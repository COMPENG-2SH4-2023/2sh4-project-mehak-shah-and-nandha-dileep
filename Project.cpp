#include <iostream>
#include "MacUILib.h"
#include "objPos.h" // fundamental building block for project.
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

# define DELAY_CONST 100000

GameMechs* myGM;
Player* myPlayer;
Food* myFood;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
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

    myGM = new GameMechs(); // Set the board dimensions to 30x15
    myPlayer = new Player(myGM);
    myFood = new Food(myGM);

    //generating initial food
    objPos blockOff; //assuming that there is no blockOff initially
    myFood->generateFood(blockOff);
}

void GetInput(void)
{
    myGM->getInput();
}

void RunLogic(void)
{
    // In Player.cpp, updatePlayerDir() gets char input from GameMechs and updates direction
    myPlayer->updatePlayerDir(); 
    myPlayer->movePlayer();

    objPos tempPos;
    myPlayer->getPlayerPos(tempPos);

    char input;
    input = myGM->getInput();

    if (input == ' ')
    {
        myGM->clearInput();
        myFood->generateFood(tempPos);
    }

    //myGM->clearInput(); // To prevent repeating input
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 

    //MacUILib_printf("Object: <%d, %d> with %c\n", myPos.x, myPos.y, myPos.symbol);

    objPos tempPos;
    myPlayer->getPlayerPos(tempPos);

    objPos foodPos;
    myFood->getFoodPos(foodPos);

    int i, j;
    for (i = 0; i < myGM->getBoardSizeY(); i++) 
    {
        for (j = 0; j < myGM->getBoardSizeX(); j++) 
        {
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
            else if (i == foodPos.y && j == foodPos.x) 
            { //the character key
                MacUILib_printf("%c", foodPos.symbol);
    //          Otherwise, print the space character
            } 
            else 
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Score: %d\n", myGM->getScore());
    MacUILib_printf("Board size: %dx%d,\nPlayer Position: <%d, %d> + %c\n", myGM->getBoardSizeX(), myGM->getBoardSizeY(), tempPos.x, tempPos.y, tempPos.symbol);

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    MacUILib_uninit();
    
    // Remove heap instances
    delete myGM;
    delete myPlayer;
    delete myFood;
}