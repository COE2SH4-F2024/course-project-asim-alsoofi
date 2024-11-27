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
}

// More methods to be added