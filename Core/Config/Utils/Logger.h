//
// Created by AwallencePC on 19.03.2025.
// Папка Utils: Вспомогательные утилиты (счёт, таймер, логи).
// Logger: Записывает логи игры в файл (для отладки и отчёта).
//

#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>

class Logger
{
public:
    // Получить единственный экземпляр (синглтон)
    static Logger& getInstance()
    {
        static Logger instance;
        return instance;
    }

    // Записать сообщение в лог
    void log(const std::string& message);

private:
    Logger(); // Приватный конструктор
    ~Logger(); // Деструктор для закрытия файла

    // Запрещаем копирование
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::ofstream logFile; // Файл для логов
};



#endif //LOGGER_H
