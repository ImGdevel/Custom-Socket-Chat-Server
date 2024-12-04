#include "EventHandler.h"
#include <iostream>

using namespace std;

void EventHandler::registerHandler(const string& type, HandlerFnc handler) {
    handlers[type] = handler;
}

void EventHandler::handleEvent(const std::shared_ptr<ClientSession>& session, const string& message) {

    cout << "message Type: " << message << endl;

    auto delimiterPos = message.find(":");
    if (delimiterPos == string::npos) {
        cerr << "Invalid message format: " << message << endl;
        return;
    }

    string type = message.substr(0, delimiterPos);
    string content = message.substr(delimiterPos + 1);

    cout << "type: " << type << " message: " << message << endl;

    auto it = handlers.find(type);
    if (it != handlers.end()) {
        it->second(session, content);
    } else {
        cerr << "No handler found for type: " << type << endl;
    }
}