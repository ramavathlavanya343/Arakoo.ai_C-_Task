#include "WebSocketClient.hpp"
#include <iostream>

/*
   Entry point of the WebSocket client application

 */
int main() {
    WebSocketClient wsClient;
   
    //WebSocket server URL
    std::string server = "ws://echo.websocket.events";
    wsClient.connect(server);
    std::string message;
    while (true) {
        std::cout << "Enter message: ";
        std::getline(std::cin, message);
	//Exit on empty input
        if (message == "exit") break;
        wsClient.sendMessage(message);
    }
    wsClient.close();
    return 0;
}

