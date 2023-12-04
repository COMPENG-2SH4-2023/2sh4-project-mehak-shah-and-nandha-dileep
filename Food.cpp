#include "Food.h"


Food::Food(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    foodPos.setObjPos(-1, -1, 'o'); // Initialize foodPos outside of Gameboard
    srand(time(NULL)); // Seed the random number generator once
}

/*Food::~Food()
{
    // delete any heap members here
}*/

void Food::generateFood(objPosArrayList &playerPosList)
{
    // Loops until x and y positions for food is valid
    while (true)
    {
        int x = (rand() % (mainGameMechsRef -> getBoardSizeX() - 2)) + 1; // Chooses between (1, boardSizeX - 1)
        int y = (rand() % (mainGameMechsRef -> getBoardSizeY() - 2)) + 1; // Chooses between (1, boardSizeY - 1)

        foodPos.setObjPos(x, y, 'o');

        // Checking whether the food position is equal to the position of the player's body
        bool overlap = false;
        for (int i = 0; i < playerPosList.getSize(); i++)
        {
            objPos tempPos;
            playerPosList.getElement(tempPos, i);
            if (foodPos.isPosEqual(&tempPos))
            {
                overlap = true;
                break;
            }
        }

        if (x != 0 && x != mainGameMechsRef->getBoardSizeX() - 1 && y != 0 && y != mainGameMechsRef->getBoardSizeY() - 1 && overlap == 0)
        {
            break; // Valid position found, exit the loop
        }
    }
}

void Food::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}