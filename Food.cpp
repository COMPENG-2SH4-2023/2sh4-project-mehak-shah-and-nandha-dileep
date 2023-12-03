#include "Food.h"

Food::Food(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    foodPos.setObjPos(-1, -1, 'o'); //initialize foodPos outside of gameboard

}

Food::~Food()
{
    // delete any heap members here
}


void Food::generateFood(objPosArrayList &playerPosList)
{
    //generate random x and y coordinates and make sure they and NOT bparder or blockOff pos
    //check x and y againt 0 and boardsizex/y
    //remember, in objPos class you have an isPosEqual() method. Use this instead of comparing element by element for your convenience

    foodPos.setObjPos(-1, -1, ' '); //clearing any food that was previously generated
    srand(time(NULL)); // Seed the random number generator //DOUBLE CHECK IF THIS IS THE RIGHT PLACE

    while (true)
    {
        int x = (rand() % (mainGameMechsRef -> getBoardSizeX() - 2)) + 1; // Chooses between (1, boardSizeX - 2)
        int y = (rand() % (mainGameMechsRef -> getBoardSizeY() - 2)) + 1; // Chooses between (1, boardSizeY - 2)

        foodPos.setObjPos(x, y, 'o');

        /*// Check if the generated position is not on the blockOff
        if (x != 0 && x != mainGameMechsRef -> getBoardSizeX() - 1 && y != 0 && y != mainGameMechsRef -> getBoardSizeY() - 1 && foodPos.isPosEqual(&blockOff) == 0)
        {
            break; // Valid position found, exit the loop
        }*/

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

//getter
void Food::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}

