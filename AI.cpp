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
#include <string>
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
    directionFound = false;
    directionChosen = false;
    shipHitAgain = false;
    //Initialize MOVE vector with possMovesLeft
    possMoves.resize(100);
    //Fill possMoves with all- possible moves in order
    fillMoves();
    //Randomize move possible move list
    randomMoves();    
}



int AI::letter2Num(char letter){
    switch(letter){
        case 'A': return 0;
        case 'B': return 1;
        case 'C': return 2;
        case 'D': return 3;
        case 'E': return 4;
        case 'F': return 5;
        case 'G': return 6;
        case 'H': return 7;
        case 'I': return 8;
        case 'J': return 9;
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
    //Less headache than using stringstream
    for(int i = 0; i < 10; i++){
        for(int x = 0; x < 10; x++){
            //Add move to vector (Row letter + Column number)
            possMoves[(i * 10) + x] = num2Letter(i) + int2String(x + 1);    //Must convert integer to a string
        }
    }
    
    //Print possible moves in grid view 10x10 (not randomized)
    for(int i = 0; i < possMovesLeft; i++){
        cout << possMoves[i] << " ";
        if(i%10 == 9)
            cout << endl;
    }
}


string AI::fire(){
    string temp;
    //Take move from the back of the vector
    temp = possMoves.back();
    possMoves.pop_back();
    lastMove = temp;
    
    return temp;
}

string AI::fire(string position){
    string temp;
    //Find the index of the move
    int pos = find(possMoves.begin(), possMoves.end(), position) - possMoves.begin();    
    //Take move from the back of the vector
    temp = possMoves.at(pos);
    possMoves.erase(possMoves.begin() + pos);
    lastMove = temp;
    
    return temp;
}

void AI::setHit(bool hit, string position){
    if(hit){    //Ship was HIT during last move
        hits.push_back(position);
        if(newHit == false){
            newHit = true;
            shipFound = true;
            newShipFound = position;
        }
        else
            shipHitAgain = true;
    } else{ //Miss during last turn
        //If a ship has been found but the last move missed
        if(shipFound)
            shipHitAgain = false;   //Ship has been found but NOT hit in the last turn
    }
}


void AI::moveAI(){
    string position;
    //Check if ship is found during last turn
    if(shipFound){
        //Ship was found during last move, now the fun part...
        if(newHit){
            //New ship is found, must 1st find the direction of the ship, Horizontal (Left or Right) or Vertical (Up or Down))
            //Create random possibilities vector<char>
            randomDirect();
            bool directOK = false;
            do{
                direction = possDirect.back()
                //Get next position based on direction chosen. Starting from the end of the vector.
                position = nextPosition(direction, newShipFound);
                //If going in the chosen direction, then set directOK to true and FIRE!
                if(position != "Out")
                    directOK = true;
                else
                    possDirect.pop_back();  //If going in direction goes off the grid, the remove direction possibility and test and other direction
            }while(!directOK);
            
            fire(position);
              
            newHit = false;
            directionChosen = true;
        }else if(directionChosen){
            //Move one over from newShipFound
            if(shipHitAgain)
                
        }
        else if (directionFound){
            //Continue in the direction moving one over from last Move
        }
    }
}

void AI::randomDirect(){
    //Randomly choose UP(U), DOWN(D), LEFT(L), RIGHT(R)
    char randArray[4];
    randArray[0] = 'U';
    randArray[1] = 'D';
    randArray[2] = 'L';
    randArray[3] = 'R';
    //Randomize the randArray
    std::srand ( unsigned ( std::time(NULL)));   //So that cards are actually random for every game.
    std::random_shuffle(&randArray[0], &randArray[3]);
    //Copy randArray into possible Direction vector
    for(int i = 0; i < 4; i++){
        possDirect.push_back(randArray[i]);
    }
    //For debugging: Print possDirection
    for(int i = 0; i < 4; i++){
        cout << possDirect[i] << " ";
    }
    cout << endl;
}

string AI::nextPosition(char direction, string lastHit){
    //WIP HERE!!!!!
    string nextPos;
    int temp = 0;   //Only needed for debugging. After code works can combine two lines into one in the switch statement.
    //Break last hit apart into a row and column string
    string row = lastHit.substr(0, 1); //Letter
    string column = lastHit.substr(1, 2);  //Number
    
    switch(direction){
        case 'U':{
            //Move up one, manipulating the letter... Ex: C5 => B5
            if(strLetter2Num(row) == 0) //Row A (Top of grid))
                return "Out";
            else{
                temp = strLetter2Num(row) - 1;
                row = num2StrLetter(temp);
            }
            break;
        }
        case 'D':{
            //Move down one, manipulating the letter... Ex: C5 => D5
            if(strLetter2Num(row) == 9) //Row J (Bottom of grid))
                return "Out";
            else{
                temp = strLetter2Num(row) + 1;
                row = num2StrLetter(temp);
            }
            break;
        }
        case 'L':{
            //Move left one, manipulating the number... Ex: C5 => C4
            if(strNum2Num(column) == 1) //Column 1 (Left of grid)
                return "Out";
            else{
                temp = strNum2Num(column) + 1;
                column = intNum2StrNum(temp);
            }
            break;
        }
        case 'R':{
            //Move right one, manipulating the number... Ex: C5 => C6
            if(strNum2Num(column) == 10) //Column 1 (Left of grid)
                return "Out";
            else{
                temp = strNum2Num(column) - 1;
                column = intNum2StrNum(temp);
            }
            break;
        }
    }
    
    nextPos = row + column;
     
    return nextPos;
}

char AI::switchDirection(char direction){
    switch(direction){
        case 'U': return 'D';
        case 'D': return 'U';
        case 'L': return 'R';
        case 'R': return 'L';
    }
}

int AI::strLetter2Num(string letter){
    switch(letter){
        case "A": return 0;
        case "B": return 1;
        case "C": return 2;
        case "D": return 3;
        case "E": return 4;
        case "F": return 5;
        case "G": return 6;
        case "H": return 7;
        case "I": return 8;
        case "J": return 9;
    }
}
int AI::strNum2Num(string num){
    switch(num){
        case "0": return 0;
        case "1": return 1;
        case "2": return 2;
        case "3": return 3;
        case "4": return 4;
        case "5": return 5;
        case "6": return 6;
        case "7": return 7;
        case "8": return 8;
        case "9": return 9;
        case "10": return 10;
    }
}

string AI::num2StrLetter(int x){
    //0-9 == A-J
    switch(x){
        case 0: return "A";
        case 1: return "B";
        case 2: return "C";
        case 3: return "D";
        case 4: return "E";
        case 5: return "F";
        case 6: return "G";
        case 7: return "H";
        case 8: return "I";
        case 9: return "J";
    }
}

string AI::intNum2StrNum(int num){
    switch(num){
        case 0: return "0";
        case 1: return "1";
        case 2: return "2";
        case 3: return "3";
        case 4: return "4";
        case 5: return "5";
        case 6: return "6";
        case 7: return "7";
        case 8: return "8";
        case 9: return "9";
        case 10: return "10";
    }
}

char AI::num2Letter(int x){
    //0-9 == A-J
    switch(x){
        case 0: return 'A';
        case 1: return 'B';
        case 2: return 'C';
        case 3: return 'D';
        case 4: return 'E';
        case 5: return 'F';
        case 6: return 'G';
        case 7: return 'H';
        case 8: return 'I';
        case 9: return 'J';
    }
}

string AI::int2String(int x){
    switch(x){
        case 0: return "0";
        case 1: return "1";
        case 2: return "2";
        case 3: return "3";
        case 4: return "4";
        case 5: return "5";
        case 6: return "6";
        case 7: return "7";
        case 8: return "8";
        case 9: return "9";
        case 10: return "10";
    }
}
