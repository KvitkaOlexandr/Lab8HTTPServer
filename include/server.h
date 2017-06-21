#ifndef SERVER_H
#define SERVER_H

#include <iterator>
#include <iostream>
#include <sstream>
#include <vector>
#include "languages.h"
using namespace std;
/**
 * @brief enum of responses from recognition
 */
enum {
    OK,
    UNKNOWN,
    WRONG_INDEX,
    ROOT,
    FAVORITES,
    FILE_INF,
    FILE_DATA,
    FAVORITES_BY_ID,
    FAVORITES_BY_VALUE
};

/**
 *
 * @param str - string to divide
 * @return vector of separated words
 */
vector<std::string> getRequest(std::string str);
/**
 *
 * @param request - vector of separated words
 * @return int representing command
 */
int recognition(vector<std::string> request);
/**
 * @brief decides what response to do
 * @param request - words of http-get
 * @param recognised - value returned by recognition
 * @param langueges - vector of langueges
 * @return final response
 */
string Response(vector<std::string> request, int recognised, vector<Languege> langueges);
/**
 *
 * @return 404 statused empty response
 */
string Resp404();
/**
 *
 * @return response to /
 */
string RespRoot();
/**
 *
 * @param langueges vector of langueges to be turned into response
 * @return response on /favorites
 */
string RespFavorites(vector<Languege> langueges);
/**
 *
 * @param langueges vector of langueges to be turned into response
 * @return response on /favorites?clas={value}
 */
string RespFavoritesByValue(vector<Languege> langueges, vector<std::string> request);
/**
 *
 * @param langueges vector of langueges to be turned into response
 * @return response on /favorites/{id}
 */
string RespFavoritesById(vector<Languege> langueges, vector<std::string> request);
/**
 *
 * @return response to /file
 */
string RespFileInf();
/**
 *
 * @return response to /file/data
 */
string RespFileData();
/**
 *
 * @param fileName
 * @return all data from file in str
 */
char * fileReader(const char * fileName);
/**
 *
 * @param fileName
 * @return size of file
 */
int getFileSize(const char * fileName);

#endif //HTTPSERVERLAB_PROCESSOR_H