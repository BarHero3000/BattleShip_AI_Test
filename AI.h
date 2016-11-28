/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AI.h
 * Author: Brandon
 *
 * Created on October 15, 2016, 9:26 PM
 */

#ifndef AI_H
#define AI_H

#include <vector>
#include <string>

using namespace std;

class AI {
public:
    AI();
    AI(const AI& orig);
    //virtual ~AI();
    string randomFire();
    string fire(string position);
    string getLastMove(){return lastMove;}
    void setHit(string hit);
    void setHit(bool wasHit);
    void moveAI();
    void sunkShip(int shipSize);
    string moveAI2();
    void moveResult(bool hit);
    void moveResult(bool hit, bool sunk, int shipSize);
    
private:  
    
    bool debugging; //Used to display results while debugging
    
    vector<string> possMoves;
    vector<string> possShip;   //Possible ship coordinates
    vector<char> possDirect;  //Possible direction of the ship
    vector<string> hits;
    
    int possMovesLeft;
    string lastMove;
    bool shipFound;
    bool newHit;
    bool miss;
    string newShipFound;    //Location that the new ship was found
    char direction; //UP(U), DOWN(D), LEFT(L), RIGHT(R)
    string nextMove;
    bool directionFound;
    bool directionChosen;
    bool shipHitAgain;
    int key;
    
    void randomMoves();
    void fillMoves();
    void randomDirect();
    string nextPosition(char direction, string lastHit);
    char switchDirection(char direction);
    
    int strLetter2Num(string letter);
    int strNum2Num(string num);
    string num2StrLetter(int x);
    string intNum2StrNum(int num);
    char num2Letter(int x);
    int letter2Num(char letter);  
    int charNum2IntNum(char num);
    char intNum2CharNum(int num);
    
    

};

#endif /* AI_H */

