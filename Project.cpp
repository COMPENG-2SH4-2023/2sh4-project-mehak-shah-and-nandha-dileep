#include <iostream>
#include "MacUILib.h"
#include "objPos.h" // fundamental building block for project.
#include "objPosArrayList.h"
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
    myFood = new Food(myGM);
    myPlayer = new Player(myGM, myFood);

    //generating initial food
    // For testing purposes only to be removed afterwards
    objPosArrayList blockOff; //assuming there is no blockoff initailly
    myFood->generateFood(blockOff); // Turn into arrayList operation
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

    objPosArrayList* tempPosList;
    tempPosList = myPlayer->getPlayerPos();
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

    for (int i = 0; i < myGM->getBoardSizeY(); i++) 
    {
        for (int j = 0; j < myGM->getBoardSizeX(); j++) 
        {
            drawn = false;
            
            // Iterate through every element in the playerBody list
            for (int k = 0; k < playerBody->getSize(); k++)
            {
                playerBody->getElement(tempBody, k);
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

//          3. For every visited character location on the game board
//          If on border on the game board, print a special character
            if (i == 0 || i == myGM->getBoardSizeY() - 1 || j == 0 || j == myGM->getBoardSizeX() - 1) 
            {
                MacUILib_printf("#");
//          If at the player object position, print the player symbol
            } 
            else if (i == foodPos.y && j == foodPos.x) 
            { //the character key
                MacUILib_printf("%c", foodPos.symbol);
//              Otherwise, print the space character
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
    
    /*MacUILib_printf("Player Positions:\n");
    for (int l = 0; l < playerBody->getSize(); l++)
    {
        playerBody->getElement(tempBody, l);
        MacUILib_printf("<%d, %d> ", tempBody.x, tempBody.y);
    }
    MacUILib_printf("\nFood Position: <%d, %d>\n", foodPos.x, foodPos.y);
    */
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen(); 

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
    MacUILib_uninit();

    
    // Remove heap instances
    delete myGM;
    delete myPlayer;
    delete myFood;
}