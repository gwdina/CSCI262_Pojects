/*
 * main.cpp
 *
 * Author: C. Painter-Wakefield
 *
 * main() function for the Image Fun program.  Initializes an instance of the
 * manager class by installing various tools.  Prints a friendly welcome message
 * and then hands control off to the manager.
 *
 * Last modified: 1/16/2022
 */

#include <iostream>

#include "framework/steganography.h"
#include "framework/mondrian.h"
#include "manager.h"
#include "editor.h"


using namespace std;

int main() {
    cout << endl;
    cout << "Welcome to Image Fun!" << endl;
    cout << endl;

    manager m;
    m.install_tool(new editor);
    m.install_tool(new steganography);
    m.install_tool(new mondrian);


    m.run();

    cout << "Thank you for using Image Fun!" << endl;

    return 0;
}

