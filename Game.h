#ifndef GAME_H
#define GAME_H

#include <Arduino.h>

class Game{

    public:
    //=====CORE GAME METHODS=====:
        virtual void update() = 0;
        virtual void draw() = 0;
        virtual void startup() = 0;   
        virtual ~Game();
};

#endif