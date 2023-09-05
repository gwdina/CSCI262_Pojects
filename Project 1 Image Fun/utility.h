/*
 * utility.h
 *
 * Author: C. Painter-Wakefield
 *
 * Utility functions for:
 *  - collecting user input
 *  - displaying menus of options
 *  - trimming strings
 *
 * Last modified: 1/16/2022
 */

#ifndef _UTILITY_H
#define _UTILITY_H

#include <string>
#include <vector>

using namespace std;

class utility {
public:
    /*
     * The utility functions below for getting input will prompt until
     * a non-empty line of text is input.  If a message is supplied,
     * it will be used to prompt the user.  If no message is supplied,
     * it is assumed the caller prompted the user already.
     */

    // get a line of input, trimmed
    static string get_line(const string &message = "");

    // get a single word; throw an error if more than one word
    // is provided
    static string get_word(const string &message = "");

    // get lines of input until an empty line is entered; lines
    // will be trimmed and separated by newline characters.
    static string get_lines(const string &message = "");

    // get a single integer; throw an error for text or extra
    // non-space characters
    static int get_integer(const string &message = "");

    // get a list of integers of specific size; throw an error for
    // text or extra non-space characters
    static vector<int> get_integers(unsigned count, const string &message = "");

    // display a menu of options
    static void display_menu(const vector<string> &headers, const vector<vector<string>> &rows);

    // trim whitespace from either end of a string
    static void trim(string &s);

private:
    static void _prompt(const string &message);
};

#endif
