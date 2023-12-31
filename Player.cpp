#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* thisFood)
{
    // Initializing food and gameMechanic references, and direction state
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    foodRef = thisFood;

    // Intiatilizing player body
    objPos tempPos; 
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);
}


Player::~Player()
{
    // Delete any heap members
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;
}

// Processes input from user and updates snake directions (UP, DOWN, RIGHT and LEFT)
void Player::updatePlayerDir()
{
    // Gets user input
    char input;
    input = mainGameMechsRef->getInput();

    // Updates direction
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

// Uses direction to update snake movement
void Player::movePlayer()
{
     // Holds the position information of snake head
    objPos currentHead;
    playerPosList->getHeadElement(currentHead);

    // Updates snake movement, accounting for boarders
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
    
    // Checks if the new head position overlaps with food
    if (checkFoodComsumption() == 1)
    {
        // If yes, increase player length and generate new food
        increasePlayerLength();
    }
    else
    {
        // Otherwise, carry out regular insert + remove to complete the snake movement
        playerPosList->insertHead(currentHead);
        playerPosList->removeTail();

        // Check for self-collision
        checkSelfCollision();
    }
}

// Additional Functions
bool Player:: checkFoodComsumption()
{
    // Get the  position of the player's head
    objPos tempHead;
    playerPosList->getHeadElement(tempHead);

    // Get the  position of the food
    objPos foodPos;
    foodRef->getFoodPos(foodPos);

    // Check if the head position is equal to any food position
    if (tempHead.isPosEqual(&foodPos)) {
        // If a match is found, return true (food consumed)
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

    // Generate new food and increase user score
    foodRef->generateFood(*playerPosList);
    mainGameMechsRef->incrementScore();
}

bool Player::checkSelfCollision()
{
    // Get the  position of the player's head
    objPos tempHead;
    playerPosList->getHeadElement(tempHead);

    //iteration through all of the body's position
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