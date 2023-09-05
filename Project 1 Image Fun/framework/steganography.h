/*
 * editor.h
 *
 * Author: Gordon Dina
 *
 * Apply various image filters to PNG image files.
 *
 * Last modified: 2/03/2022
 */

#ifndef _STEGANOGRAPHY_H
#define _STEGANOGRAPHY_H

#include "tool.h"

using namespace std;

class steganography : public tool {
public:
    // return the utility commands and utility descriptions for the functions
    // provided by this tool
    vector<string> get_verbs() override {
        return {
            "conceal",
            "reveal"


        };
    }

    vector<string> get_menu_entries() override {
        return {
            "Hide a secret message in the image",
            "Reveals what the hidden message is in the image"

        };
    }

    // perform a command provided by this tool, return true if the command
    // modifies the picture passed in argument p
    bool execute(picture &p, const string &command) override;

    steganography() = default;

private:
    bool _conceal(picture &p, string message);
    void _reveal(picture &p);

};

#endif
