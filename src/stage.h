//Header file for Stage class
//Author: Azariah unless otherwise stated
#ifndef STAGE_H
#define STAGE_H
#include “FEHLCD.h”
#include “FEHImages.h”
#include “FEHUtility.h”
#include “iostream”
#include “coins.h”
#include “enemy.h”
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>
#include “string”
using namespace std;
//Forward declarations, so pointers to these classes can be used – Carson
class Display;
class Button;
/*Includes necessary information for a game level,
with members score, res (resources), i (a counter variable),
FEHImage objects to store sprite images and backgrounds, vectors of Enemy and Coins classes,
a Player object, an array to store addresses, duration, and volume of sound effects, and pointers
to the main display, which stores objects meant to be displayed to the screen, and pause and play buttons.
*/
/*Azariah*/
class Stage {
    public:
       int score, res, lives, seconds, i = 0;
       bool end = false, win=false;
       FEHImage squirrel, squirrel2, squirrelf, squirrel2f;
       FEHImage enemyf1, enemyf2;
       FEHImage stage1_background, stage2_background, stage3_background;
       vector<Enemy> enemies;
       vector<Coins> coins;
       FEHImage coinImg;
       Player player;
       //Carson
       string musicPath[3]={“assets/sounds/stage1.wav”, “assets/sounds/stage2.wav”, “assets/sounds/cottagecore.wav”};
       int musicDuration[3]={41,56,218};
       int volume[3]={1,1,4};
       int stageNum=1;
       bool paused=false, hiddenExitFound=false;
       //Pointers to pause and play buttons, and main display
       Button *pausePtr=nullptr;
       Button *playPtr=nullptr;
       Display *dPtr=nullptr;
       //
       Stage(int stageNum);
       bool update();
       // draws the LCD.WriteAt to draw score, resources, stage, time, lives – Azariah
       void drawStats(Stage &stage, int n);
       //Resets Stage and data members to initial states – Carson
       void reset();
       //Checks if win conditions met – Carson
       void checkWin();
       /*Displays prompt to screen, gives instructions
        to press ENTER to clear stage. Called if player
        is near an exit. – Carson
        */
        void exitPrompt(string str);
       //Changes music – Carson
       void setMusic();
       //Checks collisions – Carson
       bool checkCollisions();
};
//Draws Stage and runs it – Azariah
void drawStage(Stage *s);
//
//Ends game and switches screen – Carson
void gameOver(Stage *s);
//
#endif
