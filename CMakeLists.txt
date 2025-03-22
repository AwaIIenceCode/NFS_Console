# CMakeLists.txt: Файл сборки проекта (настройка CMake для компиляции).

cmake_minimum_required(VERSION 3.20)
project(NFS_Console)

set(CMAKE_CXX_STANDARD 17)

# Путь к SFML
set(SFML_DIR "J:/MyIDE/SFML/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5.1 REQUIRED COMPONENTS graphics window system)

# Собрать все .cpp файлы из Core/ и его подпапок
file(GLOB_RECURSE CORE_SOURCES "Core/*.cpp")

# Объединить main.cpp и все файлы из Core/
set(SOURCES main.cpp ${CORE_SOURCES})

# Создать исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES})

# Линковка с SFML
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)