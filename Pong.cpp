#include "Pong.h"
#include "pitches.h"
#include "Menu.h"

Pong::Pong(GameEngine& engineRef) : 
engine(engineRef), 
mainMenu(engineRef, "Pong:",{
    MenuItem("2-Player", [this](){p2_option = 0; menuDone = true;}),
    MenuItem("CPU", [this](){currentMenu = &cpuMenu;}),
}),
cpuMenu(engineRef, "Pong:",{
    MenuItem("Pim", [this](){p2_option = 1; menuDone = true;}),
    MenuItem("Charlie", [this](){p2_option = 2; menuDone = true;}),
}),
currentMenu(&mainMenu)
{
    ball_x = default_ball_x;
    ball_y = default_ball_y;
    }

/*===========================================
  ==--------------GAME METHODS-------------==
  =========================================== */

    void Pong::startup(){
      startAnimation();
      resetBall();
      drawScoreboard();
    }

    void Pong::update() {
        playPong();
    }

    void Pong::draw() {
        drawPlayer1();
        drawPlayer2();
        drawBall();
        engine.renderFrame();
        engine.clearPixels();
        //engine.clearOLEDBuffer();
    }

    void Pong::playPong(){
        if (onStart == true){
            startup();
            onStart = false;
        }
        if (p1_option == 0) movePlayer1();
        else if (p1_option == 1) ai_move_pim_p1();
        else if (p1_option == 2) ai_move_charlie_p1();

        if (p2_option == 0) movePlayer2();
        else if (p2_option == 1)  ai_move_pim();
        else if (p2_option == 2)  ai_move_charlie();

        draw();
        ballPhysics();
        serve();
    }

    void Pong::startAnimation(){
      for (int j = 0; j < 8; j++){
        for (int i = 0; i < 16; i++){
          engine.setPixel(i, j, 1);
          engine.renderFrame();
          delay(10);
        }
      }
    }
/*===========================================
  ==-------------PLAYER METHODS------------==
  =========================================== */

    void Pong::drawPlayer1(){
        for (int i = p1_pos; i < p1_pos+3; i++){
          engine.setPixel(0, i, 1);
        }
      }
      
    void Pong::drawPlayer2(){
    for (int i = p2_pos; i < p2_pos+3; i++){
        engine.setPixel(15, i, 1);
      }
    }

    void Pong::drawScoreboard(){
      engine.clearOLEDBuffer();
      String p1_score_text = String(p1_score);
      String p2_score_text = String(p2_score);
      engine.drawTextOLED(34,20, "SCORE:");
      engine.drawTextOLED(40,50, p1_score_text.c_str());
      engine.drawTextOLED(60,50, " - ");
      engine.drawTextOLED(82,50, p2_score_text.c_str());
      engine.sendOLEDBuffer();
    }
    
    void Pong::movePlayer1(){
        if (engine.time - time_move_p1 > 100 && engine.joy_y == 1 && p1_pos < 5){
            p1_pos = p1_pos + 1;
            time_move_p1 = millis();
        }
        
        if (engine.time - time_move_p1 > 100 && engine.joy_y == -1 && p1_pos > 0){
            p1_pos = p1_pos - 1;
            time_move_p1 = millis();
        }
    }
    
    void Pong::movePlayer2(){
        if (engine.time - time_move_p2 > 100 && engine.button1 == LOW && p2_pos < 5){
            p2_pos = p2_pos + 1;
            time_move_p2 = millis();
        }
        
        if (engine.time - time_move_p2 > 100 && engine.button4 == LOW && p2_pos > 0){
            p2_pos = p2_pos - 1;
            time_move_p2 = millis();
        }
    }
    
  /*===========================================
  ==----------------AI METHODS---------------==
  ============================================= */
    
    //Easier AI that plays safe
    void Pong::ai_move_pim(){
        if (engine.time - time_ai_move > pim_think_time + pim_var){
            if (p2_pos+1 < ball_y && p2_pos < 5){
                p2_pos = p2_pos + 1;
            }
            if (p2_pos+1 > ball_y && p2_pos > 0){
                p2_pos = p2_pos - 1;
            }
            time_ai_move = millis();
            pim_var = random(10, 40);
        }
    }
    
    //Aggressive AI that goes for speed ups
    void Pong::ai_move_charlie(){
        if (engine.time - time_ai_move > charlie_think_time + charlie_var){
            if (p2_pos+2 < ball_y && p2_pos < 5){
                p2_pos = p2_pos + 1;
            }
            if (p2_pos > ball_y && p2_pos > 0){
                p2_pos = p2_pos - 1;
            }
            time_ai_move = millis();
            charlie_var = random(5,20);
        }
        if (ball_vel_y == 0 && p2_pos+1 == ball_y && ball_y <6){
            p2_pos = p2_pos + 1;
         }
        if (ball_vel_y == 0 && p2_pos+1 == ball_y && ball_y >1){
            p2_pos = p2_pos - 1;
            }
    }
    
    void Pong::ai_move_pim_p1(){
        if (engine.time - time_ai_move_p1 > pim_think_time + pimp1_var){
            if (p1_pos+1 < ball_y && p1_pos < 5){
                p1_pos = p1_pos + 1;
            }
            if (p1_pos+1 > ball_y && p1_pos > 0){
                p1_pos = p1_pos - 1;
            }
            time_ai_move_p1 = millis();
            pimp1_var = random(20, 50);
        }
    }
    //Player 1 Version of Charlie
    void Pong::ai_move_charlie_p1(){
        if (engine.time - time_ai_move_p1 > charlie_think_time + charliep1_var){
            if (p1_pos+2 < ball_y && p1_pos < 5){
            p1_pos = p1_pos + 1;
            }
            if (p1_pos > ball_y && p1_pos > 0){
            p1_pos = p1_pos - 1;
            }
            time_ai_move_p1 = millis();
            charliep1_var = random(10,30);
        }
        if (ball_vel_y == 0 && p1_pos+1 == ball_y && ball_y <6){
            p1_pos = p1_pos + 1;
        }
        if (ball_vel_y == 0 && p1_pos+1 == ball_y && ball_y >1){
            p1_pos = p1_pos - 1;
        }
    }
  
  /*===========================================
  ==--------------BALL METHODS---------------==
  =========================================== */
    
    void Pong::drawBall(){
        if (ball_y > 7){
            engine.setPixel(ball_x, 7, 1);
        }
        else if (ball_y < 0){
            engine.setPixel(ball_x, 0, 1);
        }
        else {
            engine.setPixel(ball_x, ball_y, 1);
        }
    }
    
    void Pong::serve(){
        if (did_serve == false){
            if (engine.button2 == LOW){
                ball_vel_x = -1;
                did_serve = true;
            }
        }
    }
    
    void Pong::ballPhysics(){
        if (engine.time - time_move_ball > ball_speed){
            checkCollisionP1();
            checkCollisionP2();
            checkCollisionWall();
            ball_x = ball_x + ball_vel_x;
            ball_y = ball_y + ball_vel_y;
            time_move_ball = millis();
        }
    }
    
    void Pong::checkCollisionWall(){
        if (ball_y >= 7 || ball_y <= 0){
            ball_vel_y = -1*ball_vel_y;
        }
    }
    
    void Pong::checkCollisionP1(){
        if (ball_x == 1){
            engine.playNote(C4, 200);
                if(ball_y == p1_pos || (ball_y < 0 && p1_pos == 0)){
                    ball_vel_x = 1; 
                    if (ball_vel_y > -2){
                        ball_vel_y = ball_vel_y - 1;
                    }
                }
                else if(ball_y == p1_pos+1){
                    ball_vel_x = 1; 
                }
                else if(ball_y == p1_pos+2 || (ball_y > 7 && p1_pos == 5)){
                    ball_vel_x = 1; 
                    if (ball_vel_y < 2){
                        ball_vel_y = ball_vel_y + 1;
                    }
                }
                else {
                    loseSong();
                    scoreAnimation();
                    resetBall();
                    p2_score = p2_score + 1;
                    drawScoreboard();
                    checkWin();
            }
        }
    }
    
    void Pong::checkCollisionP2(){
        if (ball_x == 14){
            engine.playNote(C4, 200);
        
            if(ball_y == p2_pos || (ball_y < 0 && p2_pos == 0)){
                ball_vel_x = -1; 
                if (ball_vel_y > -2){
                    ball_vel_y = ball_vel_y - 1;
                }
            }
            else if(ball_y == p2_pos+1){
            ball_vel_x = -1; 
            }
            else if(ball_y == p2_pos+2 || (ball_y > 7 && p2_pos == 5)){
            ball_vel_x = -1; 
                if (ball_vel_y < 2){
                    ball_vel_y = ball_vel_y + 1;
                }
            }
            else {
                loseSong();
                scoreAnimation();
                resetBall();
                p1_score = p1_score + 1;
                drawScoreboard();
                checkWin();
            }
        }
    }
    
    void Pong::checkWin(){
      Serial.println("Checking win....");
      if (p1_score >= winScore){
        winAnimation("Player 1");
      }
      else if (p2_score >= winScore){
        winAnimation("Player 2");
      }
    }

    void Pong::winAnimation(String text){
      for (int i = 0; i < 16; i++){
        for (int j = 0; j < 8; j++){
          engine.setPixel(i, j, 1);
          engine.renderFrame();
          delay(20);
        }
      }
      engine.clearOLEDBuffer();
      engine.drawTextOLED(38,20, text.c_str());
      engine.drawTextOLED(48,50, "Wins!");
      engine.sendOLEDBuffer();
      delay(3000);
      resetGame();
    }

    void Pong::scoreAnimation(){
        for (int i=0; i < 3; i++){
            engine.setPixel(ball_x, ball_y, 0);
            drawPlayer1();
            drawPlayer2();
            engine.renderFrame();
            delay(200);
            engine.setPixel(ball_x, ball_y, 1);
            drawPlayer1();
            drawPlayer2();
            engine.renderFrame();
            delay(200);
        }
    }
    
    void Pong::loseSong(){
        engine.playNote(B4, 200);
        delay(200);
        engine.playNote(A4, 200);
    }
    
    void Pong::resetBall(){
        ball_x = default_ball_x;
        ball_y = default_ball_y;
        ball_vel_x = 0;
        ball_vel_y = 0;
        did_serve = false;
    }

    void Pong::resetScore(){
        p1_score = 0;
        p2_score = 0;
    }

    void Pong::resetGame(){
        resetScore();
        drawScoreboard();
    }