#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>  

/*
    The base for this code comes from:
    https://medium.com/@sidhanthpandey/how-to-create-an-http-server-in-c-812cee49ff77
*/

void handleRequest(boost::beast::http::request<boost::beast::http::string_body>& request, boost::asio::ip::tcp::socket& socket) {
    // Prepare the response message
    boost::beast::http::response<boost::beast::http::string_body> response;
    response.version(request.version());
    response.result(boost::beast::http::status::ok);
    response.set(boost::beast::http::field::server, "My boost::beast::http Server");
    response.set(boost::beast::http::field::content_type, "text/plain");
    response.body() = "Hello, World!";
    response.prepare_payload();

    // Send the response to the client
    boost::beast::http::write(socket, response);
}

void runServer() {
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor(io_context, {boost::asio::ip::tcp::v4(), 8080});

    while (true) {
        boost::asio::ip::tcp::socket socket(io_context);
        acceptor.accept(socket);

        // Read the http request
        boost::beast::flat_buffer buffer;
        boost::beast::http::request<boost::beast::http::string_body> request;
        boost::beast::http::read(socket, buffer, request);

        // Handle the request
        if (request.target()=="/test"){
            handleRequest(request, socket);
        }else{
            boost::beast::http::response<boost::beast::http::string_body> response;
            response.result(boost::beast::http::status::not_found);
            response.body() = "Not Found";
            response.prepare_payload();
            boost::beast::http::write(socket, response);
        }

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