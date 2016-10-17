/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AI.cpp
 * Author: Brandon
 * 
 * Created on October 15, 2016, 9:26 PM
 */

#include "AI.h"
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

using namespace std;

AI::AI() {
    this->possMovesLeft = 100;
    //Initialize MOVE vector with possMovesLeft
    possMoves.resize(100);
    //Fill possMoves with all- possible moves in order
    //Randomize move possible move list
    
}

char AI::getLetter(int x){
    switch(x){
        case 0:{
            return 'A';
        }
        case 1:{
            return 'B';
        }
        case 2:{
            return 'C';
        }
        case 3:{
            return 'D';
        }
        case 4:{
            return 'E';
        }
        case 5:{
            return 'F';
        }
        case 6:{
            return 'G';
        }
        case 7:{
            return 'H';
        }
        case 8:{
            return 'J';
        }
        case 9:{
            return 'K';
        }
    }
}

void AI::randomMoves(){
    //Create temporary move vector and copy vectors
    vector<string> tempMoves(possMoves);
    //Array of numbers the size of the total deck to be randomized.
    int randArray[possMovesLeft];
    //Fill randArray from 0 to numOfCards - 1
    for(int i = 0; i < possMovesLeft; i++){
        randArray[i] = i;
    }   
    //Randomize the randArray
    std::srand ( unsigned ( std::time(0) ) );   //So that cards are actually random for every game.
    std::random_shuffle(&randArray[0], &randArray[possMovesLeft - 1]);   
    //Randomize Possible Moves Vector using the randomized array
    for(int i = 0; i < possMovesLeft; i++){
        possMoves[i] = tempMoves[randArray[i]];
    }    
    
}

