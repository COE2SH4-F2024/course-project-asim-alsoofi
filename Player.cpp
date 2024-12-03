#include "Player.h"
#include "objPosArrayList.h"
#include "Food.h"
#include "GameMechs.h"

Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    foodRef = thisFoodRef;
    playerPosList = new objPosArrayList();
    direction = STOP;

    objPos headPos(mainGameMechsRef -> getBoardSizeX() / 2, mainGameMechsRef -> getBoardSizeY() / 2,'@');
    // more actions to be included
    playerPosList->insertHead(headPos);
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
    playerPosList = nullptr;
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef -> getInput();
        // PPA3 input processing logic     
    switch(input){                      
            case 'w': case 'W':
                if (direction == LEFT || direction == RIGHT || direction == STOP)
                {
                    direction = UP;
                }
                break;
            case 'a': case 'A':
                if (direction == UP || direction == DOWN || direction == STOP)
                {
                    direction = LEFT;
                }
                break;
            case 's':  case 'S':
                if (direction == LEFT || direction == RIGHT || direction == STOP)
                {
                    direction = DOWN;
                }
                break;
            case 'd': case 'D':
                if (direction == UP || direction == DOWN || direction == STOP)
                {
                    direction = RIGHT;
                }
                break;
            default:
                break;
        }    
}

void Player::movePlayer()
{
    objPos head = playerPosList->getHeadElement();
    
    // PPA3 Finite State Machine logic
    if (direction == UP){
        head.pos->y -= 1;
        if (head.pos-> y == 0){
            head.pos-> y = mainGameMechsRef->getBoardSizeY() - 1;
        }
    }
    else if (direction == DOWN){
        head.pos->y += 1;
        if (head.pos-> y == mainGameMechsRef->getBoardSizeY()){
            head.pos-> y = 1;
        }
    }
    else if (direction == LEFT){
        head.pos->x -= 1;
        if (head.pos-> x == 0){
            head.pos-> x = mainGameMechsRef->getBoardSizeX() - 1;
        }
    }
    else if (direction == RIGHT){
        head.pos->x += 1;
        if (head.pos-> x == mainGameMechsRef->getBoardSizeX()){
            head.pos-> x = 1;
        }
    }


    if(head.pos->x == foodRef->getFoodPos().pos-> x && head.pos->y == foodRef->getFoodPos().pos-> y){
        playerPosList->insertHead(head);
        foodRef->generateFood(*playerPosList);
        mainGameMechsRef->incrementScore();
    }
    else{
        playerPosList->insertHead(head);
        playerPosList->removeTail();
    }

    if(checkSelfCollision()){
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
    }
}

// More methods to be added
// Self collision
bool Player::checkSelfCollision(){
    objPos head = playerPosList->getHeadElement();

    for(int i = 1; i < playerPosList->getSize(); i++) {
        objPos bodySegment = playerPosList->getElement(i);
        if(head.pos->x == bodySegment.pos->x && head.pos->y == bodySegment.pos->y){
            return true; // Collision Occurs
        } 
    }
    return false; // No Collision
}