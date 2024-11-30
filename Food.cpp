#include "Food.h"
#include <cstdlib>  // For rand()
#include <ctime>    // For time()
#include <cstdlib>  // For rand()
#include <ctime>    // For time()
// Constructor: Initialize food position and symbol
Food::Food() {
    foodPos.pos->x = 2;           // Default x position
    foodPos.pos->y = 2;           // Default y position
    foodPos.symbol = 'o';    // Default symbol for food
    srand(time(nullptr));    // Seed the random number generator
}

// Destructor: If there's any dynamic memory, free it here (not necessary for this case)
Food::~Food() {}

// Generate a random position for food, avoiding the player's position
void Food::generateFood(objPos blockOff) {
    int x, y;
    char symbol = 'o';  // Food symbol
    bool unique = false;

    while (!unique) {
        unique = true;

        // Randomly generate x and y within bounds
        x = rand() % (20 - 2) + 1;  // x range [1, 18]
        y = rand() % (10 - 2) + 1;  // y range [1, 8]

        // Ensure the food doesn't overlap with the player (blockOff position)
        if (x == blockOff.pos->x && y == blockOff.pos->y) {
            unique = false;
            continue;
        }

        // If the position is unique, set the food's position
        foodPos.pos->x = x;
        foodPos.pos->y = y;
        foodPos.symbol = symbol;
    }
}

// Return the current food position
objPos Food::getFoodPos() const {
    return foodPos;
}
