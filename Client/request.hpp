#pragma one
class Request_handler {
    private:
    std::string URL;
    std::string PORT;

    public:
    Request_handler(std::string url, std::string port = "8080");

    std::vector<int64_t> get_task();
};