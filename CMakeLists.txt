cmake_minimum_required(VERSION 3.20)
project(NFS_Console)

set(CMAKE_CXX_STANDARD 17)

# Путь к SFML
set(SFML_DIR "J:/MyIDE/SFML/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5.1 REQUIRED COMPONENTS graphics window system)

# Собрать все .cpp файлы из Core/
file(GLOB_RECURSE CORE_SOURCES "Core/*.cpp")

# Источники проекта
set(SOURCES main.cpp ${CORE_SOURCES}
        Core/Config/Utils/ScaleManager.cpp
        Core/Config/Utils/ScaleManager.h
        Core/Data/States/GameState.cpp
        Core/Data/States/GameState.h
        Core/Application/MainMenuState.cpp
        Core/Application/MainMenuState.h
        Core/Application/GameplayState.cpp
        Core/Application/GameplayState.h)

# Создаём исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES})

# Указываем корень проекта для поиска заголовков
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

# Линковка с SFML
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system sfml-audio)