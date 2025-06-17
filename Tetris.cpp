#include "Tetris.h"
#include "pitches.h"

    Tetris::Tetris(GameEngine& engineRef) : engine(engineRef){}

    void Tetris::startup(){

    }

    void Tetris::update(){
        if (engine.button1 == LOW){
            clearAll();
          }
        engine.getTime();
        engine.getInputs();  
        draw();
        playerPhysics();
        assignShape();
    }

    void Tetris::draw(){
        drawShape(player_shape);
        drawBlocks();
        engine.renderFrame();
        engine.clearPixels();
    }

    void Tetris::drawShape(int shape[]){
        for (int i = 0; i < 4; i++){
        engine.setPixel(shape[i], shape[i+4],1);
        }
    }
  
    void Tetris::rotateShape(){
        int holder[8];
        if (player_shape_num == 0){
            return;
        }
        if (player_shape_num == 1){
            int dx = player_shape[5] - player_shape[6];
            int dy = player_shape[1] - player_shape[2];
            //(x,y) of the left-middle block
            holder[5] = player_shape[5] - dx;
            holder[1] = player_shape[1] - dy;
            //(x,y) of the right-middle block
            holder[6] = player_shape[6] - dy;
            holder[2] = player_shape[2] + dx;
            //(x,y) of the left block
            holder[4] = holder[5] + dy;
            holder[0] = holder[1] - dx;
            //(x,y) of the right block
            holder[7] = holder[6] - dy;
            holder[3] = holder[2] + dx;
        }
        //Do the rotations for blocks that rotate in a 3x3 area
        if (player_shape_num >= 2 && player_shape_num <= 6){
            holder[0] = player_shape[0];
            holder[4] = player_shape[4];
    
            for(int i = 1; i< 4; i++){
                int dx = player_shape[i] - player_shape[0];
                int dy = player_shape[i+4] - player_shape[4];
                holder[i+4] = player_shape[4]+ dx;
                holder[i] = player_shape[0] - dy;
            }
        }
        // If the piece will be out of bounds after rotating, move it in bounds (only possible with a few shapes and positions)
        for (int i=0; i<4; i++){
            if (holder[i+4] < 0){
                for (int j = 0; j<4; j++){
                    holder[j+4] = holder[j+4]+1;
                }
            }
            else if (holder[i+4] > 7){
                for (int j = 0; j<4; j++){
                    holder[j+4] = holder[j+4]-1;
                }
            }
            if (player_shape[i] < 0){
                for (int k = 0; k<4; k++){
                holder[k] = holder[k]+1;
                }
            }
        }
        //Check to see if there will be collision with a placed block
        for (int i=0; i<4; i++){
            if (blocks[holder[i]][holder[i+4]] == 1){
                return;
            }
        }
        //Set the player piece to the rotated piece
        for (int i=0; i<8;i++){
            player_shape[i] = holder[i];
        }
    }
    
    void Tetris::assignShape(){
        if (assigned_shape == false){
            player_shape_num = random(0,7);
            //player_shape_num = 1;
            for (int i=0; i < 8; i++){
                player_shape[i] = shapes[player_shape_num][i];
            }
            assigned_shape = true;
        }
    }
    
    void Tetris::drawBlocks(){
        for (int i=0; i < 16; i++){
            for(int j=0; j < 8; j++){
                if(blocks[i][j] == 1){
                    engine.setPixel(i, j, 1);
                }
            }
        }
    }
    
    //=====PLAYER FUNCTIONS=====
    
    void Tetris::playerPhysics(){
        if (engine.time - time_last_move_p > p_speed && engine.joy_x == -1){
            checkToBlocks();
            movePlayerDown();
            time_last_move_p = millis();
            time_last_move_y = millis();
            }
        if (engine.time - time_last_move_y > speed){
            checkToBlocks();
            movePlayerDown();
            time_last_move_y = millis();
        }
        if (engine.time - time_last_move_x > 120){
            movePlayerLateral();
            time_last_move_x = millis();
        }
        if (engine.time - time_last_rotate > 200 && engine.joy_x == 1){
            rotateShape();
            time_last_rotate = millis();
        }
    }
    
    void Tetris::movePlayerDown(){
        for (int i = 0; i<4; i++){
            player_shape[i] = player_shape[i]-1;
        }
    }
    
    void Tetris::movePlayerLateral(){
        if (engine.joy_y == 1 && canMoveR() == true){
            for (int i = 4; i<8; i++){
                player_shape[i] = player_shape[i]+1;
            }
        }
        if (engine.joy_y == -1 && canMoveL() == true){
            for (int i = 4; i<8; i++){
                player_shape[i] = player_shape[i]-1;
            }
        }
    }
    
    bool Tetris::canMoveL(){
        for (int i=0; i<4; i++){
            if (player_shape[i+4] <= 0 || blocks[player_shape[i]][player_shape[i+4]-1] == 1){
                return false;
            }
        }
        return true;
    }
    
    bool Tetris::canMoveR(){
        for (int i=0; i<4; i++){
            if (player_shape[i+4] >= 7 || blocks[player_shape[i]][player_shape[i+4]+1] == 1){
                return false;
            }
        }
        return true;
    }
    
    // =====GAME FUNCTIONS=====
    
    void Tetris::checkToBlocks(){
        if (canMoveDown() == false){
            for (int i = 0; i<4; i++){
                blocks[player_shape[i]][player_shape[i+4]] = 1;
            }
            assigned_shape = false;
            score = score + getScore(checkRows(), level);
            Serial.println(score);
        }
    }
    
    int Tetris::getScore(int rows, int level){
        if (rows == 1){
            return 40*level;
        }
        else if (rows == 2){
            return 100*level;
        }
        else if (rows == 3){
            return 300*level;
        }
        else if (rows == 4){
            return 1200*level;
        }
        else{
            return 0;
        }
    }
    
    bool Tetris::canMoveDown(){ 
    for (int i=0; i<4; i++){
            if (player_shape[i] <= 0 || blocks[player_shape[i]-1][player_shape[i+4]] == 1){
                return false;
            }
        }
        return true;
    }
    
    int Tetris::checkRows(){
        int cleared_rows = 0;
        for (int i = 0; i < 16; i++){
            if(rowFull(blocks[i]) == true){
                clearRow(blocks[i]);
                clearAnimation(i);
                shiftRowsDown(i);
                cleared_rows = cleared_rows + 1;
                i = 0;
            }
        }
        return cleared_rows;
    }
    
    void Tetris::clearAnimation(int row){
        for (int i = 0; i < 8; i++){
            engine.setPixel(row, i, 0);
        }
        drawBlocks();
        engine.renderFrame();
        delay(200);
        for (int i = 0; i < 8; i++){
            engine.setPixel(row, i, 1);
        }
        drawBlocks();
        engine.renderFrame();
        delay(200);
    }
    
    void Tetris::shiftRowsDown(int lowest_row){
        for (int i = lowest_row; i < 15; i++){
            for (int j = 0; j < 8; j++){
                blocks[i][j] = blocks[i+1][j];
            }
        }
    }
    
    void Tetris::clearRow(int row[]){
        for(int i = 0; i < 8; i++){
            row[i] = 0;
        }
    }
    
    void Tetris::clearAll(){
        for(int i = 0; i < 16; i++){
            for(int j = 0; j < 8; j++){
                blocks[i][j] = 0;
            }
        }
    }
    
    bool Tetris::rowFull(int row[]){
        for (int i = 0; i < 8; i++){
            if(row[i] == 0){
                return false;
            }
        }
        return true;
    }
    