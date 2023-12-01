#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    sizeList = 0; // Points to the next position in the array
    sizeArray = ARRAY_MAX_CAP; // sizeArray = 200
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
    // Can't insert anything if the array is full. 
    // Also protects against the case sizeList is negative
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
    // Can't insert anything if the array is full. 
    // Also protects against the case sizeList is negative
    if(sizeList >= sizeArray || sizeList < 0)
    {
        return;
    }

    aList[sizeList] = thisPos;  // Inserting the element at the tail, index: sizeList
    sizeList++;
}

void objPosArrayList::removeHead()
{
    // Can't remove elements if sizeList is negative or if the array contains no elements
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
    // Can't remove elements if sizeList is negative or if the array contains no elements
    if(sizeList <= 0)
    {
        return;
    }   
    sizeList--;
}

// Pass-by-value
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
    if (index < 0 || index >= sizeList)
    {
        return;
    }
    
    returnPos = aList[index];
}