///@file
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <debugapi.h>
#include <ostream>
#include <fstream>
#include <filesystem>
#include <iostream>
#include "i3lib.h"

using std::cerr;
using i3::Logger;

namespace {
    constexpr auto logFilename = "i3log.log";

    void initLogger(std::ofstream &logFile)
    {
        Logger::i3logErr_instance.bDebugStreamEnabled = true;
        Logger::i3logErr_instance << I3LOG_FILE_AND_LINE "Error debug window stream established.\n";

        Logger::i3logErr_instance.attachStream(cerr);
        Logger::i3logErr_instance << I3LOG_FILE_AND_LINE "Error console stream established.\n";

        logFile.open(logFilename, std::ios_base::out | std::ios_base::app);
        bool bLogFileIsEmpty = (std::filesystem::file_size(logFilename) == 0);
        if (bLogFileIsEmpty)
        {
            logFile << I3LOG_FILE_AND_LINE << "*************\n";
            logFile << I3LOG_FILE_AND_LINE << "* i3log.log *\n";
            logFile << I3LOG_FILE_AND_LINE << "*************\n";
            logFile << I3LOG_FILE_AND_LINE << "\n";
        }
        else
        {
            logFile << I3LOG_FILE_AND_LINE << "\n";
            logFile << I3LOG_FILE_AND_LINE << "******************************************\n";
            logFile << I3LOG_FILE_AND_LINE << "* Appending output to existing i3log.log *\n";
            logFile << I3LOG_FILE_AND_LINE << "******************************************\n";
            logFile << I3LOG_FILE_AND_LINE << "\n";
        }

        logFile << I3LOG_FILE_AND_LINE;

        Logger::i3logErr_instance.attachStream(logFile);

        Logger::i3logErr_instance << I3LOG_FILE_AND_LINE "Error logging established.\n";

        Logger::i3logWarn_instance.bDebugStreamEnabled = true;
        Logger::i3logWarn_instance.attachStream(cerr);
        Logger::i3logWarn_instance.attachStream(logFile);

        Logger::i3logWarn_instance << I3LOG_FILE_AND_LINE "Warning logging established.\n";

        Logger::i3log_instance.bDebugStreamEnabled = true;
        Logger::i3log_instance.attachStream(cerr);
        Logger::i3log_instance.attachStream(logFile);

        i3log << "Default logging established.\n";
        
        Logger::i3logDebug_instance.bDebugStreamEnabled = true;
        Logger::i3logDebug_instance.attachStream(cerr);
        Logger::i3logDebug_instance.attachStream(logFile);

        i3logDebug << "Debug logging established.\n";
    } //initLogger()
} //anonymous namespace

int main(int argc, const char* argv[])
{
    int result = 0;

    std::ofstream logFile;
    initLogger(logFile);

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
