#pragma once

#include <boost/asio.hpp>
#include <boost/beast.hpp>

boost::beast::http::response<boost::beast::http::string_body> handle_test(boost::beast::http::request<boost::beast::http::string_body>& request) {
    // Prepare the response message
    boost::beast::http::response<boost::beast::http::string_body> response;
    response.version(request.version());
    response.result(boost::beast::http::status::ok);
    response.set(boost::beast::http::field::server, "My boost::beast::http Server");
    response.set(boost::beast::http::field::content_type, "text/plain");
    response.body() = "Hello, World!";
    response.prepare_payload();

    return response;
}

// TODO Finish when mongocxx is up and running
// boost::beast::http::response<boost::beast::http::string_body> handle_get_tasks(boost::beast::http::request<boost::beast::http::string_body>& request) {

//     boost::beast::http::response<boost::beast::http::string_body> response;

//     return response;
// }

boost::beast::http::response<boost::beast::http::string_body> ć(boost::beast::http::request<boost::beast::http::string_body>& request) {

    boost::beast::http::response<boost::beast::http::string_body> response;
    response.result(boost::beast::http::status::not_found);
    response.body() = "Not Found";
    response.prepare_payload();

    return response;
}

// boost::beast::http::response<boost::beast::http::string_body> handle(boost::beast::http::request<boost::beast::http::string_body>& request) {

//     boost::beast::http::response<boost::beast::http::string_body> response;
 
//     return response;
// }