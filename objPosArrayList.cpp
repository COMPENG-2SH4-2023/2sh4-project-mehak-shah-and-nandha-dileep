#include "objPosArrayList.h"

// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.

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
    // Create new (larger) array if the current array is full. 
    if(sizeList >= sizeArray)
    {
        // Allocate memory for a new list
        objPos* newList = new objPos[sizeArray + ARRAY_INCREASE_AMOUNT];

        // Copy old list items into new list
        for (int i = 0; i < sizeList; i++)
        {
            newList[i] = aList[i];
        }

        // Deallocate the memory of the old array
        delete[] aList;

        // Update the pointer to point to the new array 
        aList = newList;

        sizeArray = sizeArray + ARRAY_INCREASE_AMOUNT; // Updates list size
    }

    for (int i = sizeList; i > 0; i--)
    {
        aList[i].setObjPos(aList[i-1]);  // Shiting all elements towards the tail to create space at the head
    }
    aList[0].setObjPos(thisPos); // Inserting the element at the head, index: 0
    sizeList++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    // Create new (larger) array if the current array is full. 
    if(sizeList >= sizeArray)
    {
        // Allocate memory for a new list
        objPos* newList = new objPos[sizeArray + ARRAY_INCREASE_AMOUNT];

        // Copy old list items into new list
        for (int i = 0; i < sizeList; i++)
        {
            newList[i] = aList[i];
        }

        // Deallocate the memory of the old array
        delete[] aList;

        // Update the pointer to point to the new array 
        aList = newList;

        sizeArray = sizeArray + ARRAY_INCREASE_AMOUNT; // Updates list size
    }

    aList[sizeList].setObjPos(thisPos);  // Inserting the element at the tail, index: sizeList
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
        aList[i].setObjPos(aList[i+1]);
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
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[sizeList - 1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    if (index < 0 || index >= sizeList)
    {
        return;
    }
    
    returnPos.setObjPos(aList[index]);
}