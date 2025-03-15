/*
 WebSocketClient.hpp
 Header file for the WebSocket client class
 Defines the WebSocketClient class and its methods

 */
#ifndef WEBSOCKETCLIENT_HPP
#define WEBSOCKETCLIENT_HPP

#include <iostream>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>

/*
   Constructor to initialize the WebSocket client
   Connect to the given WebSocket server
   Send a message to the WebSocket server
   Callback for when the connection is opened
   Callback for receiving messages

 */

class WebSocketClient {
public:
    WebSocketClient();
    void connect(const std::string& uri);
    void sendMessage(const std::string& message);
    void onOpen(websocketpp::connection_hdl hdl);
    void close();

    /*
       WebSocket client instance
       Stores the connection handle for sending messages
     */

private:
    void onMessage(websocketpp::connection_hdl hdl, websocketpp::client<websocketpp::config::asio_client>::message_ptr msg);
    websocketpp::client<websocketpp::config::asio_client> client;
        websocketpp::connection_hdl connection_handle;
};

#endif
