#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <string>
#include <vector>
#include <sstream>
#include "../../../Application/GameMode.h"
#include "../../../Config/Utils/Logger.h"

class SaveManager {
public:
    static SaveManager& getInstance() {
        static SaveManager instance;
        return instance;
    }

    // Сохраняем рекорд для указанного режима
    void saveRecord(GameMode mode, float time) {
        std::ofstream file("records.txt", std::ios::app);
        if (file.is_open()) {
            std::string modeStr = (mode == GameMode::TIME_TRIAL) ? "TimeTrial" : "Unknown";
            file << modeStr << " " << time << "\n";
            file.close();
            Logger::getInstance().log("Result saved: " + modeStr + " " + std::to_string(time));
        } else {
            Logger::getInstance().log("Failed to open records.txt for saving");
        }
    }

    // Загружаем рекорды для указанного режима
    std::vector<float> loadRecords(GameMode mode) {
        std::vector<float> records;
        std::ifstream file("records.txt");
        if (file.is_open()) {
            std::string line;
            std::string modeStr = (mode == GameMode::TIME_TRIAL) ? "TimeTrial" : "Unknown";
            while (std::getline(file, line)) {
                std::stringstream ss(line);
                std::string recordMode;
                float recordTime;
                ss >> recordMode >> recordTime;
                if (recordMode == modeStr) {
                    records.push_back(recordTime);
                }
            }
            file.close();
        } else {
            Logger::getInstance().log("Failed to open records.txt for reading");
        }
        return records;
    }

private:
    SaveManager() = default;
    SaveManager(const SaveManager&) = delete;
    SaveManager& operator=(const SaveManager&) = delete;
};

#endif //SAVEMANAGER_H