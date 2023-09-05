//
// Created by gwdin on 2/9/2022.
//


#include <iostream>

#include "mondrian.h"
#include "utility.h"
#include <cstdlib>
#include <ctime>

using namespace std;

bool mondrian::execute(picture &p, const string &command) {
    if (command == "paint"){
        _paint(p);
    }


    else {
        cout << "Unknown command: " << command << endl;
        return false;
    }

    return true;
}

bool mondrian::_paint(picture &p){
    srand(time(0));
    // get picture dimensions and other user preferences
    vector<int> dimensions;
    int min_area = 0;
    try {
        dimensions = utility::get_integers(
                2,
                "Please enter the width and height of your painting as positive integers (e.g., \"800 600\")"
        );
        min_area = utility::get_integer("Please enter the minimum area for rectangles to split");
    }
    catch (runtime_error &e) {
        cout << e.what() << endl << endl;
        return false;
    }

    p.start_new(dimensions[0], dimensions[1]);

    _paint_recursive(p, 0, p.width()-1, 0, p.height()-1, min_area);

    return true;

}

void mondrian::_paint_recursive(picture &p, int left, int right, int top, int bottom, int area){
    //int x = rand()%(p.width()-1);
    //int y = rand()%(p.height()-1);

    int width = right - left;
    int height = bottom - top;

    if ((height == 0) || (width == 0)){
        return;
    }


    if((width*height) < area){
        _color_fill(p, left, right, top, bottom);
    }
    else{
        if(width > height){
            int x = rand()%width + left;
            _draw_vertical_line(p, x, top, bottom);
            _paint_recursive(p, x, right, top, bottom, area);
            _paint_recursive(p, left, x, top, bottom, area);
        }
        if(width < height){
            int y = rand()%height + top;
            _draw_horizontal_line(p, y, left, right);
            _paint_recursive(p, left, right, y, bottom, area);
            _paint_recursive(p, left, right, top, y, area);
        }
    }



}

void mondrian::_color_fill(picture &p, int left, int right, int top, int bottom) {
    int red;
    int green;
    int blue;
    int color = rand()%99;

    if (color >= 45){
        red = 255;
        green =255;
        blue =255;
    }
    if(color <= 14){
        red = 255;
        blue =0;
        green =0;
    }
    if((color >= 15) && (color <= 29)){
        blue = 128;
        red =0;
        green =0;
    }
    if((color >= 30) && (color <= 44)){
        red = 255;
        blue =0;
        green =255;
    }


    for (int i = left; i < right; i++) {
        for (int j = top; j < bottom; j++) {
            p.set(i,j,red,green, blue);
        }

    }

}

void mondrian::_draw_horizontal_line(picture &p, int y, int left, int right){
    for(int i =left; i < right; i++){
        p.set(i, y, 255, 255, 255);
    }
}

void mondrian::_draw_vertical_line(picture &p, int x, int top, int bottom){
    for(int i =top; i < bottom; i++){
        p.set(x, i, 255, 255, 255);
    }

}