#ifndef INITLOGGER_H
#define INITLOGGER_H
///@file
#include <string>
#include <fstream>

namespace app {
    void initLogger(const std::string logFilename, std::ofstream &logFile);
}

#endif //INITLOGGER_H
