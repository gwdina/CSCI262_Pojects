/*
 * utility.cpp
 *
 * Author: C. Painter-Wakefield
 *
 * Utility class static function implementations.
 *
 * Last modified: 1/16/2022
 */

#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

#include "utility.h"

using namespace std;

string utility::get_line(const string &message) {
    string input;

    while (input.empty()) {
        _prompt(message);
        getline(cin, input);
        trim(input);
    }

    return input;
}

string utility::get_word(const string &message) {
    string result;
    string input = get_line(message);

    istringstream sin(input);
    sin >> result;

    if (!sin.eof()) {
        throw runtime_error("Invalid input: more than one word.");
    }

    return result;
}

string utility::get_lines(const string &message) {
    // get at least one line
    string result = get_line(message);

    while (true) {
        string input;
        getline(cin, input);
        trim(input);
        if (input.empty()) break;
        result.push_back('\n');
        result += input;
    }

    return result;
}

int utility::get_integer(const string &message) {
    int result;
    string input = get_line(message);

    istringstream sin(input);
    sin >> result;

    if (!sin.eof()) {
        throw runtime_error("Invalid input: text after integer.");
    }

    return result;
}

vector<int> utility::get_integers(unsigned count, const string &message) {
    vector<int> result;
    string input = get_line(message);

    istringstream sin(input);
    for (unsigned i = 0; i < count; i++) {
        int val;
        sin >> val;
        result.push_back(val);
    }

    if (!sin.eof()) {
        throw runtime_error("Invalid input: text after last integer.");
    }

    return result;
}

void utility::display_menu(const vector<string> &headers, const vector<vector<string>> &rows) {
    vector<size_t> widths;

    for (const string &s: headers) {
        widths.push_back(s.size());
    }

    for (const auto &row: rows) {
        if (row.size() != headers.size()) {
            throw runtime_error("Menu row size does not match header size.");
        }
        for (size_t i = 0; i < row.size(); i++) {
            widths[i] = max(widths[i], row[i].size());
        }
    }

    cout << "What would you like to do?" << endl;
    cout << endl;

    for (size_t i = 0; i < headers.size(); i++) {
        cout << left << setw((int)widths[i]) << headers[i] << ' ';
    }
    cout << endl;

    for (auto w: widths) {
        cout << string(w, '-') << ' ';
    }
    cout << endl;

    for (auto &row: rows) {
        for (size_t i = 0; i < headers.size(); i++) {
            cout << left << setw(widths[i]) << row[i] << ' ';
        }
        cout << endl;
    }
}

// This is not a very efficient implementation.
void utility::trim(string &s) {
    while (!s.empty() && isspace(s.back())) s.pop_back();
    while (!s.empty() && isspace(s.front())) s.erase(0, 1);
}

void utility::_prompt(const string &message) {
    if (!message.empty()) {
        cout << message << ": ";
    }
}
