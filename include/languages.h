#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>

#include "languages.h"
using namespace std;
/**
 * @class - describes the language
 */
class Languege{
public:
    string name;
    int rating;
    string clas;
    /**
     *
     * @brief - constructor
     */
    Languege(string , int, string);
};


#endif //LANGUAGE_H