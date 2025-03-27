cmake_minimum_required(VERSION 3.20)
project(NFS_Console)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Путь к SFML
set(SFML_DIR "J:/MyIDE/SFML/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5.1 REQUIRED COMPONENTS graphics window system audio)

# Собрать все .cpp и .h файлы из Core/
file(GLOB_RECURSE CORE_SOURCES "Core/*.cpp" "Core/*.h") # Исправляем GLOB_RECURSIVE на GLOB_RECURSE

# Источники проекта
set(SOURCES
        main.cpp
        ${CORE_SOURCES}
)

# Исключаем ненужные файлы (которые ты удалил)
list(FILTER CORE_SOURCES EXCLUDE REGEX "Core/Data/Managers/Utility/TimerManager\\..*") # Удаляем TimerManager
list(FILTER CORE_SOURCES EXCLUDE REGEX "Core/Data/Managers/Interfaces/SpeedController\\..*") # Удаляем SpeedController
list(FILTER CORE_SOURCES EXCLUDE REGEX "Core/Data/States/GameOverState\\..*") # Удаляем GameOverState
list(FILTER CORE_SOURCES EXCLUDE REGEX "Core/Data/States/MenuState\\..*") # Удаляем MenuState
list(FILTER CORE_SOURCES EXCLUDE REGEX "Core/Data/States/StateManager\\..*") # Удаляем StateManager
list(FILTER CORE_SOURCES EXCLUDE REGEX "Core/UI/UIManager\\..*") # Удаляем UIManager
list(FILTER CORE_SOURCES EXCLUDE REGEX "Core/UseCases/.*") # Удаляем всю папку UseCases

# Создаём исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES})

# Указываем корень проекта для поиска заголовков
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

# Линковка с SFML
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system sfml-audio)

# Для тестов
option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
    enable_testing()
    file(GLOB_RECURSE TEST_SOURCES "Tests/*.cpp") # Исправляем тут тоже
    add_executable(NFS_Console_Tests ${TEST_SOURCES} ${CORE_SOURCES})
    target_include_directories(NFS_Console_Tests PRIVATE ${CMAKE_SOURCE_DIR})
    target_link_libraries(NFS_Console_Tests sfml-graphics sfml-window sfml-system sfml-audio)
    add_test(NAME NFS_Console_Tests COMMAND NFS_Console_Tests)
endif()