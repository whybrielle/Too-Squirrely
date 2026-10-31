//Author: Azariah unless otherwise stated
#include “FEHLCD.h”
#include “FEHImages.h”
#include “FEHUtility.h”
#include “iostream”
#include “player.h”
#include “stage.h”
#include “enemy.h”
#include “coins.h”
#include “string”
#include <random>
#include “Design.h”
class Display;
Stage::Stage(int stageNum):
   // Creates player character and enemy character
   player(squirrel, “assets/squirrel1.png”,
                  squirrel2, “assets/squirrel2.png”,
                  squirrelf, “assets/flip1.png”,
                  squirrel2f, “assets/flip2.png”,
                  10, 170)
{
// basic stage/level stats
this->stageNum = stageNum;
reset();
// add 14 coins and 3 enemies to vectors to each stage
   coins.emplace_back(coinImg, rand() % 319 + 1, 10);
   coins.emplace_back(coinImg, rand() % 319 + 1, 20);
   coins.emplace_back(coinImg, rand() % 319 + 1, 30);
   coins.emplace_back(coinImg, rand() % 319 + 1, 40);
   coins.emplace_back(coinImg, rand() % 319 + 1, 5);
   coins.emplace_back(coinImg, rand() % 319 + 1, 0);
   coins.emplace_back(coinImg, rand() % 319 + 1, 35);
   coins.emplace_back(coinImg, rand() % 319 + 1, 10);
   coins.emplace_back(coinImg, rand() % 319 + 1, 20);
   coins.emplace_back(coinImg, rand() % 319 + 1, 30);
   coins.emplace_back(coinImg, rand() % 319 + 1, 40);
   coins.emplace_back(coinImg, rand() % 319 + 1, 5);
   coins.emplace_back(coinImg, rand() % 319 + 1, 0);
   coins.emplace_back(coinImg, rand() % 319 + 1, 35);
}
//Updates stage information (player movement, coin locations, etc.); called by drawStage
//in a while loop to repeat until stage ends – Azariah
bool Stage::update(){
    if (!paused) {
        if(lives <= 0 || i >= seconds){
            return end;
        }
        drawStats(*this, stageNum);
        player.update();
        player.movePlayer();
        // for each coin in the coin vector draw a coin
        int numCoins=coins.size();
        if (stageNum==2) {
            numCoins=2;
        } else if (stageNum==3) {
            numCoins=1;
        }
        for (int j=0;j<numCoins;j++) {
            coins[j].drawCoin();
        }
        for(Coins &coin : coins){
            coin.drawCoin();
        }
        for(Enemy &enemy : enemies){
            if(enemy.alive && enemy.isTouching(player) && player.invincibleTimer == 0){
            lives–;
            player.invincibleTimer = Player::INVINCIBLE_TIME;
            }
        }
        // check for projectile-enemy collisions
        for(Enemy &enemy : enemies){
            if(enemy.alive){
                if(player.isHitting(enemy) && player.active){
                    player.active = false;
                    enemy.alive = false;
                    score += 100;
                }
                else {
                    enemy.goWalk(true);
                }
            }
        }
            // If player interacts with a coin
            for(Coins &coin : coins){
            if(!coin.touched && coin.hasCollectedCoin(player)){
                coin.touched = true;
                score += 200;
                res++;
            }
            coin.cy+=8;
            // if coin reaches ground and is not collected
            // fall from sky again
            if(coin.cy >= 190){
                coin.cy = 0;
                coin.cx = rand() % 319 + 1;
                coin.touched = false;
            }
        }
        i++;
        //Draws pause and play buttons- Carson
        LCD.SetFontScale(0.5);
        (*pausePtr).Draw();
        (*playPtr).Draw();
        LCD.SetFontScale(1);
        //
    }
    //Initializes exitStage button (not drawn yet) – Carson
    Button exitStage(“”, 124, 140, 70, 20, RED, WHITE, RED);
    float x, y;
    //Checks for touch
    if (LCD.Touch(&x,&y)) {
        if ((*pausePtr).icon.Pressed(x,y,1)) {
            //Pause, displays pause menu
            paused=true;
            Shape pauseMenu(100,65,119,100,GRAY);
            Show(&pauseMenu);
            Text txt(“Game Paused”, 124, 70, 4, 0.5, WHITE);
            txt.Draw();
            exitStage.Draw();
            Text ext(“Exit Stage”, 128, 140, 4, 0.5, WHITE);
            ext.Draw();
        } else if ((*playPtr).icon.Pressed(x,y,1)) {
            //hides pause menu, unpause
            paused=false;
        } else if (paused) {
            //exits if exitStage button pressed
            if (exitStage.icon.Pressed(x,y,1)) {
                return end;
            }
        }
    }
    //Calls to Stage member functions – Carson
    checkCollisions();
    checkWin();
    if (win) {
        //Breaks from while loop in drawStage
        return end;
    }
    //
    return !end;
    LCD.Update();
    Sleep(16);
}
// Displays the stats during gameplay – Azariah
void Stage::drawStats(Stage &stage, int n){
   if(stageNum == 1){
       stage1_background.Draw(0,0);
   } else if (stageNum==2) {
       stage2_background.Draw(0,0);
   } else if (stageNum==3) {
        stage3_background.Draw(0,0);
   }
   LCD.WriteAt(“SCORE”, 1, 1);
   LCD.WriteAt(stage.score, 15, 20);
   LCD.WriteAt(“RES”, 75, 1); // resources (coins)
   LCD.WriteAt(stage.res, 86, 20);
   LCD.WriteAt(“STAGE”, 120, 1);
   LCD.WriteAt(n, 145, 20);
   LCD.WriteAt(“TIME”, 191, 1);
   LCD.WriteAt(stage.seconds – i, 200, 20);
   LCD.WriteAt(“LIVES”, 255, 1);
   LCD.WriteAt(stage.lives, 280, 20);
}
//
/*Checks if player found an exit, calls exitPrompt to
determine if player wants to clear the stage. – Carson
*/
void Stage::checkWin() {
    if (stageNum==1) {
        if (player.getX()>=210 && player.getX() <=230) {
            if (player.getY()>=170 && player.getY()<=210) {
                exitPrompt(“Exit found!”);
            }
        }
    } else if (stageNum==2) {
        if (player.getX()>=125 && player.getX() <=155) {
            if (player.getY()>=150 && player.getY()<=210) {
                exitPrompt(“Easy exit.”);
            }
        } else if (player.x_pos>=270) {
            if (player.y_pos<=24) {
                exitPrompt(“Hidden exit!”);
                hiddenExitFound=true;
            }
        }
    } else if (stageNum==3) {
        if (player.getX()>=200 && player.getX() <=250) {
            if (player.getY()>=150 && player.getY()<=210) {
                exitPrompt(“Exit found.”);
            }
        } else if (player.getX()>=50 && player.getX()<=70) {
            if (player.getY()<=100) {
                exitPrompt(“Hidden exit!”);
            }
        }
    }
}
/*Displays prompt to screen, gives instructions
to press ENTER to clear stage. Called if player
is near an exit. – Carson
*/
void Stage::exitPrompt(string str) {
    Shape rect(72,65,179,40,GRAY);
    rect.layer=2;
    Show(&rect);
    Text txt1(str, 134, 70, 4, 0.5, WHITE);
    txt1.Draw();
    Text txt2(“Press ENTER to clear stage.”, 90, 85, 4, 0.5, WHITE);
    txt2.Draw();
    Keyboard.waitAnyKey();
    if (Keyboard.lastChar()==10) {
        win=true;
    }
}
//Calls changeMusic function to set and play music for the stage – Carson
void Stage::setMusic(){
    changeMusic(dPtr, musicPath[stageNum-1], musicDuration[stageNum-1], volume[stageNum-1]);
    (*(*dPtr).musicPtr).play();
}
//Depending on stage, allows player to land on platforms – Carson
bool Stage::checkCollisions(){
    if (stageNum==2) {
        //Checks if player lands on first tree
        if (player.x_pos>= 55 && player.x_pos<=60) {
            if (player.y_pos<=160) {
                if (player.y_pos>130) {
                    player.groundYPos=160;
                } else {
                    player.groundYPos=130;
                }
            }
        //Checks if player lands on second tree
        } else if (player.x_pos>=292 && player.x_pos<=297 && player.y_pos<=160 && player.y_pos>120) {
            if (player.y_pos>130) {
                player.groundYPos=160;
            } else if (player.y_pos<=130) {
                player.groundYPos=130;
            }
        //Checks if player falls off top platform
        }else if (player.x_pos<170 && player.groundYPos==22) {
            player.groundYPos=102;
        //Checks if player lands on other platforms
        } else if (player.x_pos>= 100 && player.x_pos<=319) {
            if (player.y_pos<=102) {
                if (player.y_pos>=70) {
                    player.groundYPos=102;
                } else if (player.x_pos>=140 && player.y_pos<=22) {
                    player.groundYPos=22;
                } else if (player.x_pos<=140 &&player.y_pos>22 && player.y_pos<60) {
                    player.groundYPos=102;
                } else if (player.y_pos>=60) {
                    if (player.x_pos>=183 && player.x_pos<=210) {
                        player.groundYPos=62;
                    } else if (player.x_pos>=230 && player.x_pos<=250) {
                        player.groundYPos=62;
                    } else if (player.x_pos>=270 && player.x_pos<=290) {
                        player.groundYPos=62;
                    } else {
                        player.groundYPos=102;
                    }
                }
            //Checks if player falls off second tree
            } else if (player.groundYPos==130 || player.groundYPos==160) {
                if (player.x_pos<292 || player.x_pos>297) {
                    player.groundYPos=startingGroundPos;
                }
            }
        //if not on platform, player falls back to ground
        } else {
            player.groundYPos=startingGroundPos;
        }
    } else if (stageNum==3) {
        //Checks if on hood of Donatos truck
        if (player.x_pos>=165 && player.x_pos<=180){
            if (player.y_pos<=160) {
                player.groundYPos=160;
            }
        //Checks if on roof of Donatos truck
        } else if(player.x_pos>=167 && player.x_pos<270) {
            if (player.y_pos<=125) {
                player.groundYPos=125;
            }
        //Checks if on clock tower
        } else if (player.x_pos>=10 && player.x_pos <=130) {
            if (player.y_pos<=95) {
                player.groundYPos=95;
            }
        } else {
            player.groundYPos=startingGroundPos;
        }
    }
}
// When called in background or display, it draws the stage and starts the game – Azariah
void drawStage(Stage *s){
    (*s).setMusic();
    int tI=TimeNow();
    (*(*s).dPtr).currentStage=(*s).stageNum;
    LCD.Clear();
    while(s->update()){
        //Loops music – Carson
        int tF=TimeNow();
        if (tF>=tI+(*s).musicDuration[(*s).stageNum-1]) {
            (*(*((*s).dPtr)).musicPtr).pause();
            tI=tF;
            (*(*((*s).dPtr)).musicPtr).play();
        }
        //
    }
    gameOver(s);//Ends game, switches screen – Carson
}
//If level was cleared (win==true), show nextStageScreen.
//Otherwise, gameOverScreen – Carson
void gameOver(Stage *s){
    (*(*s).dPtr).inStage=false;
    if ((*s).win) {
        (*(*s).dPtr).nextStageScreen=true;
    } else {
        (*(*s).dPtr).gameOverScreen=true;
    }
    (*s).reset();
    LCD.Clear();
}
//Resets Stage data – Written by Azariah, moved in function by Carson
void Stage::reset() {
    score = 0;
    res = 0;
    lives = 3;
    score = 0;
    if (stageNum==1) {
        seconds=400;
    } else if (stageNum==2) {
        seconds=600;
    } else if (stageNum==3) {
        seconds=800;
    }
   player.x_pos=10;
   player.y_pos=170;
    win=false;
    end = false;
    i=0;
    paused=false;
   stage1_background.Open(“assets/northrec.png”);
   stage2_background.Open(“assets/traditions.png”);
   stage3_background.Open(“assets/clocktower.png”);
   //Resets enemies
   vector<Enemy> newEnemies;
   newEnemies.emplace_back(enemyf1, “assets/michi1.png”, enemyf2, “assets/michi2.png”, 150, 190);
   newEnemies.emplace_back(enemyf1, “assets/michi1.png”, enemyf2, “assets/michi2.png”, 240, 190);
   newEnemies.emplace_back(enemyf1, “assets/michi1.png”, enemyf2, “assets/michi2.png”, 200, 190);
   newEnemies.emplace_back(enemyf1, “assets/michi1.png”, enemyf2, “assets/michi2.png”, 300, 190);
   enemies=newEnemies;
}
