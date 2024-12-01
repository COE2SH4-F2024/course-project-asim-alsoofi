#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
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
    switch(input)
        {                      
            case 'w': 
            case 'W':
                if (direction == LEFT || direction == RIGHT || direction == STOP)
                {
                    direction = UP;
                }
                break;
            case 'a':
            case 'A':
                if (direction == UP || direction == DOWN || direction == STOP)
                {
                    direction = LEFT;
                }
                break;
            case 's':
            case 'S':
                if (direction == LEFT || direction == RIGHT || direction == STOP)
                {
                    direction = DOWN;
                }
                break;
            case 'd':
            case 'D':
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
        if (head.pos->y == 0){
            head.pos->y = 8;
        }
    }
    else if (direction == DOWN){
        head.pos->y += 1;
        if (head.pos->y == 9){
            head.pos->y = 1;
        }
    }
    else if (direction == LEFT){
        head.pos->x -= 1;
        if (head.pos->x == 0){
            head.pos->x = 18;
        }
    }
    else if (direction == RIGHT){
        head.pos->x += 1;
        if (head.pos->x == 19){
            head.pos->x = 1;
        }
    }

    playerPosList->insertHead(head);
}

// More methods to be added