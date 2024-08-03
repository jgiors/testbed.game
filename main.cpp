///@file
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <debugapi.h>
#include <ostream>
#include <fstream>
#include <filesystem>
#include <iostream>
#include "i3lib.h"
#include "initLogger.h"

using std::cerr;
using i3::Logger;

namespace {
    constexpr const char* logFilename = "i3log.log";
}

int main(int argc, const char* argv[])
{
    int result = 0;

    std::ofstream logFile;
    app::initLogger(logFilename, logFile);

    i3::Prng seedPrng;    

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return result;
}
