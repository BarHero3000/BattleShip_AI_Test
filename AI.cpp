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
#include <iostream>
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <string>       //std::to_string()
#include <sstream>      //Needed to convert int to string

using namespace std;

AI::AI() {
    possMovesLeft = 100;
    shipFound = false;
    newHit = false;
    //Initialize MOVE vector with possMovesLeft
    possMoves.resize(100);
    //Fill possMoves with all- possible moves in order
    fillMoves();
    //Randomize move possible move list
    randomMoves();    
}

char AI::num2Letter(int x){
    //0-9 == A-J
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
            return 'I';
        }
        case 9:{
            return 'J';
        }
    }
}

int AI::letter2Num(char letter){
    switch(letter){
        case 'A':{
            return 0;
        }
        case 'B':{
            return 1;
        }
        case 'C':{
            return 2;
        }
        case 'D':{
            return 3;
        }
        case 'E':{
            return 4;
        }
        case 'F':{
            return 5;
        }
        case 'G':{
            return 6;
        }
        case 'H':{
            return 7;
        }
        case 'I':{
            return 8;
        }
        case 'J':{
            return 9;
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
    
    //Print possible moves in grid view (randomized)
    cout << endl;
    for(int i = 0; i < possMovesLeft; i++){
        cout << possMoves[i] << " ";
        if(i%10 == 9)
            cout << endl;
    }
    
}

void AI::fillMoves(){
    stringstream out;

//    for(int i = 0; i < 10; i++){
//        for(int x = 0; x < 10; x++){
//            //Column number added to the stringstream, needed to convert int to string
//            out << x + 1;
//            //Add move to vector (Row letter + Column number)
//            possMoves[(i * 10) + x] = getLetter(i) + out.str();
//            //Clear stringstream
//            out.str("");
//        }
//    }
    
    //Less headache than using stringstream
    for(int i = 0; i < 10; i++){
        for(int x = 0; x < 10; x++){
            //Add move to vector (Row letter + Column number)
            possMoves[(i * 10) + x] = getLetter(i) + int2String(x + 1);
        }
    }
    
    //Print possible moves in grid view (not randomized)
    for(int i = 0; i < possMovesLeft; i++){
        cout << possMoves[i] << " ";
        if(i%10 == 9)
            cout << endl;
    }
}

string AI::int2String(int x){
    switch(x){
        case 0:{
            return "0";
        }
        case 1:{
            return "1";
        }
        case 2:{
            return "2";
        }
        case 3:{
            return "3";
        }
        case 4:{
            return "4";
        }
        case 5:{
            return "5";
        }
        case 6:{
            return "6";
        }
        case 7:{
            return "7";
        }
        case 8:{
            return "8";
        }
        case 9:{
            return "9";
        }
        case 10:{
            return "10";
        }
    }
}

string AI::fire(){
    string temp;    //temporary string to hold the move and be returned.
    temp = possMoves[0];    //Assign first move in the vector to temp string.
    possMoves.erase(0); //Delete the first move in the vector.
    lastMove = temp;    //Assign move to the lastMove string.
    return temp;
}

void AI::setHit(string hit){
    hits.push_back(hit);
    if(!newHit){
        newHit = true;
        shipFound = true;
    }
}

void AI::moveAI(){
    //Check if ship is found
    if(shipFound){
        //Ship was found during last move, now the fun part...
        if(newHit){
            //New ship is found, must 1st find the direction of the ship, Horizontal or Vertical
            //Randomly choose Horizontal or Vertical
            srand(time(NULL));  //Set random number generator
            //Get a random number 0(Horizontal) or 1(Vertical)
            int tempInt = rand%2;
            //Get direction based on random number
            if(tempInt == 0)
                direction = 'H';
            else
                direction = 'V';
            
            
            
            newHit = false;
            //Initialize possible direction vector with the 4 possibilities
            //UP, DOWN, RIGHT, LEFT
            
                    
        }
    }
}

void AI::randomDirect(){
    possDirect.resize(4);
    
    //UP
    //DOWN
    //LEFT
    //RIGHT
    
    
    
        
}

