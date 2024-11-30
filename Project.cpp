#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer; // Global pointer for a player object on the heap
GameMechs *myGM;
Food *food;



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

    food = new Food();
    food ->generateFood(myPlayer -> getPlayerPos());
}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    
}

void DrawScreen(void){
    MacUILib_clearScreen();   
    int i, j;

    objPos playerPos = myPlayer -> getPlayerPos();
    objPos foodPos = food -> getFoodPos();

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
                        if (foodPos.pos-> x == j && foodPos.pos-> y == i) {
                            MacUILib_printf("%c", foodPos.symbol);
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
    delete food;

    MacUILib_uninit();
}
