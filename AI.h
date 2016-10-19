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
    string fire();
    string fire(string position);
    string getLastMove(){return lastMove;}
    void setHit(string hit);
    void moveAI();
    
private:  
    vector<string> possMoves;
    vector<char> possDirect;  //Possible direction of the ship
    vector<string> hits;
    
    int possMovesLeft;
    string lastMove;
    bool shipFound;
    bool newHit;
    string newShipFound;    //Location that the new ship was found
    char direction; //UP(U), DOWN(D), LEFT(L), RIGHT(R)
    string nextMove;
    bool directionFound;
    bool directionChosen;
    
    void randomMoves();
    void fillMoves();
    string int2String(int x);
    char num2Letter(int x);
    int letter2Num(char letter);    
    void randomDirect();
    string nextPosition(char direction, string lastHit);
    
    

};

#endif /* AI_H */

