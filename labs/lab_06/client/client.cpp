//
// Created by Rostyslav on 06.11.2023.
//
#include <iostream>
#include <string>
#include <boost/asio.hpp>

constexpr const char* SERVER_IP = "127.0.0.1";
constexpr short SERVER_PORT = 8000;

int main(int argc, char** argv) {
    // Convert the cmd args
    std::vector<std::string> args(argv + 1, argv + argc);

    if (args.size() < 1) {
        std::cout << "Usage: client '<command>'" << std::endl;
        return 1;
    }

    using namespace boost;
    using namespace boost::asio;
    using namespace boost::asio::ip;
    using namespace boost::system;

    // Concatenate all arguments into a single string
    std::string command;
    for (const auto& arg : args) {
        if (!command.empty()) {
            command += " ";
        }
        command += arg;
    }

    io_service io_service;
    udp::socket socket(io_service);
    udp::endpoint remote_endpoint;

    // Open the socket
    socket.open(udp::v4());

    // Resolve the remote endpoint
    remote_endpoint = udp::endpoint(address::from_string(SERVER_IP), SERVER_PORT);

    // Send the entire command
    error_code error;
    socket.send_to(buffer(command), remote_endpoint, 0, error);

    if (error) {
        std::cerr << error.what() << std::endl;
        return 2;
    }
    std::cout << "Message sent successfully: " << command << std::endl;

    return 0;
}


