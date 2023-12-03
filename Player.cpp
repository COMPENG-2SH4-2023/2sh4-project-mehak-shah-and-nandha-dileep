#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    objPos tempPos; 
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() /2, mainGameMechsRef->getBoardSizeY() /2, '@');
    
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);

    // For debugging purposes, insert another 4 heads
    /*playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);*/
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
    // new current head should be inserted to the head of the list,
    playerPosList->insertHead(currentHead);

    // then remove tail
    playerPosList->removeTail();
}

