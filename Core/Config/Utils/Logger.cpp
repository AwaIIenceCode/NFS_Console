//
// Created by AwallencePC on 19.03.2025.
//

#include "Logger.h"
#include <ctime>

Logger::Logger()
{
    logFile.open("game.log", std::ios::out | std::ios::app);

    if (!logFile.is_open())
    {
        throw std::runtime_error("Failed to open log file");
    }
}

Logger::~Logger()
{
    if (logFile.is_open())
    {
        logFile.close();
    }
}

void Logger::log(const std::string& message)
{
    if (!logFile.is_open()) return;

    time_t now = time(nullptr);
    std::string timeStr = ctime(&now);
    timeStr.pop_back();

    logFile << "[" << timeStr << "] " << message << std::endl;
    logFile.flush();
}