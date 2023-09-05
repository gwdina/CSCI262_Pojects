/*
 * hashtable.h
 *
 * Put the class declaration of the hashtable class here.
 *
 * Author: Gordon Dina
 */

#ifndef _HASHTABLE_PROJECT_H
#define _HASHTABLE_PROJECT_H

#include <string>
#include <vector>
#include <functional>
#include <cstddef>
#include "hash_functions.h"
#include <iostream>

using namespace std;

template <class T, class H = std::hash<T>>
class hashtable {
public:
    // constructor
    hashtable();

    // basic hashset operations
    void insert(const T& key);
    void remove(const T& key);
    bool contains(const T& key);
    size_t size();


    // diagnostic functions
    double load_factor();

    // convenience method, invokes the "hash" template parameter
    // function object to get a hash code
    static unsigned hash(const T &key) {
        H h; //H-hash1 (default) (1.734, 2.24, 1.633), hash2 (8.505, 8.503, 8.478), hash3 (2.361, 1.805, 1.817), hash4 (1.92, 2.136, 1.805)
        return h(key);
    }
//hisagram
    int capacity(); //just _cap

    void buckets();


private:
    int _cap;
    int _size;
    vector<vector<T>> _table;

    //hashtable<string, hash1>;

};
template <class T, class H >

hashtable<T, H>::hashtable(){
    _cap = 4;
    _size = 0;
    _table.resize(_cap);
}

template <class T, class H >
void hashtable<T, H>::insert(const T& key){
    if(contains(key) == false){
        if(_size >= (_cap * 3/4)){
            _cap *= 2;
            vector<vector<T>> the;
            the.resize(_cap);
            for(int i=0; i < _cap/2;++i){
                for(int j=0; j < _table.at(i).size();++j){
                    int index = hash(_table.at(i).at(j)) % _cap;
                    the[index].push_back(_table.at(i).at(j));
                }
            }
            _table.swap(the);

        }
        size_t index = hash(key) % _cap;
        _table[index].push_back(key);
        _size += 1;
    }


}

template <class T, class H >
void hashtable<T, H>::remove(const T& key){
    if(contains(key) == true) {
        size_t index = hash(key) % _cap;
        for (int i = 0; i < _table.at(index).size(); ++i) {
            if (_table.at(index).at(i) == key) {
                _table.at(index).erase(_table.at(index).begin() + i);
                --_size;
                return;
            }
        }
    }
}

template <class T, class H >
bool hashtable<T, H>::contains(const T& key){
    size_t index = hash(key) % _cap;
    for(int i=0; i < _table.at(index).size();++i) {
            if (_table.at(index).at(i) == key) {
                return true;
            }
        }
    return false;
}

template <class T, class H >
size_t hashtable<T, H>::size(){
    return _size;
}

template <class T, class H >
double hashtable<T, H>::load_factor(){
    double number = double (_size) / _cap;
    return number;
}
///////////////////////////////////////////

template <class T, class H >
int hashtable<T, H>::capacity(){
    return _cap;
}


template <class T, class H >

void hashtable<T, H>::buckets(){
    int max=0;
    for(int i=0; i < _table.size(); ++i){
        if(_table.at(i).size() > max){
            max = _table.at(i).size();
        }
    }

    vector<int> bucket_sizes;


    for(int i=0; i < _table.size(); ++i){
        bucket_sizes.push_back(_table.at(i).size());
    }

    for(int i=0; i <= max; ++i) {
        int count = 0;
        for(int j=0; j < bucket_sizes.size(); ++j){
            if(bucket_sizes.at(j) == i){
                ++count;
            }
        }
        cout << endl << i << ": " << count;
        }
    cout << endl;

    }


#endif
