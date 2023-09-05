//
// Created by gwdin on 2/9/2022.
//

#ifndef _MONDRIAN_H
#define _MONDRIAN_H

#include "tool.h"

using namespace std;

class mondrian : public tool {
public:
    // return the utility commands and utility descriptions for the functions
    // provided by this tool
    vector<string> get_verbs() override {
        return {
            "paint"

        };
    }

    vector<string> get_menu_entries() override {
        return {
            "Creates a blank canvas and fills it in with rectangles"

        };
    }

    // perform a command provided by this tool, return true if the command
    // modifies the picture passed in argument p
    bool execute(picture &p, const string &command) override;

    mondrian() = default;

private:
    bool _paint(picture &p);
    void _paint_recursive(picture &p, int left, int right, int top, int bottom, int area);
    void _color_fill(picture &p, int left, int right, int top, int bottom);
    void _draw_horizontal_line(picture &p, int y, int left, int right);
    void _draw_vertical_line(picture &p, int x, int top, int bottom);
};

#endif
