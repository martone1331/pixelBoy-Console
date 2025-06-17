#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include <functional>
#include "GameEngine.h"
#include "pitches.h"
#include "MenuItem.h"

class Menu {
    public:
        Menu(GameEngine& engine, const char* title, std::vector<MenuItem> items);

        void update();
        void draw();
        void reset();
        Menu* goBack();

        Menu* getCurrentSubmenu();

        bool isSelect = false;
        bool isBack = false;

    
    private:
        GameEngine& engine;
        const char* title;
        std::vector<MenuItem> items;
        int menuSelect = 0;
        bool menuStart = false;

        unsigned long menu_time;
        unsigned long input_time;
        bool inputLocked = false;

        Menu* currentSubmenu = nullptr;

        void moveUp();
        void moveDown();
        void select();
        
};

#endif