#include <boost/asio.hpp>

#include <string>

#include "request.hpp"

Request_handler::Request_handler(std::string url, std::string port) {
    URL = url;
    PORT = port;
}

void Request_handler::get_task() {
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::resolver resolver(io_context);
    auto const endpoints = resolver.resolve(URL, PORT);
    boost::asio::ip::tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);
    std::string request;
    boost::asio::write(socket, boost::asio::buffer(request));

    boost::asio::streambuf response;
    boost::asio::read_until(socket, response, "\r\n");

    // TODO: Unpack data to std::vector<int> or std::array<int>
}