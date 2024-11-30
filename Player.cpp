#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    direction = STOP;
    

    // more actions to be included
    objPos playerPos(mainGameMechsRef -> getBoardSizeX() / 2, mainGameMechsRef -> getBoardSizeY() / 2,'@');
}


Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
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
    // PPA3 Finite State Machine logic
        if (direction == UP){
        playerPos.pos->y -= 1;
        if (playerPos.pos->y == 0){
            playerPos.pos->y = 8;
        }
    }
    else if (direction == DOWN){
        playerPos.pos->y += 1;
        if (playerPos.pos->y == 9){
            playerPos.pos->y = 1;
        }
    }
    else if (direction == LEFT){
        playerPos.pos->x -= 1;
        if (playerPos.pos->x == 0){
            playerPos.pos->x = 18;
        }
    }
    else if (direction == RIGHT){
        playerPos.pos->x += 1;
        if (playerPos.pos->x == 19){
            playerPos.pos->x = 1;
        }
    }
}

// More methods to be added