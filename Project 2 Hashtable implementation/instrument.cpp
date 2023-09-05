//
// Created by gwdin on 3/17/2022.
//

#include "instrument.h"
#include <fstream>
#include <time.h>
#include <ctime>
#include <iostream>
#include "hash_functions.h"
#include <string>
#include <map>



//template <class T, class H >
void instrument::test_time(string file){ //get file contents and do the hash thing, have to use in main

    ifstream outFS;
    hashtable<string> mega;//H can be replaced
    hashtable<string, hash1> has1;
    hashtable<string, hash2> has2;
    hashtable<string, hash3> has3;
    hashtable<string, hash4> has4;

    vector<string> context;
    string word;
    outFS.open(file);

    while (outFS.eof() == false) { //gets everything, don't forget working direct needs "../" in run-edit config
        outFS >> word;
        context.push_back(word);
    }
    outFS.close();


    clock_t start = clock(); //what is being timed?

    for (int i=0; i < context.size(); ++i) { //gets everything
        mega.insert(context[i]);
    }


    clock_t stop = clock();


// delta will be the total time your code took to run in seconds
    double delta = (stop - start) / double(CLOCKS_PER_SEC);
    cout << "default: " << delta << endl;

///////////////////////////////////////////////////////////////////////////
    clock_t start_1 = clock(); //what is being timed?


    for (int i=0; i < context.size(); ++i) { //gets everything
        has1.insert(context[i]);
    }


    clock_t stop_1 = clock();


// delta will be the total time your code took to run in seconds
    double delta_1 = (stop_1 - start_1) / double(CLOCKS_PER_SEC);
    cout << "has1: " << delta_1 << endl;
//////////////////////////////////////////////////////////////////


    clock_t start_2 = clock(); //what is being timed?


    for (int i=0; i < context.size(); ++i) { //gets everything
        has2.insert(context[i]);
    }


    clock_t stop_2 = clock();


// delta will be the total time your code took to run in seconds
    double delta_2 = (stop_2 - start_2) / double(CLOCKS_PER_SEC);
    cout << "has2: " << delta_2 << endl;
//////////////////////////////////////////////////////////////////


    clock_t start_3 = clock(); //what is being timed?


    for (int i=0; i < context.size(); ++i) { //gets everything
        has3.insert(context[i]);
    }


    clock_t stop_3 = clock();


// delta will be the total time your code took to run in seconds
    double delta_3 = (stop_3 - start_3) / double(CLOCKS_PER_SEC);
    cout << "has3: " << delta_3 << endl;
//////////////////////////////////////////////////////////////////


    clock_t start_4 = clock(); //what is being timed?


    for (int i=0; i < context.size(); ++i) { //gets everything
        has4.insert(context[i]);
    }

    clock_t stop_4 = clock();


// delta will be the total time your code took to run in seconds
    double delta_4 = (stop_4 - start_4) / double(CLOCKS_PER_SEC);
    cout << "has4: " << delta_4 << endl;
}


void instrument::hisagram(string file){//b u c k e t
    ifstream outFS;
    hashtable<string> mega;
    hashtable<string, hash1> has1;
    hashtable<string, hash2> has2;
    hashtable<string, hash3> has3;
    hashtable<string, hash4> has4;

    vector<string> context;
    string word;
    outFS.open(file);

    while (outFS.eof() == false) { //gets everything, don't forget working direct needs "../" in run-edit config
        outFS >> word;
        context.push_back(word);
    }
    outFS.close();

    for (int i=0; i < context.size(); ++i) { //gets everything
        mega.insert(context[i]);
    }

    cout << "default";
    mega.buckets();
//////////////////////////////////////////////////////////////
    for (int i=0; i < context.size(); ++i) { //gets everything
        has1.insert(context[i]);
    }

    cout << endl << "has1";
    has1.buckets();
//////////////////////////////////////////////////////////////
    for (int i=0; i < context.size(); ++i) { //gets everything
        has2.insert(context[i]);
    }

    cout << endl << "has2";
    has2.buckets();
//////////////////////////////////////////////////////////////
    for (int i=0; i < context.size(); ++i) { //gets everything
        has3.insert(context[i]);
    }

    cout << endl << "has3";
    has3.buckets();
//////////////////////////////////////////////////////////////
    for (int i=0; i < context.size(); ++i) { //gets everything
        has4.insert(context[i]);
    }

    cout << endl << "has4";
    has4.buckets();
}