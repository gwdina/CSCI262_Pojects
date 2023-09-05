/*
 * tool.h
 *
 * Author: C. Painter-Wakefield
 *
 * Abstract base class for tool objects.
 *
 * Last modified: 1/16/2022
 */

#ifndef _TOOL_H
#define _TOOL_H

#include <vector>
#include <string>

#include "picture.h"

using namespace std;

class tool {
public:
    // return the utility commands and utility descriptions for the functions
    // provided by this tool
    virtual vector<string> get_verbs() = 0;
    virtual vector<string> get_menu_entries() = 0;

    // perform a command provided by this tool, return true if the command
    // modifies the picture passed in argument p
    virtual bool execute(picture &p, const string &command) = 0;

    tool() = default;
};

#endif
