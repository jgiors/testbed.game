///@file
#include "precomp.h"

using std::cerr;
using i3::Logger;

void app::initLogger(const std::string logFilename, std::ofstream &logFile) {
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
} //app::initLogger()
