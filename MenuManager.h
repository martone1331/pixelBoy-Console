#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <Arduino.h>
#include "GameEngine.h"
#include "Menu.h"
#include "MenuItem.h"
#include <stack>

class MenuManager{

    public:

        MenuManager();
        void openMenu(Menu* menu);
        void update();
        void draw();

    private:
        std::stack<Menu*> menuStack;
};

#endif