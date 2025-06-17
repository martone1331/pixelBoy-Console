#ifndef MENUITEM_H
#define MENUITEM_H

#include <Arduino.h>
#include <functional>
#include "GameEngine.h"
#include "pitches.h"

class Menu;

class MenuItem{
    public:
        MenuItem(const char* label, std::function<void()> action = nullptr, Menu* submenu = nullptr);

        const char* getLabel() const;
        void runAction();
        Menu* getSubmenu();

    private:
        const char* label;
        std::function<void()> action;
        Menu* submenu;
};

#endif