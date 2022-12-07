//
// Created by W0068332 on 11/21/2021.
//
//Example main.cpp
//This supposes that city->step() calls the move method of each organism in the city
//in a single pass causing each to perform all tasks that it can.

#include <iostream>
#include <chrono>
#include <thread>
#include "../inc/City.h"
#include "../inc/Organism.h"
#include "../inc/GameSpecs.h"


using namespace std;

void ClearScreen()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

int main() {
    City *city = new City();

    cout << *city;



    chrono::milliseconds interval(PAUSE_SECONDS);

    while (city->hasDiversity()) { //while both humans and zombies exist
        this_thread::sleep_for(interval);
        ClearScreen();
        city->move(); //includes all actions

        cout << *city; //prints city


    }//end while
}//end main

