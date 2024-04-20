#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <string>
#include <vector>

#include "request.hpp"

Request_handler::Request_handler(std::string url, std::string port) {
    URL = url;
    PORT = port;
}

std::vector<int64_t> Request_handler::get_task() {
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::resolver resolver(io_context);
    auto const endpoints = resolver.resolve(URL, PORT);
    boost::asio::ip::tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints.begin(), endpoints.end());
    boost::beast::http::request<boost::beast::http::string_body> req(
        boost::beast::http::verb::get,
        "/tasks",
        11);
    req.set(boost::beast::http::field::host, URL);
    req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    boost::beast::http::write(socket, req);

    boost::beast::flat_buffer buffer;
    boost::beast::http::response<boost::beast::http::dynamic_body> response;
    boost::beast::http::read(socket, buffer, response);

    const boost::beast::basic_multi_buffer<std::allocator<char>>& body =
        response.body();

    std::string bodyString(boost::asio::buffers_begin(body.data()),
                           boost::asio::buffers_end(body.data()));

    boost::property_tree::ptree pt;
    std::istringstream is(bodyString);
    boost::property_tree::read_json(is, pt);

    std::vector<int64_t> indexes;
    for (const boost::property_tree::ptree::value_type& item :
         pt.get_child("data")) {
        indexes.push_back(item.second.get_value<int64_t>());
    }
    return indexes;
}