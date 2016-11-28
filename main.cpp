/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Brandon
 *
 * Created on October 15, 2016, 9:26 PM
 */

#include <cstdlib>
#include "AI.h"
#include <iostream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    AI testAI = AI();
    
    //Initial fire
    testAI.fire("A1");
    //State that it was a hit
    testAI.setHit(true);
    //AI fires around hit in a random direction
    testAI.moveAI();
    //State that it was a hit
    testAI.setHit(true);
    //AI fires around hit in set direction
    testAI.moveAI();
    //State that it was a hit
    testAI.setHit(true);
    //State ship sunk
    testAI.sunkShip(3);

    return 0;
}

