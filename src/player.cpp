//Author: Azariah
#include “player.h”
#include “enemy.h”
#include “stage.h”
#include “FEHLCD.h”
#include “iostream”
#include “FEHKeyboard.h”
#include <FEHImages.h>
#include <string>
#include “FEHUtility.h”
#include <FEHSound.h>
using namespace std;
Player::Player(){}
// Constructor
// takes the FEHImage object of the player animation sprites and their adresses
Player::Player(FEHImage f1, char addy[30], FEHImage f2, char addy2[30], FEHImage f1f, char flip1[30], FEHImage f2f, char flip2[30], int x, int y) {
   frame1 = f1;
   frame2 = f2;
   frame1_flip = f1f;
   frame2_flip = f2f;
   strcpy(imgAdress, addy);
   strcpy(imgAdress2, addy2);
   strcpy(imgflip1, flip1);
   strcpy(imgflip2, flip2);
   x_pos = x;
   y_pos = y;
   frame1.Open(imgAdress);
   frame2.Open(imgAdress2);
   frame1_flip.Open(imgflip1);
   frame2_flip.Open(imgflip2);
   projectileleft.Open(“assets/aright.png”);
   projectileright.Open(“assets/aleft.png”);
}
// Get x position of player sprite
int Player::getX(){
   return x_pos;
}
// Get y position of player sprite
int Player::getY(){
   return y_pos;
}
// Draws the first or second frame of animation for the player depending on number inputed
void Player::drawPlayer(int n) {
   if(n == 0){
       frame1.Draw(x_pos, y_pos);
   } else {
       frame2.Draw(x_pos, y_pos);
   }
}
//Flips player
void Player::drawPlayerRight(int n) {
   if(n == 0){
       frame1_flip.Draw(x_pos, y_pos);
   } else {
       frame2_flip.Draw(x_pos, y_pos);
   }
}
void Player::shooting(int o){
   // if projectile bool is false
   h = false;
   if (invincibleTimer==0) {
        if(!active){
            active = true;
            // shot in left or right directions
            if(facing == 1){
                projX = x_pos + 25;
                projY = y_pos + 3;
            } else {
                projX = x_pos – 10;
                projY = y_pos + 3;
            }
            projDistance = 0;
            projDirection = facing;
        }
    }
}
void Player::update(){
   if (invincibleTimer > 0){
       invincibleTimer–;
   }
}
// Player movement
void Player::movePlayer() {
   if(invincibleTimer > 0){
       invincibleTimer–;
   }
   // simplifed key declarations
   bool left = Keyboard.isPressed(KEY_A);
   bool right = Keyboard.isPressed(KEY_D);
   bool jump = Keyboard.isPressed(KEY_W);
   bool shoot = Keyboard.isPressed(KEY_SPACE);
   // if player is on the ground and hits w key, set a neg velocity
   if (onGround() && jump) {
       //bounce.play();
       vel = -10;
   }
   // increase players velocity, making it more positive
   // and makes player move down
   vel += 1.2;
   y_pos += vel;
   // ground collision
   if (y_pos >= groundYPos){
       y_pos = groundYPos;
       vel = 0;
   }
   bool walking = false;
   if (right) {
       // Movement
       x_pos += speed;
       facing = 1;
       walking = true;
   } else if (left) {
       // Movement
       x_pos -= speed;
       facing = -1;
       walking = true;
   }
   // if space is pressed, shoot projectile
   if(shoot){
       //acorn_sound.play();
       shooting(facing);
   }
   // if projectile is on the screen, move a certain distance left or right
   if(active){
       projX += speedproj * projDirection;
       projDistance += speedproj;
       if (projDistance >= 60){
           active = false;
       }
   }
   /* If player is on the ground and hitting ‘a’ or ‘s’ keys
    set period for animations to play */
   if(walking && onGround()){
       animTimer++;
       if (animTimer >= 5) {
           animFrame = (animFrame + 1) % 2; // switches between frame 1 and 2
           animTimer = 0;
       }
   } else {
       animFrame = 0;
       animTimer = 0;
   }
   /*
   If player is walking left or right while on the ground
   draw the frames.
   */
   if(walking && onGround()){
       if (facing == 1){
           drawPlayerRight(animFrame);
       } else {
           drawPlayer(animFrame);
       }
   } else { // if player is not on ground
       if(facing == 1){
           drawPlayerRight(0);
       } else {
           drawPlayer(0);
       }
   }
   // set projectile direction
   if(active){
       if (projDirection == 1){
           projectileright.Draw(projX, projY);
       } else {
           projectileleft.Draw(projX, projY);
       }
   }
}
bool Player::onGround(){ // To be changed later to be functional with a map
   if(y_pos == groundYPos){
       return true;
   } else {
       return false;
   }
}
bool Player::isHitting(Enemy &enemy){
   int projwidth = 6;
   int ewidth = 5;
   int xDistance = abs(enemy.x_enemy – projX);
   int yDistance = abs((enemy.y_enemy + 3) – projY);
   if(xDistance <= (projwidth + ewidth) && yDistance <= 2){
       return true;
   } else {
       return false;
   }
}
