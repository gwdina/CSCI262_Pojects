/*
Copyright (C) Cay S. Horstmann 2017

This file is part of the Big C++ media utilities.

The Big C++ media utilities are free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free Software Foundation,
either version 3 of the License, or (at your option) any later version.

The Big C++ media utilities are distributed in the hope that they will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with the Big C++ media
utilities. If not, see <https://www.gnu.org/licenses/>.

picture.h

A friendly wrapper for the lodepng library, allowing for
simple 2D picture editing.

Modified: 1/17/2022 (cpw) [added start_new, load, resize, and clear methods, renamed class
  to lowercase picture]
*/

#ifndef _PICTURE_H
#define _PICTURE_H

#include "framework/lodepng.h"
#include <string>
#include <vector>

using namespace std;

class picture
{
 public:
   /**
      Constructs a picture with width and height zero.
   */
   picture() = default;

   /**
      Constructs a picture from the given PNG file.
      @param filename a file name that should specify a PNG file.
   */
   explicit picture(const string& filename);

   /**
      Constructs a picture with pixels in a single color (by default,
      white).
      @param red the red value of the pixels (between 0 and 255)
      @param green the green value of the pixels (between 0 and 255)
      @param blue the blue value of the pixels (between 0 and 255)
      @param width the width of the picture
      @param height the height of the picture
   */
   picture(int width, int height, int red = 255, int green = 255, int blue = 255);

   /**
      Constructs a picture from a two-dimensional vector of gray levels.
      @param grays the gray levels
   */
   explicit picture(const vector<vector<int> >& grays);

   /**
      Returns the width of this picture.
      @return the width
   */   
   int width() const { return _width; }

   /**
      Returns the height of this picture.
      @return the height
   */
   int height() const { return _height; }

    /**
      Discard any current picture data, and create a new picture of all one color
      (white, by default).
      @param red the red value of the pixels (between 0 and 255)
      @param green the green value of the pixels (between 0 and 255)
      @param blue the blue value of the pixels (between 0 and 255)
      @param width the width of the picture
      @param height the height of the picture
    */
    void start_new(int width, int height, int red = 255, int green = 255, int blue = 255);

    /**
      Load a picture from the given PNG file, overwriting any current picture.
      @param filename a file name that should specify a PNG file.
   */
   void load(const string& filename);

   /**
      Saves this picture to the given file.
      @param filename a file name that should specify a PNG file.
   */
   void save(const string& filename) const;

   /**
      Yields the red value at the given position.
      @param x the x-coordinate (column)
      @param y the y-coordinate (row)
      @return the red value of the pixel (between 0 and 255),
      or 0 if the given point is not in the picture.
   */
   int red(int x, int y) const;

   /**
      Yields the green value at the given position.
      @param x the x-coordinate (column)
      @param y the y-coordinate (row)
      @return the green value of the pixel (between 0 and 255),
      or 0 if the given point is not in the picture.
   */
   int green(int x, int y) const;

   /**
      Yields the red value at the given position.
      @param x the x-coordinate (column)
      @param y the y-coordinate (row)
      @return the blue value of the pixel (between 0 and 255),
      or 0 if the given point is not in the picture.
   */   
   int blue(int x, int y) const;

   /**
      Sets a pixel to a given color, expanding
      the picture if necessary.
      @param x the x-coordinate (column)
      @param y the y-coordinate (row)
      @param red the red value of the pixel (between 0 and 255)
      @param green the green value of the pixel (between 0 and 255)
      @param blue the blue value of the pixel (between 0 and 255)
   */   
   void set(int x, int y, int red, int green, int blue);

   /**
      Yields the gray levels of all pixels of this image.
      @return a 2D array of gray values (between 0 and 255)
   */
   vector<vector<int> > grays() const;

   /**
      Adds a picture to this picture at a given position, expanding
      the picture if necessary.
      @param other the picture to add
      @param x the x-coordinate (column) of the top left corner
      @param y the y-coordinate (row) of the top left corner
   */
   void add(const picture& other, int x = 0, int y = 0);

   /**
      Resize the picture to the specified width and height, cropping
      if necessary; new pixels get the red, green, and blue values
      specified (by default, new pixels will be white).
      @param width the width of the picture
      @param height the height of the picture
      @param red the red value of the pixels (between 0 and 255)
      @param green the green value of the pixels (between 0 and 255)
      @param blue the blue value of the pixels (between 0 and 255)
   */
   void resize(int width, int height, int red = 255, int green = 255, int blue = 255);

   /**
      Resets the picture to zero width and height.
   */
   void clear();

private:
   void ensure(int x, int y);
   
   vector<unsigned char> _values;
   int _width = 0;
   int _height = 0;
};

#endif
