#pragma one
class Request_handler {
    private:
    std::string URL;
    std::string PORT;

    public:
    Request_handler(std::string url, std::string port = "8080");

    std::string get_task();
};