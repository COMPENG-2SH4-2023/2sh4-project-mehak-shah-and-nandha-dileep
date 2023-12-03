#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* thisFood)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    foodRef = thisFood;

    // more actions to be included
    objPos tempPos; 
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() /2, mainGameMechsRef->getBoardSizeY() /2, '@');
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char input;
    input = mainGameMechsRef->getInput();

    switch(input)
    {                      
        case 'W':
        case 'w': //accepts lowercase letters too
            if (myDir != DOWN)
            {
                myDir = UP;
            }
            break;
        case 'S':
        case 's':
            if (myDir != UP)
            {
                myDir = DOWN;
            }
            break;
        case 'A':
        case 'a':
            if (myDir != RIGHT)
            {
                myDir = LEFT;
            }
            break;
        case 'D': 
        case 'd':
            if (myDir != LEFT)
            {
                myDir = RIGHT;
            } 
            break;
        default:
            break;
    }
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    objPos currentHead; // Holds the pos information of the current head
    playerPosList->getHeadElement(currentHead);

    switch (myDir)
    {
        case UP:
            currentHead.y--;
            if (currentHead.y <= 0)   //Wraparound logic
            {
                currentHead.y = mainGameMechsRef->getBoardSizeY() - 2;
            }
            break;
        case DOWN:
            currentHead.y++;
            if (currentHead.y >= mainGameMechsRef->getBoardSizeY() - 1)    //Wraparound logic
            {
                currentHead.y = 1;
            }
            break;
        case LEFT:
            currentHead.x--;
            if (currentHead.x <= 0)    //Wraparound logic
            {
                currentHead.x = mainGameMechsRef->getBoardSizeX() - 2;
            }
            break;
        case RIGHT:
            currentHead.x++;
            if (currentHead.x >= mainGameMechsRef->getBoardSizeX() - 1)     //Wraparound logic
            {
                currentHead.x = 1;
            }
            break;
        default:
            break;
    }
    
    // Check if the new head position overlaps with food
    if (checkFoodComsumption() == 1)
    {
        // If yes, increase player length and generate new food
        increasePlayerLength();
    }
    else
    {
        // If no, carry out regular insert + remove to complete the snake movement
        playerPosList->insertHead(currentHead);
        playerPosList->removeTail();

        // Check for self-collision
        checkSelfCollision();
    }
}

// Need more actions in here:
        /* After inserting the head but before removing the tail 
           - check new head position collides with food 
           - if yes, incremente the score in GM and generate new food. do not remove the tail 
           - otherwise, remove tail and move on
           
           
        Lastly, add self-collision check.
        - if self-collided 
            set loseFlag and exitFlag to true (through GM), 
            this will break the program loop and end the game
        - if ending, you need to differentiate the end game stakes
            LOST - display LOST message otherwise, 
            display ENDGAME message only
        */

// Additional Functions
bool Player:: checkFoodComsumption()
{
    objPos tempHead;
    playerPosList->getHeadElement(tempHead);

    objPos foodPos;
    foodRef->getFoodPos(foodPos);

    if (tempHead.isPosEqual(&foodPos)) {
        return true;
    }

    return false;
}

void Player::increasePlayerLength()
{
    // Get the  position of the player's body
    objPos bodyPos;
    playerPosList->getHeadElement(bodyPos);

    // Insert a new head at the body position
    playerPosList->insertHead(bodyPos);

    foodRef->generateFood(*playerPosList);

    mainGameMechsRef->incrementScore();

}


bool Player::checkSelfCollision()
{
    objPos tempHead;
    playerPosList->getHeadElement(tempHead);

    for (int i = 1; i < playerPosList->getSize(); i++)
    {
        objPos tempPos;
        playerPosList->getElement(tempPos, i);

        // Check if the head position collides with any element in the playerPosList
        if (tempHead.isPosEqual(&tempPos))
        {
            // Collision detected, set lose flag and exit flag
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
            return true;
        }
    }

    return false;

}
