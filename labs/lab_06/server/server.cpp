//
// Created by Rostyslav on 06.11.2023.
//
#include <SFML/Graphics.hpp>
#include <boost/asio.hpp>
#include "iostream"

using namespace sf;
using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::system;

constexpr short SERVER_PORT = 8000;
constexpr short MAX_UDP_SIZE = 1024;
constexpr const char* WINDOW_TITLE = "Lab 06";
constexpr size_t WINDOWS_WIDTH = 800;
constexpr size_t WINDOWS_HEIGHT = 600;


class Drawer{
public:
    static std::vector<CircleShape*> circles;
    static std::vector<RectangleShape*> rectangles;
    static std::vector<std::vector<Vertex>> lines;
    static void Draw(RenderWindow& window){
        for(auto &&x :circles){
            window.draw(*x);
        }

        for(auto &&x: rectangles){
            window.draw(*x);
        }
        for(auto &&line: lines){
            for (auto& vertex : line) {
                vertex.color = Color::Red;
            }
            window.draw(&line[0], line.size(), Lines);
        }
    }

    static void ParseRectangle(std::vector<std::string> words){
        std::vector<int> coords;
        for (int i = 2; i <= 5; ++i) { // start from the third word
            std::istringstream iss(words[i]);
            int value;
            if (!(iss >> value)) {
                std::cout << "Invalid coordinate: " << words[i] << std::endl;
                return;
            }
            coords.push_back(value);
        }

        RectangleShape* rectangle = new RectangleShape(Vector2f(coords[2] - coords[0], coords[3] - coords[1]));
        rectangle->setFillColor(Color::Red);

        // Set the position to the first two coordinates
        rectangle->setPosition(Vector2f(coords[0], coords[1]));



        rectangles.push_back(rectangle);  // Store the pointer

        // For demonstration, let's just print out the size and position
        std::cout << "Rectangle is added at position (" << rectangle->getPosition().x
                  << ", " << rectangle->getPosition().y << ") with size ("
                  << rectangle->getSize().x << ", " << rectangle->getSize().y << ")" << std::endl;
    }

    static void ParseCircle(std::vector<std::string> words){
        std::vector<int> params;
        for (int i = 2; i <= 4; ++i) {
            std::istringstream iss(words[i]);
            int value;
            if (!(iss >> value)) {
                std::cout << "Invalid parameter for circle: " << words[i] << std::endl;
                return;
            }
            params.push_back(value);
        }

        // Dynamically allocate a new CircleShape
        CircleShape* circle = new CircleShape(static_cast<float>(params[2]));
        circle->setPosition(static_cast<float>(params[0]), static_cast<float>(params[1]));

        // For demonstration, let's just print out the position and radius
        std::cout << "Circle added at position (" << circle->getPosition().x
                  << ", " << circle->getPosition().y << ") with radius "
                  << circle->getRadius() << std::endl;
        circle->setFillColor(Color::Red);

        // Store the pointer in the vector
        circles.push_back(circle);
    }


    static void ParseLine(std::vector<std::string> words){

        std::vector<int> coords;
        for (int i = 2; i <= 5; ++i) {
            std::istringstream iss(words[i]);
            int value;
            if (!(iss >> value)) {
                std::cout << "Invalid coordinate for line: " << words[i] << std::endl;
                return;
            }
            coords.push_back(value);
        }

        std::vector<Vertex> line = {
                Vertex(Vector2f(static_cast<float>(coords[0]), static_cast<float>(coords[1]))),
                Vertex(Vector2f(static_cast<float>(coords[2]), static_cast<float>(coords[3])))
        };

        lines.push_back(line);
        std::cout << "Line added from (" << line[0].position.x << ", " << line[0].position.y
                  << ") to (" << line[1].position.x << ", " << line[1].position.y << ")" << std::endl;
    }

    static void ParseInfo(std::string message){
        std::istringstream iss(message);
        std::vector<std::string> words;
        std::string word;

        while (iss >> word) {
            words.push_back(word);
        }

        if(words.size() < 2 || words[0] != "draw"){
            std::cout<<"Unknown parameters";
            return;
        }

        if(words[1] ==  "square" && words.size() == 6)
            ParseRectangle(words);
        else if(words[1] == "circle" && words.size() == 5)
            ParseCircle(words);
        else if(words[1] == "line" && words.size() == 6)
            ParseLine(words);
        else
            std::cout<<"Unknown shape or incorrect count of parameters";
    }
};
std::vector<CircleShape*> Drawer::circles;
std::vector<RectangleShape*> Drawer::rectangles;
std::vector<std::vector<Vertex>> Drawer::lines;


int main()
{
    // create the window
    RenderWindow window(VideoMode(WINDOWS_WIDTH, WINDOWS_HEIGHT), WINDOW_TITLE);
    io_service io_service;
    udp::socket socket(io_service, udp::endpoint(udp::v4(), SERVER_PORT));
    udp::endpoint sender_endpoint;

    std::cout << "Server is listening on port " << SERVER_PORT << std::endl;

    // Buffer for incoming data
    std::vector<char> buffer(MAX_UDP_SIZE);
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                window.close();
        }


        // clear the window with black color
        window.clear(Color::White);

        // draw everything here...

        Drawer::Draw(window);

        // end the current frame
        window.display();
        error_code error;
        size_t length = socket.receive_from(asio::buffer(buffer), sender_endpoint, 0, error);

        if (error && error != error::message_size) {
            std::cerr << "Exception: " << error.what() << std::endl;
            continue;
        }

        std::string message(buffer.begin(), buffer.begin() + length);
        std::cout << "Received: " << message << " from " << sender_endpoint << std::endl;
        Drawer::ParseInfo(message);
    }

    return 0;
}

