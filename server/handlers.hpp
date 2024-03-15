#pragma once

#include <boost/asio.hpp>
#include <boost/beast.hpp>

#include "mongo.hpp"

boost::beast::http::response<boost::beast::http::string_body> response_fill(
    boost::beast::http::request<boost::beast::http::string_body>& request) {
    // Prepare the response message
    boost::beast::http::response<boost::beast::http::string_body> response;
    response.version(request.version());
    response.result(boost::beast::http::status::ok);
    response.set(boost::beast::http::field::server,
                 "My boost::beast::http Server");
    response.set(boost::beast::http::field::content_type, "text/plain");

    return response;
}

boost::beast::http::response<boost::beast::http::string_body> handle_test(
    boost::beast::http::request<boost::beast::http::string_body>& request) {
    boost::beast::http::response<boost::beast::http::string_body> response;
    response = response_fill(request);
    try {
        database().unreserve();
        response.body() = "Hello, World!";
    } catch (const char* e) {
        std::cerr << "Exception: " << e << std::endl;
        response.body() = "Failure";
    }
    // response.body() = request.method_string().to_string();
    response.prepare_payload();

    return response;
}

boost::beast::http::response<boost::beast::http::string_body> handle_get_tasks(
    boost::beast::http::request<boost::beast::http::string_body>& request) {
    boost::beast::http::response<boost::beast::http::string_body> response;
    response = response_fill(request);

    try {
        response.body() = database().get_task();
        // response.body() = "Success";
    } catch (const char* e) {
        std::cerr << "Exception: " << e << std::endl;
        response.body() = "Failure";
    }

    response.prepare_payload();
    return response;
}

boost::beast::http::response<boost::beast::http::string_body> handle_404(
    boost::beast::http::request<boost::beast::http::string_body>& request) {
    boost::beast::http::response<boost::beast::http::string_body> response;
    response.result(boost::beast::http::status::not_found);
    response.body() = "Not Found";
    response.prepare_payload();

    return response;
}

boost::beast::http::response<boost::beast::http::string_body>
    handle_post_deposit(
        boost::beast::http::request<boost::beast::http::string_body>& request) {
    boost::beast::http::response<boost::beast::http::string_body> response;
    response = response_fill(request);

    try {
        std::string body = request.body();
        database().insert_result(body);
        response.body() = "Success hpd";
    } catch (const char* e) {
        std::cerr << "Exception: " << e << std::endl;
        response.body() = "Failure";
    }

    response.prepare_payload();
    return response;
}

// boost::beast::http::response<boost::beast::http::string_body>
// handle(boost::beast::http::request<boost::beast::http::string_body>& request)
// {

//     boost::beast::http::response<boost::beast::http::string_body> response;

//     return response;
// }