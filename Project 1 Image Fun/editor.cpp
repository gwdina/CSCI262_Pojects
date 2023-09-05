/*
 * editor.cpp
 *
 * Author: Gordon Dina
 *
 * Implementation code for the editor class.
 *
 * Last modified: 1/20/2022
 */

#include <iostream>

#include "editor.h"

using namespace std;

bool editor::execute(picture &p, const string &command) {
    if (command == "negate") _negate(p);
    else if (command == "grayscale") {
        _grayscale(p);
    }
    else if (command == "extreme_contrast") {
        _extremecontrast(p);
    }
    else if (command == "horizontal_flip") {
        _horizontalflip(p);
    }
    else if (command == "enlarge") {
        _enlarge(p);
    }
    else if (command == "reduce") {
        _reduce(p);
    }

    else {
        cout << "Unknown command: " << command << endl;
        return false;
    }

    return true;
}

void editor::_negate(picture &p) {
    int w = p.width();
    int h = p.height();

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            p.set(x, y, 255 - p.red(x, y), 255 - p.green(x, y), 255 - p.blue(x, y));
        }
    }
}

void editor::_grayscale(picture &p) {
    int w = p.width();
    int h = p.height();

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            p.set(x, y, (p.red(x, y) + p.green(x, y) + p.blue(x, y))/3, (p.red(x, y) + p.green(x, y) + p.blue(x, y))/3, (p.red(x, y) + p.green(x, y) + p.blue(x, y))/3);
        }
    }
}

void editor::_extremecontrast(picture &p) {//ask about with professer on monday or ask on pizza
    int w = p.width();
    int h = p.height();

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int r = p.red(x, y);
            int g = p.green(x, y);
            int b = p.blue(x, y);


            if (r <= 127){
                r = 0;
            }
            else if (r > 127) {
                r = 255;
            }

            if (g <= 127){
                g = 0;
            }
            else if (g > 127) {
                g = 255;
            }

            if (b <= 127){
                b = 0;
            }
            else if (b > 127) {
                b = 255;
            }

            p.set(x, y, r, g, b);
        }
    }
}

void editor::_horizontalflip(picture &p) {
    int w = p.width();
    int h = p.height();

    picture copy;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            copy.set(w - 1 - x, y,p.red(x, y),p.green(x, y),p.blue(x, y));
        }
    }
    p = copy;

}

void editor::_enlarge(picture &p) {
    int w = p.width();
    int h = p.height();

    int new_width = 2 * w;
    int new_height = 2 * h;

    picture copy;

    copy.resize(new_width, new_height);

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            copy.set(2*x, 2*y,p.red(x, y),p.green(x, y),p.blue(x, y));
            copy.set(2*x, 2*y+1,p.red(x, y),p.green(x, y),p.blue(x, y));
            copy.set(2*x+1, 2*y,p.red(x, y),p.green(x, y),p.blue(x, y));
            copy.set(2*x+1, 2*y+1,p.red(x, y),p.green(x, y),p.blue(x, y));
        }
    }

p = copy;


}

void editor::_reduce(picture &p) {//taking (2x2) pixel average and setting it the first pixel
    int w = p.width();
    int h = p.height();

    picture copy;

    int new_width = w/2;
    int new_height = h/2;

    for (int y = 0; y < 2*h; y++) {
        for (int x = 0; x < 2*w; x++) {

            int r = (p.red(2*x, 2*y) + p.red(2*x+1, 2*y)  + p.red(2*x, 2*y+1) +p.red(2*x+1, 2*y+1))/4;
            int g = (p.green(2*x, 2*y) + p.green(2*x+1, 2*y)  + p.green(2*x, 2*y+1) + p.green(2*x+1, 2*y+1))/4;
            int b = (p.blue(2*x, 2*y) + p.blue(2*x+1, 2*y)  + p.blue(2*x, 2*y+1) + p.blue(2*x+1, 2*y+1))/4;

            copy.set(x, y,r,g,b);
        }
    }



    copy.resize(new_width, new_height);

    p = copy;


}