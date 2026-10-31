//Author: Azariah
#include “coins.h”
#include “FEHLCD.h”
#include “FEHImages.h”
#include “FEHUtility.h”
#include “iostream”
#include “stage.h”
#include “player.h”
using namespace std;
Coins::Coins(FEHImage coin, int x, int y){
    cx=x;
    cy=y;
    peanut = coin;
    peanut.Open(“assets/peanut.png”);
}
//If not touched, draws coin to screen – Azariah
void Coins::drawCoin(){
    if(!touched){
        peanut.Draw(cx, cy);
    }
}
//Checks if the player’s location is within the
//collection area (cwidth and cheight) of the coin – Azariah
bool Coins::hasCollectedCoin(Player &player){
    int pwidth = 13;
    int pheight = 8;
    int cwidth = 5;
    int cheight = 5;
    int xDistance = abs(player.getX() – cx);
    int yDistance = abs(player.getY() – cy);
    if(xDistance <= (pwidth + cwidth) && yDistance <= (pheight + cheight)){
        return true;
    } else {
        return false;
    }
}
