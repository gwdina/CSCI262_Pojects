/*
 * manager.cpp
 *
 * Author: C. Painter-Wakefield
 *
 * Implementation code for the manager class.
 *
 * Last modified: 1/16/2022
 */

#include <iostream>
#include <stdexcept>
#include <algorithm>

#include "manager.h"
#include "utility.h"

using namespace std;

void manager::run() {
    const vector<string> columns = { "Command", "Description" };

    vector<vector<string>> rows;
    vector<_action> tool_actions;

    rows.push_back({ "load", "Load a picture" });
    rows.push_back({ "save", "Save the current picture" });

    for (tool* tp: _tools) {
        vector<string> verbs = tp->get_verbs();
        vector<string> descriptions = tp->get_menu_entries();

        if (verbs.size() != descriptions.size()) {
            throw runtime_error("Tool mismatch: number of verbs does not match number of utility entries.");
        }

        for (size_t i = 0; i < verbs.size(); i++) {
            tool_actions.push_back({tp, verbs[i] });
            rows.push_back({ verbs[i], descriptions[i] });
        }
    }

    rows.push_back({ "exit", "Exit this program" });

    while (true) {
        string command;
        bool recognized_command = false;

        cout << string(78, '=') << endl << endl;

        if (!_has_picture()) {
            cout << "You currently have no picture loaded.";
        }
        else {
            if (_last_filename.empty()) {
                cout << "Current picture: unnamed";
            }
            else {
                cout << "Current picture: " << _last_filename;
            }

            if (_is_modified) {
                cout << ", modified since last save";
            }

            cout << ".";
        }
        cout << endl << endl;

        utility::display_menu(columns, rows);

        cout << endl;

        try {
            command = utility::get_word("Please enter command");
        }
        catch (runtime_error &e) {
            cout << e.what() << endl << endl;
            continue;
        }

        if (command == "exit") break;
        if (command == "load") {
            _load();
            recognized_command = true;
        }
        else if (command == "save") {
            _save();
            recognized_command = true;
        }
        else {
            for (auto &a : tool_actions) {
                if (command == a.verb) {
                    bool modified = a.t->execute(_picture, command);
                    _is_modified = _is_modified || modified;
                    recognized_command = true;
                    break;
                }
            }
        }
        if (!recognized_command) {
            cout << "I didn't understand that." << endl << endl;
        }
    }
}

void manager::_load() {
    string filename;
    try {
        filename = utility::get_word("Please enter filename of the picture to load, e.g., \"selfie.png\"");
        cout << endl;
        _picture.load(filename);
    }
    catch (runtime_error &e) {
        cout << e.what() << endl << endl;
        return;
    }
    cout << "Load successful!" << endl << endl;
    _last_filename = filename;
    _is_modified = false;
}

void manager::_save() {
    string filename;
    try {
        filename = utility::get_word("Please enter filename of the picture to save, e.g., \"new.png\"");
        cout << endl;
        _picture.save(filename);
    }
    catch (runtime_error &e) {
        cout << e.what() << endl << endl;
        return;
    }
    cout << "Save successful!" << endl << endl;
    _last_filename = filename;
    _is_modified = false;
}



