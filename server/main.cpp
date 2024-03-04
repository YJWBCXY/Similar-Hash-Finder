#include <cstdint>
#include <vector>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

#include <boost/asio.hpp>
#include <boost/beast.hpp>

#include "handlers.hpp"

/*
    The base for this code comes from:
    https://medium.com/@sidhanthpandey/how-to-create-an-http-server-in-c-812cee49ff77
*/


void runServer() {
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor(io_context,
                                            {boost::asio::ip::tcp::v4(), 8080});

    while (true) {
        boost::asio::ip::tcp::socket socket(io_context);
        acceptor.accept(socket);

        // Read the http request
        boost::beast::flat_buffer buffer;
        boost::beast::http::request<boost::beast::http::string_body> request;
        boost::beast::http::read(socket, buffer, request);

        boost::beast::http::response<boost::beast::http::string_body> response;

        // Handle the request
        if (request.target() == "/test") {
            response = handle_test(request);
        } else if (request.target() == "/tasks") {
            response = handle_get_tasks(request);
        } else {
            response = handle_404(request);
        }
        // Send the response to the client
        boost::beast::http::write(socket, response);

        // Close the socket
        socket.shutdown(boost::asio::ip::tcp::socket::shutdown_send);
    }
}

int main() {
    try {
        runServer();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}