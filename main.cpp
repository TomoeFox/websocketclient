#include <iostream>
#include <string>
#include <cpprest/ws_client.h>

using namespace std;
using namespace web;
using namespace web::websockets::client;

string Message(string a) {
string response;
  websocket_client client;
  client.connect("ws://echo.websocket.org").wait();

  websocket_outgoing_message out_msg;


  out_msg.set_utf8_message(a);
  client.send(out_msg).wait();

  client.receive().then([](websocket_incoming_message in_msg) {
    return in_msg.extract_string();
  }).then([&response](string body) {
response = body;
  }).wait();

  client.close().wait();
return "Responce: "+response;
  }

int main() {
string a;
getline(cin,a);
cout << "Request: " << a  << endl;
cout<< Message(a);

  return 0;
}
