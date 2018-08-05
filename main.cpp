#include <iostream>
#include <string>
#include <cpprest/ws_client.h>
#include <sys/stat.h>
#include <fstream>
#include <chrono>
#include <time.h>

using namespace std;
using namespace web;
using namespace web::websockets::client;

ofstream _log("./logs/log",ios::app);
time_t current = time(0);
string _datatime = ctime(&current);


string Message(string a)
{

    string response;
    websocket_client client;
    client.connect("ws://echo.websocket.org").wait();

    websocket_outgoing_message out_msg;


    out_msg.set_utf8_message(a);
    client.send(out_msg).wait();

    client.receive().then([](websocket_incoming_message in_msg)
    {
        return in_msg.extract_string();
    }).then([&response](string body)
    {
        response = body;
    }).wait();

    client.close().wait();
    _log << "Response: "+response << " ||| " + _datatime;

    return "Response: "+response;
}

int main()
{

    mkdir("./logs", S_IRWXU | S_IRWXO | S_IRWXG);

    string a;
    getline(cin,a);
    cout << "Request: " << a  << endl;
    _log << "Request: " << a << " ||| " + _datatime;

    cout << Message(a) << endl;


    return 0;
}
