#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

# define DELAY_CONST 100000

//declaring heap instances
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
    myFood = new Food(myGM);
    myPlayer = new Player(myGM, myFood);

    objPosArrayList blockOff; //assuming there is no blockoff initailly
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

    // Get all of the positions of the player's body
    objPosArrayList* tempPosList;
    tempPosList = myPlayer->getPlayerPos();

    // Get the  position of the player's head
    objPos tempPos;
    tempPosList->getHeadElement(tempPos);

    myGM->clearInput(); // To prevent repeating input
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 

    bool drawn;

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos tempBody;

    objPos foodPos;
    myFood->getFoodPos(foodPos);

    //iterating through every element of the gameboard
    for (int i = 0; i < myGM->getBoardSizeY(); i++) 
    {
        for (int j = 0; j < myGM->getBoardSizeX(); j++) 
        {
            drawn = false;
            
            // Iterate through every element in the playerBody list
            for (int k = 0; k < playerBody->getSize(); k++)
            {
                playerBody->getElement(tempBody, k);
                //If at the player object position, print the player symbol
                if (tempBody.x == j && tempBody.y == i)
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;
                }

            }
            // If playerBody was drawn, don't draw anything below
            if (drawn)
            {
                continue;
            }

            //For every visited character location on the game board
            //If on border on the game board, print a special character
            if (i == 0 || i == myGM->getBoardSizeY() - 1 || j == 0 || j == myGM->getBoardSizeX() - 1) 
            {
                MacUILib_printf("#");
            } 
            else if (i == foodPos.y && j == foodPos.x) 
            { //the character key
                MacUILib_printf("%c", foodPos.symbol);
            //Otherwise, print the space character
            } 
            else 
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("INSTRUCTIONS: \n");
    MacUILib_printf("Press 'W' to go up.\nPress 'S' to go down.\nPress 'D' to go right.\nPress 'A' to go left.\n" );
    MacUILib_printf("Collect food (o) to grow longer, but avoid colliding with the snake's own body.\n");
    MacUILib_printf("Press the key '!' to exit the game! \n\n");

    MacUILib_printf("Score: %d\n", myGM->getScore());

    //Printing the exit messages after game exits
    if (myGM->getExitFlagStatus())
    {
        if (myGM->getLoseFlagStatus())
        {
            // Player lost
            MacUILib_printf("Game Over! You lost. Your score is %d!\n", myGM->getScore());
        }
        else
        {
            // Normal exit
            MacUILib_printf("Game Over! You have exited the game. Your score is %d!\n", myGM->getScore());
        }
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

    
    // Remove heap instances
    delete myGM;
    delete myPlayer;
    delete myFood;
}