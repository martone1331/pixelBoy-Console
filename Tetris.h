#ifndef TETRIS_H
#define TETRIS_H

#include <Arduino.h>
#include "GameEngine.h"
#include "Game.h"

class Tetris : public Game {

    private:
        GameEngine& engine;
    // =====SHAPES=====:

    // All shapes have 4 blocks, with the first 4 numbers being their spawned x coordinates and the last 4 being their y's.
    // Origin of rotation is always the first point

        int shapes[7][8] =  {
        //SQUARE
        {15,15,14,14,3,4,3,4},
        //LINE
        {14,14,14,14,2,3,4,5},
        //REVERSE-Z
        {14,14,15,15,4,3,4,5},
        //Z
        {14,15,15,14,4,3,4,5},
        //REVERSE-L
        {14,14,14,15,4,3,5,5},
        //L
        {14,15,14,14,4,3,3,5},
        //T
        {14,14,15,14,4,3,4,5}
        };
        
        int blocks[16][8];
        
        // =====PLAYER VARIABLES=====:
        
        int player_shape[8];
        int player_shape_num;
        boolean assigned_shape = false;
        
        unsigned long time_last_move_y;
        unsigned long time_last_move_p;
        unsigned long time_last_move_x;
        unsigned long time_last_rotate;

        int p_speed = 120;
        int speed = 1000;
        
        int score = 0;
        int level = 1;
        int cleared_rows = 0;
        


    public:
        //Constructor
        Tetris(GameEngine& engine);

        void startup() override;
        void update() override;
        void draw() override;

        void drawShape(int shape[]);
        void rotateShape();
        void assignShape();
        void drawBlocks();
        void playerPhysics();
        void movePlayerDown();
        void movePlayerLateral();
        bool canMoveL();
        bool canMoveR();
        void checkToBlocks();
        int getScore(int rows, int level);
        bool canMoveDown();
        int checkRows();
        void clearAnimation(int row);
        void shiftRowsDown(int lowest_row);
        void clearRow(int row[]);
        void clearAll();
        bool rowFull(int row[]);
};

#endif