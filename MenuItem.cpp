#include "MenuItem.h"
#include "Menu.h"

MenuItem::MenuItem(const char* label, std::function<void()> action, Menu* submenu )
    : label(label), action(action), submenu(submenu){}

const char* MenuItem::getLabel() const{
    return label;
}

void MenuItem::runAction(){
    if(action){
        action();
    }
}

Menu* MenuItem::getSubmenu() {
    return submenu;
}
