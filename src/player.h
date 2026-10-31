//Header file for Player class, contains player 

//information, sprites, stats, etc. 

//Author: Azariah unless otherwise specified 

#ifndef PLAYER_H 

#define PLAYER_H 

class Enemy; 

#include “FEHLCD.h” 

#include “iostream” 

#include “FEHKeyboard.h” 

#include “FEHUtility.h” 

#include <FEHImages.h> 

#include <string> 

#include <FEHSound.h> 

#include “enemy.h” 

 

using namespace std; 

 

// Class variables and function prototypes of player class. 

// No functin definition in .h file 

 

//const for initial y position of the ground – Carson 

const int startingGroundPos=190; 

 

class Player { 

   public: 

        //Player stats, to be shown in Statistics screen 

        //of main menu – Carson 

       string name=“Squirrel”; 

       int score=0; 

       int hiddenDoorsFound=0; 

       int stagesUnlocked=1; 

       // Player related variables – Azariah 

       FEHImage frame1, frame2, frame1_flip, frame2_flip; 

       FEHImage projectileleft, projectileright; 

       int x_pos, y_pos, speed = 5, health = 3; 

       char imgAdress[30], imgAdress2[30]; 

       char imgflip1[30], imgflip2[30]; 

       // animation related variables 

       int animFrame = 0; 

       float gravity = .8, vel = 0; 

       int facing = 1; // right 

       int animTimer = 0; 

       // projectile related variables 

       int projX = 0; 

       int projY = 0; 

       int speedproj = 6; 

       int projDistance = 0; 

       int projDirection; 

   public: 

       int groundYPos=190;//Sets location of ground-Carson 

       bool h = false; 

       bool active = false; 

       int invincibleTimer = 0; 

       static const int INVINCIBLE_TIME = 120; 

       Player(); 

       Player(FEHImage f1, char addy[20], FEHImage f2, char addy2[20], FEHImage f1f, char flip1[20], FEHImage f2f, char flip2[20], int x, int y); 

       int getX(); 

       int getY(); 

       void drawPlayer(int n); 

       void drawPlayerRight(int n); 

       void shooting(int o); 

       void update(); 

       bool onGround(); 

       bool isHitting(Enemy &enemy); 

       void movePlayer(); 

}; 

 

#endif 
