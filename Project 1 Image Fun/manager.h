/*
 * manager.h
 *
 * Author: C. Painter-Wakefield
 *
 * Provides a top-level user interface for the Image Fun program, and functions
 * to load and save pictures.  Other capabilities are provided by separate tool
 * classes (subclasses of tool) which are added using the install_tool() method.
 *
 * Last modified: 1/16/2022
 */

#ifndef _MANAGER_H
#define _MANAGER_H

#include <string>
#include <vector>

#include "picture.h"
#include "tool.h"

using namespace std;

class manager {
public:
    // nothing really to do here
    manager() = default;

    // add a tool
    void install_tool(tool* t) { _tools.push_back(t); }

    // loop until user exits, displaying top-level utility and invoking different
    // functions
    void run();

private:
    // load an image into _picture (must be a PNG file)
    void _load();

    // save the image in _picture to a PNG file
    void _save();

    // assume a valid picture has non-zero width
    bool _has_picture() { return _picture.width() > 0; }

    picture       _picture;
    vector<tool*> _tools;

    string        _last_filename;
    bool          _is_modified = false;

    struct _action {
        tool *t;
        string verb;
    };
};

#endif
