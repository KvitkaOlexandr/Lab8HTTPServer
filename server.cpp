#include "../include/server.h"
#include <cstring>
#include <time.h>
#include <jansson.h>


const string filepath = "data/text.txt";
    vector<std::string> getRequest(std::string str){
    istringstream stream(str);
    vector<std::string> request{istream_iterator<std::string>{stream},
                               istream_iterator<std::string>{}};
    return request;
}
int recognition(vector<std::string> request){
    int size = request.size();
    if(size > 1){
        std::string first = request.at(0);
        std::string second = request.at(1);
        if(first.compare("GET")) return UNKNOWN;
        if(!second.compare("/file") ) return FILE_INF;
        if(!second.compare("/") ) return ROOT;
        if(!second.compare("/file/data")) return FILE_DATA;
        if(!second.compare("/favorites")) return FAVORITES;
        std::size_t found = second.find("/favorites?");
        if (found!=std::string::npos) return FAVORITES_BY_VALUE;
        found = second.find("/favorites/");
        if (found!=std::string::npos) return FAVORITES_BY_ID;
    }
    return UNKNOWN;
}
string Response(vector<std::string> request, int recognised, vector<Languege> langueges) {

    switch(recognised){
        case UNKNOWN:
            return  Resp404();
        case ROOT:
            return RespRoot();
        case FAVORITES:
            return RespFavorites(langueges);
        case FAVORITES_BY_ID:
            return RespFavoritesById(langueges, request);
        case FAVORITES_BY_VALUE:
            return RespFavoritesByValue(langueges, request);
        case FILE_DATA:
            return RespFileData();
        case FILE_INF:
            return  RespFileInf();

    }
}
string Resp404(){
    string response404 = "HTTP/1.1 404 Not Found\n";
    return response404;
}
string RespRoot(){
    string rootResponse = "HTTP/1.1 200 OK\n";
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    rootResponse += "Connection: Closed\n"
            "Content-Type: text/html; charset=iso-8859-1\r\n\r\n";

    json_t * json = json_object();
    json_object_set_new(json, "title", json_string( "Lab_Server"));
    json_object_set_new(json, "developer", json_string("Olexandr_Kvitka"));
    json_object_set_new(json, "time", json_string(asctime(timeinfo)));
    
    char * jsonString = json_dumps(json, JSON_INDENT(2));
    rootResponse += jsonString;
    return rootResponse;
}
string RespFavorites(vector<Languege> langueges){
    string favoritesResponse = "HTTP/1.1 200 OK\n"
                            "Connection: Closed\r\n\r\n";
    json_t * json = json_object();
    json_t * arr = json_array();
    for (int i = 0; i < langueges.size(); i++) {
        Languege languege = langueges.at(i);
        json_t * lang = json_object();
        json_object_set_new(lang, "name", json_string(languege.name.c_str()));
        json_object_set_new(lang, "rating", json_integer(languege.rating));
        json_object_set_new(lang, "clas", json_string(languege.clas.c_str()));
        json_array_append(arr, lang);
    }
    json_object_set_new(json, "languages", arr);


    char * jsonString = json_dumps(json, JSON_INDENT(2));

    favoritesResponse += jsonString;


    return favoritesResponse;
}
string RespFavoritesByValue(vector<Languege> langueges, vector<std::string> request){
    string favoritesResponse = "HTTP/1.1 200 OK\n"
            "Connection: Closed\r\n\r\n";

    auto str = request.at(1);
    size_t last_index = str.find("?");
    string result = str.substr(last_index + 1);
    cout << "SUBSTR\n\n\n"<< result.substr(0,10);
    if(result.substr(0,9).compare("clas"))
        return  Resp404();
    last_index = str.find("=");
    result = str.substr(last_index + 1);
    json_t * json = json_object();
    json_t * arr = json_array();
    for (int i = 0; i < langueges.size(); i++) {
        Languege languege = langueges.at(i);
        if(languege.clas.compare(result)) continue;
        json_t * lang = json_object();
        json_object_set_new(lang, "name", json_string(languege.name.c_str()));
        json_object_set_new(lang, "rating", json_integer(languege.rating));
        json_object_set_new(lang, "clas", json_string(languege.clas.c_str()));
        json_array_append(arr, lang);
    }
    json_object_set_new(json, "languages", arr);
    char * jsonString = json_dumps(json, JSON_INDENT(2));
    favoritesResponse += jsonString;
    return favoritesResponse;
}

string RespFavoritesById(vector<Languege> langueges, vector<std::string> request){
    string favoritesResponse = "HTTP/1.1 200 OK\n"
            "Connection: Closed\r\n\r\n";
    auto str = request.at(1);
    size_t last_index = str.find_last_not_of("0123456789");
    string result = str.substr(last_index + 1);
    int index = stoi(result);
    if(index < 0 || index >= langueges.size()){
        return Resp404();
    }
    json_t * json = json_object();
    json_t * arr = json_array();

        Languege  languege = langueges.at(index);
        json_t * lang = json_object();
        json_object_set_new(lang, "name", json_string(languege.name.c_str()));
        json_object_set_new(lang, "rating", json_integer(languege.rating));
        json_object_set_new(lang, "clas", json_string(languege.clas.c_str()));
        json_array_append(arr, lang);
    json_object_set_new(json, "langueges", arr);
    char * jsonString = json_dumps(json, JSON_INDENT(2));
    favoritesResponse += jsonString;
    return favoritesResponse;
}
string RespFileInf(){
    string fileDataResponse = "HTTP/1.1 200 OK\n";
    fileDataResponse += "Connection: Closed\n"
            "Content-Type: text/html; charset=iso-8859-1\r\n\r\n";

    string data = fileReader(filepath.c_str());
    json_t * json = json_object();
    json_object_set_new(json, "name", json_string( "text.txt"));
    json_object_set_new(json, "size", json_integer(getFileSize(filepath.c_str())));
    json_object_set_new(json, "content", json_string(data.c_str()));

    char * jsonString = json_dumps(json, JSON_INDENT(2));
    fileDataResponse += jsonString;
    return fileDataResponse;
}
string RespFileData(){
    string fileDataResponse = "HTTP/1.1 200 OK\n";
    fileDataResponse += "Connection: Closed\n"
            "Content-Type: text/html; charset=iso-8859-1\r\n\r\n";

    string data = fileReader(filepath.c_str());
    auto request = getRequest(data);
    json_t * json = json_object();
    json_t * arr = json_array();
    for (auto str : request) 
    {
        string tmp = str.c_str();
        for(int i = 0; i < strlen(str.c_str()); i++){
            json_t * letterJ = json_object();
            char * ch = new char(tmp[i]);
            json_object_set_new(letterJ,  "letter", json_string(ch));
            json_array_append(arr, letterJ);
        }
    }

    json_object_set_new(json, "letters", arr);
    char * jsonString = json_dumps(json, JSON_INDENT(2));
    fileDataResponse += jsonString;
    return fileDataResponse;
}
char * fileReader(const char * fileName) {
    FILE * file = fopen(fileName, "r");
    if (file == NULL) {
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char * fcontent = (char * ) malloc(size);
    fread(fcontent, 1, size, file);
    fclose(file);
    return fcontent;
}
int getFileSize(const char * fileName) {
    FILE * file = fopen(fileName, "r");
    if (file == NULL) {
        return 0;
    }
    fseek(file, 0, SEEK_END);
    return ftell(file);
}

