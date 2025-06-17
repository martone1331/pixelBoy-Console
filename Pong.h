#ifndef PONG_H
#define PONG_H

#include <Arduino.h>
#include "Game.h"
#include "GameEngine.h"
#include "Menu.h"
#include "MenuItem.h"

class Pong : public Game{

    private:

        GameEngine& engine;

        Menu mainMenu;
        Menu cpuMenu;
        Menu* currentMenu;
        bool menuDone = false;

        int p1_option=0;
        int p2_option=1;

        //Game Variables
        
        bool onStart = true;
        int server = 0;
        int default_ball_x = 5;
        int default_ball_y = 3;
        int ball_x;
        int ball_y;
        int last_pos_x;
        int last_pos_y;
        
        int ball_vel_x = 0;
        int ball_vel_y = 0;
        int ball_speed = 120;
        unsigned long time_move_ball;
        
        int p1_score = 0;
        int p2_score = 0;
        int winScore = 5;
        boolean did_serve = false;
        
        //Variables for players:
        int p1_pos = 3;
        int p2_pos = 3;
        unsigned long time_move_p1;
        unsigned long time_move_p2;
        
        //Variables for CPU:
        unsigned long time_ai_move;
        unsigned long time_ai_move_p1;
        unsigned long pim_think_time = 140;
        unsigned long charlie_think_time = 55;
        
        // Add varience in their think time
        unsigned long pim_var;
        unsigned long pimp1_var;
        unsigned long charlie_var;
        unsigned long charliep1_var;
    

    public:
    //Constructor:
        Pong(GameEngine& engine);
        void startup() override;
        void update() override;
        void draw() override;    

        void playPong();

        void startAnimation();

        void drawPlayer1();
        void drawPlayer2();
        void drawScoreboard();
        void movePlayer1();
        void movePlayer2();

        void ai_move_pim();
        void ai_move_charlie();
        void ai_move_pim_p1();
        void ai_move_charlie_p1();

        void drawBall();
        void serve();
        void ballPhysics();
        void checkCollisionWall();
        void checkCollisionP1();
        void checkCollisionP2();

        void scoreAnimation();
        void checkWin();
        void winAnimation(String text);
        void loseSong();
        
        void resetBall();
        void resetScore();
        void resetGame();
};


#endif