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

picture.cpp

Implementation code for the picture class.

Modified: 1/17/2022 (cpw) [added start_new, load, resize, and clear methods,
  renamed class to lowercase picture]
*/

#include <algorithm>
#include <stdexcept>
#include "picture.h"

picture::picture(int width, int height, int red, int green, int blue) {
    start_new(width, height, red, green, blue);
}

picture::picture(const vector<vector<int> >& grays)
{
   if (grays.size() == 0 || grays[0].size() == 0)
   {
      _width = 0;
      _height = 0;
   }
   else
   {
      _values = vector<unsigned char>(grays[0].size() * grays.size() * 4);
      _width = grays[0].size();
      _height = grays.size();
      int k = 0;
      for (int y = 0; y < _height; y++)
         for (int x = 0; x < _width; x++)
         {
            int gray = grays[y][x];
            _values[k] = gray;
            _values[k + 1] = gray;
            _values[k + 2] = gray;
            _values[k + 3] = 255;
            k += 4;
         }
   }
}

picture::picture(const string& filename)
{
  load(filename);
}

void picture::start_new(int width, int height, int red, int green, int blue) {
    clear();
    resize(width, height, red, green, blue);
}

void picture::load(const string& filename)
{
    unsigned int w, h;
    _values.clear();
    unsigned error = lodepng::decode(_values, w, h, filename.c_str());
    if (error != 0) throw runtime_error(lodepng_error_text(error));
    _width = w;
    _height = h;
}

void picture::save(const string& filename) const
{
   unsigned error = lodepng::encode(filename.c_str(), _values, _width, _height);
   if (error != 0) throw runtime_error(lodepng_error_text(error));  
}

int picture::red(int x, int y) const
{
   if (0 <= x && x < _width && 0 <= y && y < _height)
      return _values[4 * (y * _width + x)];
   else
      return 0;
}

int picture::green(int x, int y) const
{
   if (0 <= x && x < _width && 0 <= y && y < _height)
      return _values[4 * (y * _width + x) + 1];
   else
      return 0;
}

int picture::blue(int x, int y) const
{
   if (0 <= x && x < _width && 0 <= y && y < _height)
      return _values[4 * (y * _width + x) + 2];
   else
      return 0;
}

void picture::set(int x, int y, int red, int green, int blue)
{
   if (x >= 0 && y >= 0)
   {
      ensure(x, y);
      int k = 4 * (y * _width + x);
      _values[k] = red;
      _values[k + 1] = green;
      _values[k + 2] = blue;
      _values[k + 3] = 255;
   }
}

void picture::add(const picture& other, int x, int y)
{
   ensure(x + other._width - 1, y + other._height - 1);
   int k = 0;
   for (int dy = 0; dy < other._height; dy++)
      for (int dx = 0; dx < other._width; dx++)
      {
         set(x + dx, y + dy, other._values[k],
            other._values[k + 1], other._values[k + 2]);
         k += 4;
      }
}

vector<vector<int> > picture::grays() const
{
  vector<vector<int> > result(_height);
  for (int y = 0; y < _height; y++) {  
     result[y] = vector<int>(_width);
     for (int x = 0; x < _width; x++) {
        int k = 4 * (y * _width + x);
        result[y][x] = (int)(0.2126 * _values[k]
           + 0.7152 * _values[k + 1]
           + 0.0722 * _values[k + 2]);
     }
  }
  return result;   
}

void picture::resize(int new_width, int new_height, int red, int green, int blue) {
    if (new_width == 0) new_height = 0;
    if (new_height == 0) new_width = 0;

    vector<unsigned char> new_values(4 * new_width * new_height, 255);
    for (int y = 0; y < min(_height, new_height); y++)
        for (int x = 0; x < min(_width, new_width); x++)
            for (int k = 0; k < 4; k++)
                new_values[4 * (y * new_width + x) + k] = _values[4 * (y * _width + x) + k];
    for (int y = _height; y < new_height; y++) {
        for (int x = _width; x < new_width; x++) {
            new_values[4 * (y * new_width + x) + 0] = red;
            new_values[4 * (y * new_width + x) + 1] = green;
            new_values[4 * (y * new_width + x) + 2] = blue;
            new_values[4 * (y * new_width + x) + 3] = 255;
        }
    }
    _values.swap(new_values);
    _width = new_width;
    _height = new_height;
}

void picture::clear() {
    _values.clear();
    _width = 0;
    _height = 0;
}

/**
   Ensures that the given point exists.
 */
void picture::ensure(int x, int y)
{
   if (x >= _width || y >= _height)
   {
      int new_width = max(x + 1, _width);
      int new_height = max(y + 1, _height);
      vector<unsigned char> new_values(4 * new_width * new_height);
      fill(new_values.begin(), new_values.end(), 255); // fill with white
      int j = 0;
      for (int dy = 0; dy < _height; dy++)
         for (int dx = 0; dx < _width; dx++)
            for (int k = 0; k < 4; k++, j++)
               new_values[4 * (dy * new_width + dx) + k] = _values[j];
      _values.swap(new_values);
      _width = new_width;
      _height = new_height;
   }
}

