#include "objPosArrayList.h"

// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.

objPosArrayList::objPosArrayList()
{
    sizeList = 0;
    sizeArray = ARRAY_MAX_CAP;
    aList = new objPos[ARRAY_MAX_CAP];
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(sizeList >= sizeArray || sizeList < 0)
    {
        return;
    }

    for (int i = sizeList; i > 0; i--)
    {
        aList[i] = aList[i-1];  // Shiting all elements towards the tail to create space at the head
    }
    aList[0] = thisPos; // Inserting the element at the head, index: 0
    sizeList++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(sizeList >= sizeArray || sizeList < 0)
    {
        return;
    }

    aList[sizeList] = thisPos;  // Inserting the element at the tail, index: sizeList
    sizeList++;
}

void objPosArrayList::removeHead()
{
    if(sizeList <= 0)
    {
        return;
    }   

    for(int i = 0; i < sizeList - 1; i++)
    {
        aList[i] = aList[i+1];
    }
    sizeList--;
}

void objPosArrayList::removeTail()
{
    if(sizeList <= 0)
    {
        return;
    }   
    sizeList--;
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos = aList[0];
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos = aList[sizeList - 1];
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos = aList[index];
}