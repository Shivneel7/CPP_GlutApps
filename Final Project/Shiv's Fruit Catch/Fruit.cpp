#include "Fruit.h"
#include <iostream>
#include <time.h>

Fruit::Fruit() : MovingSprite("banana1.png", 1, 1, 0, 1, .1, .1, 0, -.01, fruit) {
    srand(time(NULL));
    x = (rand() % 190) / 100.0 - 1.0;
    // std::cout << x << std::endl;
}