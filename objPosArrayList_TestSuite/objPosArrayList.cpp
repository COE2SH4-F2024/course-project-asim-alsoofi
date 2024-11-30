#include "objPosArrayList.h"
#include <iostream>
// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

// Purpose: 
objPosArrayList::objPosArrayList()
{
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;
    aList = new objPos[ARRAY_MAX_CAP];
}

// Purpose: 
objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

// Purpose: 
int objPosArrayList::getSize() const
{
    return listSize;
}

// Purpose: 
void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize >= arrayCapacity){
        return;
    }

    for(int i = listSize; i > 0; i--){
        aList[i] = aList[i - 1];
    }
    aList[0] = thisPos;
    listSize++; 
}

// Purpose: 
void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize >= arrayCapacity) {
        return;
    }

    aList[listSize] = thisPos;
    listSize++;
}

// Purpose: 
void objPosArrayList::removeHead()
{
    if(listSize == 0) {
        return;
    }

    for(int i = 0; i < listSize - 1; i++){
        aList[i] = aList[i + 1];
    }

    listSize--;
}

// Purpose: 
void objPosArrayList::removeTail()
{
    if(listSize == 0) {
        return;
    }

    listSize--;   
}

// Purpose: 
objPos objPosArrayList::getHeadElement() const
{
        return aList[0];
}

// Purpose: 
objPos objPosArrayList::getTailElement() const
{
        return aList[listSize - 1];
}

// Purpose: 
objPos objPosArrayList::getElement(int index) const
{
    if(index >=0 || index < listSize){
        return aList[index];
    }
    
}

// Not sure if I need to follow the rule of 4 here???