#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.setObjPos(5, 5, '*');
}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
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
    switch (myDir)
    {
        case UP:
            playerPos.y--;
            break;
        case DOWN:
            playerPos.y++;
            break;
        case LEFT:
            playerPos.x--;
            break;
        case RIGHT:
            playerPos.x++;
            break;
        default:
            break;
    }

    // [TODO] : Heed the border wraparound!!!
    if (playerPos.x <= 0)
    {
        playerPos.x = mainGameMechsRef->getBoardSizeX() - 2;
    }
    else if (playerPos.x >= mainGameMechsRef->getBoardSizeX() - 1)
    {
        playerPos.x = 1;
    }
    else if (playerPos.y <= 0)
    {
        playerPos.y = mainGameMechsRef->getBoardSizeY() - 2;
    }
    else if (playerPos.y >= mainGameMechsRef->getBoardSizeY() - 1)
    {
        playerPos.y = 1;
    }
}

