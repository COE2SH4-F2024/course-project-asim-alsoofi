#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "player.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer; // Global pointer for a player object on the heap
GameMechs *myGM;


objPos food[5];                // Array to hold up to 5 food items
int foodCount = 2;             // Track how many food items are in the food array
 

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM -> getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen(); 
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs();
    myPlayer = new Player(myGM);

    food[0] = objPos(10, 3, 'o');  // Food at (10, 3) with symbol '@'
    food[1] = objPos(7, 7, 'o');   // Another food at (7, 7)
}

void GetInput(void)
{
  myGM->setInput(myGM->getInput());
}

void RunLogic(void)
{
    if(myGM->getInput() != 0)
    {
        if(myGM->getInput() == ' '){ 
            myGM->setExitTrue();
        }
        myPlayer->updatePlayerDir();
        myGM->clearInput();
    }
    myPlayer->movePlayer();
}

void DrawScreen(void){
    MacUILib_clearScreen();   
    int i, j;

    objPos playerPos = myPlayer -> getPlayerPos();
    
    // Loops through the rows
    for(i = 0; i < 10; i++){
        // Loops through the columns
        for(j = 0; j < 20; j++){
            // Drawing Top and bottom border
            if(i == 0 || i == 9) {
                MacUILib_printf("#");
            }
            else {
                if (j == 0 || j == 19) {
                    MacUILib_printf("#");
                }
                else if (i == playerPos.pos-> y && j == playerPos.pos -> x) {
                    MacUILib_printf("%c", playerPos.getSymbol());
                }
                else {
                    bool objectFound = false;
                    
                    // for the food
                    for(int k = 0; k < 5; k++){
                        if (food[k].getObjPos().pos-> x == j && food[k].getObjPos().pos-> y == i) {
                            MacUILib_printf("%c", food[k].getSymbol());
                            objectFound = true;
                            break;                        
                        }
                    }
                    if(!objectFound) {
                        MacUILib_printf(" ");
                    }
                }
            }
        }
        MacUILib_printf("\n");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    // delete stuff

    delete myPlayer;
    delete myGM;

    MacUILib_uninit();
}
