#include "Menu.h"
#include "GameEngine.h"

Menu::Menu(GameEngine& engineRef, const char* title, std::vector<MenuItem> items): engine(engineRef), title(title), items(items){}

void Menu::update(){
  if (!menuStart){
    draw();
    menuStart = true;
    inputLocked = true;
    return;
  }

  if (inputLocked) {
    if (engine.button1 == HIGH && engine.button3 == HIGH){
      inputLocked = false;
    }
    return;
  }

  if (engine.time - menu_time > 400 && engine.joy_y == 1){
     moveUp();
     draw();
     engine.playNote(G4, 200);
     menu_time = millis();
  }
  if (engine.time - menu_time > 400 && engine.joy_y == -1){
      moveDown();
      draw();
      engine.playNote(G4, 200);
      menu_time = millis();
  }
  if (engine.button1 == LOW){
      isSelect = true;
      select();
      Serial.println("Selected!");
  }
  
  if (engine.button3 == LOW) {
      isBack = true;
  }
      
}

void Menu::draw(){
  engine.clearOLEDBuffer();
  engine.drawTextOLED(20, 0, title);

  for (int i = 0; i < items.size(); i++){
    const char* label = items[i].getLabel();
    if (i == menuSelect){
      engine.drawTextOLED(0, 20 + i*20, label, true);
    }
    else{
      engine.drawTextOLED(0, 20 + i*20, label, false);
    }
  }
}

void Menu::reset(){
  menuSelect = 0;
  currentSubmenu = nullptr;
}

Menu* Menu::getCurrentSubmenu(){
  return currentSubmenu;
}

void Menu::moveUp(){
  menuSelect = (menuSelect + 1) % items.size();
}

void Menu::moveDown(){
  menuSelect = (menuSelect + items.size() - 1) % items.size();
}

void Menu::select(){
  isSelect = false;
  MenuItem& item = items[menuSelect];
  item.runAction();
  Menu* submenu = item.getSubmenu();
  if (submenu) {
    currentSubmenu = submenu;
  } 
}