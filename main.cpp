#include <iostream>
#include <time.h>
#include <progbase-cpp/net.h>
#include <sstream>
#include <vector>
#include <iterator>
#include "include/server.h"
#include "include/languages.h"


using namespace std;
using namespace progbase::net;


int main(int argc, char * argv[]) {
    vector<Languege> languages;
    languages.push_back(Languege("Ci", 3, "Procedured"));
    languages.push_back(Languege("Ci plus plus", 1, "Object-oriented"));
    languages.push_back(Languege("Java", 2, "Object-oriented"));
    languages.push_back(Languege("Basic", 4, "Procedured"));
    languages.push_back(Languege("Python", 5, "Multi-paradigmatic"));
    const int serverPort = 9000;
    TcpListener listener;
    NetMessage message(10000);
    try {
        listener.bind(IpAddress("127.0.0.1", serverPort));
        listener.start();
        while (true) {
            cout << ">> Waiting for clients at " << serverPort << "..." << endl;
            TcpClient * client = listener.accept();
            client->receive(message);
            cout << ">> Received: " << endl << message.dataAsString() << endl;
            std::string data = message.dataAsString();
            auto request = getRequest(data);
            int status = recognition(request);
            string backMessage = Response(request, status, languages);
            cout << "RESOPNSE \n" << backMessage;
            message.setDataString(backMessage);
            client->send(message);
            cout << ">> Response sent." << endl;
            delete client;
        }
    } catch(NetException const & exc) {
        cerr << exc.what() << endl;
    }

}