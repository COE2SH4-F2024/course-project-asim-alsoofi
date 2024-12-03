#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "Food.h"
#include "GameMechs.h"

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
    food = new Food(myGM);
    myPlayer = new Player(myGM, food);

    
    food ->generateFood(*myPlayer -> getPlayerPos());
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
    bool objectFound;

    objPosArrayList* playerPosList = myPlayer -> getPlayerPos();
    objPos playerHead = playerPosList->getHeadElement();
    int playerSize = playerPosList->getSize();
    int BoardX = myGM->getBoardSizeX();
    int BoardY = myGM->getBoardSizeY();
    
    objPos foodPos = food -> getFoodPos();

    MacUILib_printf("Welcome to the snake game!\nRules are simple:\n- Don't collide with the border \n- Don't bite your own tail (or body)\n- Eat the food (x) and get the highest possible score!");
    MacUILib_printf("\nSettings: Up - w/W, Down - s/S, Left - a/A, Right - d/D, Quit - Spacebar\n");
    for(i = 0; i <= BoardY; i++)
    {
        for(j = 0; j <= BoardX; j++)
        {
            objectFound = false;
            for(int k = 0; k < playerSize; k++){
                objPos thisSeg = playerPosList->getElement(k);
                if(i == thisSeg.pos -> y && j == thisSeg.pos -> x){
                    MacUILib_printf("%c", thisSeg.symbol);
                    objectFound = true;
                    break;
                }
            }
            //food implementation
            if(!objectFound && i == foodPos.pos -> y && j == foodPos.pos-> x){
                MacUILib_printf("%c", foodPos.symbol);
                objectFound = true;
            }

            if(objectFound){
                continue;
            }
            else if(i == 0 || j == 0 || j == BoardX || i == BoardY){
                MacUILib_printf("#");
            }
            else{
               MacUILib_printf(" "); 
            }
        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("Score: %d", myGM -> getScore());

    if(myGM -> getExitFlagStatus()){
        MacUILib_clearScreen();
        if(myGM -> getLoseFlagStatus()){    
        MacUILib_printf("\nYou bit your own tail Game Over :(\nScore: %d", myGM -> getScore());
    }  
        else{
            MacUILib_printf("You are quitting:( Why???\nScore: %d", myGM -> getScore());
        } 
    }
    
    
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    delete myPlayer;
    delete myGM;
    delete food;

    MacUILib_uninit();
}
