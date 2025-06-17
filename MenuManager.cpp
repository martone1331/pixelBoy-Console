
#include "MenuManager.h"


MenuManager::MenuManager(){}

void MenuManager::openMenu(Menu* menu){
    menuStack.push(menu);
}

void MenuManager::update(){
    if (menuStack.empty()) return;

    Menu* currentMenu = menuStack.top();
    currentMenu->update();

    if (currentMenu->isSelect == true){
        Menu* submenu = currentMenu->getCurrentSubmenu();
        if (submenu){
            submenu->reset();
            menuStack.push(submenu);
        }
    }
    if (currentMenu->isBack == true && menuStack.size() > 1){
        currentMenu->isBack = false;
        menuStack.pop();
    }

}

void MenuManager::draw(){
    if (!menuStack.empty()){
        menuStack.top()->draw();
    }
}