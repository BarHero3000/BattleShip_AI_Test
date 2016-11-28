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
    miss = false;
    directionFound = false;
    directionChosen = false;
    shipHitAgain = false;
    key = 0;
    //Initialize MOVE vector with possMovesLeft
    possMoves.resize(100);
    //Fill possMoves with all possible moves in order
    fillMoves();
    //Randomize move possible move list
    randomMoves();    
    //Set debugging to true for debugging output
    debugging = true;
    
}
//Create the move list in order
void AI::fillMoves(){
    //Less headache than using stringstream
    for(int i = 0; i < 10; i++){
        for(int x = 0; x < 10; x++){
            //Add move to vector (Row letter + Column number)
            possMoves[(i * 10) + x] = num2Letter(i) + intNum2StrNum(x + 1);    //Must convert integer to a string
        }
    }
    if(debugging){
        //Print possible moves in grid view 10x10 (not randomized)
        for(int i = 0; i < possMovesLeft; i++){
            cout << possMoves[i] << " ";
            if(i%10 == 9)
                cout << endl;
        }
    }
}
//Randomize the Possible Move List
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
    
    if(debugging){
        //Print possible moves in grid view (randomized)
        cout << endl;
        for(int i = 0; i < possMovesLeft; i++){
            cout << possMoves[i] << " ";
            if(i%10 == 9)
                cout << endl;
        }
    }
    
}
//Pop of Move from the Possible Move List (Random Move))
string AI::randomFire(){
    string temp;
    //Take move from the back of the vector
    temp = possMoves.back();
    possMoves.pop_back();
    lastMove = temp;
    
    return temp;
}
//Fire function for specific cell, not random, remove Move from Possible Move List
string AI::fire(string position){
    string temp;
    //Find the index of the move
    int pos = find(possMoves.begin(), possMoves.end(), position) - possMoves.begin();    
    //Take move from the back of the vector
    temp = possMoves.at(pos);
    possMoves.erase(possMoves.begin() + pos);
    lastMove = temp;
    
    if(debugging){
        cout << "AI fires at: " << temp << endl;
    }
    
    return temp;
}
//Current NEEDS WORK
void AI::setHit(bool wasHit){
    if(wasHit){    //Ship was HIT during last move
        hits.push_back(lastMove);   //Add lastMove coordinate to the hit list
        possShip.push_back(lastMove);   //Add lastMove coordinate to the Possible Ship List
        if(directionChosen)
            shipHitAgain = true;
        else if(newHit == false){    //Consider comparing the size of possShip instead of using a boolean flag
            newHit = true;
            shipFound = true;
            newShipFound = lastMove;
        }
        else
            shipHitAgain = true;
    } else{ //Miss during last turn
        //If a ship has been found but the last move missed
        if(shipFound)
            shipHitAgain = false;   //Ship has been found but NOT hit in the last turn. Must change direction.
    }
}


//Confirmation of a ship sinking has been received, remove coordinates from Possible Ship List
void AI::sunkShip(int shipSize){
    //Code has not been checked to work yet.
    bool directOK = true;
    //Get current direction and reverse it.
    char checkDirection = switchDirection(direction);   
    //Check if last n amount of moves were in the same direction
    for(int i = (possShip.size() - 1); i > possShip.size() - shipSize; i--){
        if(possShip.at(i) != possShip.at(i - 1))
            directOK = false;
    }
    
    if(directOK){   //Last n amount of hit moves were in the same direction, remove those.
        for(int i = 0; i < shipSize; i++){
            possShip.pop_back();
        }
    } else{ //Remove first hit move and last shipSize - 1 hit moves
        possShip.erase(0);
        possShip.erase(possShip.size() - (1 + shipSize), possShip.size() - 1);
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
                direction = possDirect.back();
                //Get next position based on direction chosen. Starting from the end of the vector.
                position = nextPosition(direction, newShipFound);
                
                possDirect.pop_back();  //If going in direction goes off the grid, the remove direction possibility and test and other direction
                //If going in the chosen direction, then set directOK to true and FIRE!
                if(position != "Out")
                    directOK = true;
            }while(!directOK);
            
            fire(position);
              
            newHit = false;
            directionChosen = true;
        }else if(directionChosen){
            //Move one over from last Hit
            if(shipHitAgain)
                fire(nextPosition(direction, lastMove));
            else    //Ship has been found, but missed last turn, switch directions
            {
                
            }
        }
        else if (directionFound){
            //Continue in the direction moving one over from last Move
        }
    }
}
//Create a new random Direct list
//Needs work, should redo vector every time, not just add to the list!!!
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
    //Initialize Possible Direction vector with 4 possible directions
    possDirect.resize(4);
    //Copy randArray into possible Direction vector
    for(int i = 0; i < 4; i++){
        possDirect[i] = randArray[i];
    }
    if(debugging){
        //For debugging: Print possDirection
        for(int i = 0; i < 4; i++){
            cout << possDirect[i] << " ";
        }
        cout << endl;
    }
}

string AI::nextPosition(char direction, string lastHit){
    //WIP HERE!!!!! May need to change char back to string
    string nextPos;
    int temp = 0;   //Only needed for debugging. After code works can combine two lines into one in the switch statement.
    //Break last hit apart into a row and column string
    char row = lastHit.substr(0, 1).c_str()[0]; //Letter
    char column = lastHit.substr(1, 2).c_str()[0];  //Number
    
    switch(direction){
        case 'U':{
            //Move up one, manipulating the letter... Ex: C5 => B5
            if(letter2Num(row) == 0) //Row A (Top of grid))
                return "Out";
            else{
                temp = letter2Num(row) - 1;
                row = num2Letter(temp);
            }
            break;
        }
        case 'D':{
            //Move down one, manipulating the letter... Ex: C5 => D5
            if(letter2Num(row) == 9) //Row J (Bottom of grid))
                return "Out";
            else{
                temp = letter2Num(row) + 1;
                row = num2Letter(temp);
            }
            break;
        }
        case 'L':{
            //Move left one, manipulating the number... Ex: C5 => C4
            if(charNum2IntNum(column) == 1) //Column 1 (Left of grid)
                return "Out";
            else{
                temp = charNum2IntNum(column) - 1;
                column = intNum2CharNum(temp);
            }
            break;
        }
        case 'R':{
            //Move right one, manipulating the number... Ex: C5 => C6
            if(charNum2IntNum(column) == 10) //Column 10 (Right of grid)
                return "Out";
            else{
                temp = charNum2IntNum(column) + 1;
                column = intNum2CharNum(temp);
            }
            break;
        }
    }
    
    //nextPos = row + column;   //Does not work. Adds the decimal Unicode instead of the combining the characters
    nextPos += row;
    nextPos += column;
     
    return nextPos;
}
//Switch direction of Possible Direction
char AI::switchDirection(char direction){
    switch(direction){
        case 'U': return 'D';
        case 'D': return 'U';
        case 'L': return 'R';
        case 'R': return 'L';
    }
}

string AI::moveAI2(){
    switch(key){
        case 0:{    //No ships coordinates found yet
            //Fire off random coordinates. popping off from the possible move vector
            randomFire();
            break;
        }
        case 1:{    //New Ship found, create direction list
            //Set direction to popped off direction from possible direction vector
            direction = possDirect.back();
            //Fire at one space over in set direction
            fire(nextPosition(direction, lastMove));
            key = 2;    
            break;
        }
        case 2:{    //AI randomly shoots around the New Ship Coordinate
            fire(nextPosition(possDirect.back(), lastMove));
            break;
        }
        case 3:{    //Another hit is made using the Possible Direction List, set Direction
            fire(nextPosition(direction, lastMove));
            break;
        }
        case 4:{    //AI fires in set direction moving one more over each turn
            break;
        }
        case 5:{    
            break;
        }
        case 6:{
            break;
        }
        case 7:{
            break;
        }
    }
}

void AI::moveResult(bool hit, bool sunk, int shipSize){
    if(hit){    //Ship was hit
        if(possShip.size() == 0 ){   //No active ships found
            //Create random direction list
            randomDirect();           
            //New Ship has been found flag
            newShipFound = true;
            //Go to next step in AI flow chart
            key = 1;  
        } else if(sunk){
            sunkShip(shipSize);
        }
        miss = false;   //Set miss flag to false
    }
    else    //Ship was not hit
        miss = true;
}


//Converting Functions

//Convert a string letter to an integer number (A-J => 0-9)
//int AI::strLetter2Num(string letter){
//    switch(letter){
//        case "A": return 0;
//        case "B": return 1;
//        case "C": return 2;
//        case "D": return 3;
//        case "E": return 4;
//        case "F": return 5;
//        case "G": return 6;
//        case "H": return 7;
//        case "I": return 8;
//        case "J": return 9;
//    }
//}
//Convert a string number to an integer number (0-10)
//int AI::strNum2Num(string num){
//    switch(num){
//        case "0": return 0;
//        case "1": return 1;
//        case "2": return 2;
//        case "3": return 3;
//        case "4": return 4;
//        case "5": return 5;
//        case "6": return 6;
//        case "7": return 7;
//        case "8": return 8;
//        case "9": return 9;
//        case "10": return 10;
//    }
//}
//Convert an integer number to a string letter (0-9 => A-J)
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
//Convert integer number to string number (0-10)
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
//Convert integer number to char letter (0-9 => A-J)
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
//Convert char letter to integer number (A-j => 0-9)
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
//Convert a string number to an integer number (0-10)
int AI::charNum2IntNum(char num){
    switch(num){
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        //case '10': return 10;
    }
}
//Convert integer number to char number (0-9)
char AI::intNum2CharNum(int num){
    switch(num){
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';
//        case 10: return "10";
    }
}

//Obsolete Code

//Obsolete
void AI::setHit(bool hit, string position){   //Obsolete
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
//Obsolete
void AI::moveResult(bool hit){
    if(hit){    //Ship was hit
        if(possShip.size() == 0 ){   //No active ships found
            //Create random direction list
            randomDirect();
            
            //New Ship has been found flag
            newShipFound = true;
            //Go to next step in AI flow chart
            key = 1;  
        }
        miss = false;   //Set miss flag to false
    }
    else    //Ship was not hit
        miss = true;
}