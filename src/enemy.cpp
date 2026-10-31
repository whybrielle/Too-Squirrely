//Author: Azariah
#include “player.h”
#include “enemy.h”
#include “FEHLCD.h”
#include “iostream”
#include “FEHKeyboard.h”
#include <FEHImages.h>
#include <string>
#include “FEHUtility.h”
#include <FEHSound.h>
#include <math.h>
//Azariah
Enemy::Enemy(FEHImage &f1, const char *fr1, FEHImage &f2, const char *fr2, int x, int y)
{
   eframe1 = f1;
   eframe2 = f2;
   strcpy(ef1, fr1);
   strcpy(ef2, fr2);
   x_enemy = x;
   y_enemy = y;
   eframe1.Open(ef1);
   eframe2.Open(ef2);
}
/*Draws n enemies, each at a location
determined by their x_enemy and y_enemy values
– Azariah */
void Enemy::drawEnemy(int n)
{
   if(n == 0){
       eframe1.Draw(x_enemy, y_enemy);
   } else {
       eframe2.Draw(x_enemy, y_enemy);
   }
}
//Determines Enemy movement patterns – Azariah
void Enemy::goWalk(bool draw){
   if(onGround() && (!alive || !draw)){
       return;
   }
   animTimer++;
   if (animTimer >= 5) {
       animFrame = (animFrame + 1) % 2; // switches between frame 1 and 2
       animTimer = 0;
   }
   drawEnemy(animFrame);
   // Move enemy
   x_enemy += speed * direction;
   // Change direction at edges
   if (x_enemy >= endofScreenRight) {
       direction = -1;  // go left
   }
   else if (x_enemy <= 0) {
       direction = 1;   // go right
   }
}
//Checks if enemy is on ground level – Azariah
bool Enemy::onGround(){
   if(y_enemy == 201){
       return true;
   } else {
       return false;
   }
}
//Checks if enemy is touching the player – Azariah
bool Enemy::isTouching(Player &player){
   int pwidth = 13;
   int pheight = 8;
   int ewidth = 5;
   int eheight = 7;
   int xDistance = abs(player.getX() – x_enemy);
   int yDistance = abs(player.getY() – y_enemy);
   if(xDistance <= (pwidth + ewidth) && yDistance <= (pheight + eheight)){
       return true;
   } else {
       return false;
   }
}
