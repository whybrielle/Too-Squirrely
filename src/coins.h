//Author: Azariah
#ifndef COINS_H
#define COINS_H
#include “FEHLCD.h”
#include “FEHImages.h”
#include “FEHUtility.h”
#include “iostream”
#include “player.h”
class Player;
using namespace std;
/*Coins class is a collectible item, with FEHImage of peanut.
bool touched determines if player touched the coin, cx and xy
are the coin’s x and y positions.
-Azariah*/
class Coins {
    private:
        FEHImage peanut;
    public:
        bool touched = false;
        int cx, cy;
        Coins(FEHImage coin, int x, int y);
        //Checks if player has collected coin
        //by touching it – Azariah
        bool hasCollectedCoin(Player &player);
        //Draws coin on screen – Azariah
        void drawCoin();
};
#endif
