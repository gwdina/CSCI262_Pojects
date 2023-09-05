/*
 * main.cpp
 *
 * Includes the main function for the hashtable assignment
 *
 * To run the main function in this file, click the drop
 * down in between the Build Hammer button and Play button
 * and select "hashtable_main"
*/

#include <string>
#include <iostream>
#include "hashtable.h"
#include <fstream>
#include "hash_functions.h"
#include "instrument.h"
#include <time.h>
#include <ctime>

using namespace std;

int main() {
    // use this main function as a playground for this lab/assignment

   instrument i;

    i.test_time("random.txt");

    cout << endl;

    //i.hisagram("dictionary.txt");

    return 0;


}


