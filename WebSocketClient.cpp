#include <functional>
#include "WebSocketClient.hpp"
#include <websocketpp/common/thread.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>

/*
  Set up the client configuration
 */
WebSocketClient::WebSocketClient() {
    client.init_asio();
    client.set_message_handler(std::bind(&WebSocketClient::onMessage, this, std::placeholders::_1, std::placeholders::_2));
}



void WebSocketClient::connect(const std::string& uri) {
    websocketpp::lib::error_code ec;
    auto con = client.get_connection(uri, ec);
    if (ec) {
        std::cerr << "Connection Error: " << ec.message() << std::endl;
        return;
    }
    client.connect(con);
    websocketpp::lib::thread t([this] { client.run(); });
    t.detach();
}

/*
   Store the connection handle when the WebSocket is successfully opened
 */
void WebSocketClient::onOpen(websocketpp::connection_hdl hdl) {
    connection_handle = hdl;  // Store handle when connection opens
}


void WebSocketClient::sendMessage(const std::string& message) {
    if (connection_handle.expired()) {
        std::cerr << "Error getting connection: Bad Connection" << std::endl;
        return;
    }
    websocketpp::lib::error_code ec;
    client.send(connection_handle, message, websocketpp::frame::opcode::text, ec);

    if (ec) {
        std::cerr << "Send failed: " << ec.message() << std::endl;
    }
}
/*
   Print received messages from the WebSocket server
 */
void WebSocketClient::onMessage(websocketpp::connection_hdl, websocketpp::client<websocketpp::config::asio_client>::message_ptr msg) {
    std::cout << "Received: " << msg->get_payload() << std::endl;
}

void WebSocketClient::close() {
    client.stop();
}

