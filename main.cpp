///@file
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <debugapi.h>
#include <ostream>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <json/single_include/nlohmann/json.hpp>
#include "i3lib.h"
#include "initLogger.h"

using std::cerr;
using i3::Logger;
using json = nlohmann::json;

namespace {
    constexpr const char* logFilename = "i3log.log";
}

int main(int argc, const char* argv[])
{
    int result = 0;

    try {
        std::ofstream logFile;
        app::initLogger(logFilename, logFile);

        json config;

        {
            std::ifstream configFile("config.json");
            config = json::parse(configFile);
        }

        i3::Prng seedPrng;    

        sf::RenderWindow window(sf::VideoMode(config["display"]["width"], config["display"]["height"]), "SFML works!");
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
    }
    catch(std::exception &ex) {
        i3logErr << "Exception caught in main()!:\n    " << ex.what() << "\n    Exiting!\n";
    }
    catch(...) {
        i3logErr << "Unexpected exception (not derived from std::exception) caught in main! Exiting!\n";
    }

    return result;
}
