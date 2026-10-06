cmake_minimum_required(VERSION 3.16)

project(crawlerzoo-bot
    VERSION 0.1.0
    DESCRIPTION "CrawlerZoo bot"
    LANGUAGES CXX)

# ---------------------------------------------------------------- C++17 ----
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Emit build/compile_commands.json. clangd (via .clangd) reads it for the
# per-file flags, including Qt's -isystem include dirs — without it the
# language server can't resolve `#include <QCoreApplication>`.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# ------------------------------------------------------- Qt tooling --------
# AUTOMOC/AUTOUIC/AUTORCC run moc/uic/rcc over the target's sources.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Prefer Qt6, fall back to Qt5 on machines that only ship Qt5.
find_package(Qt6 6.2 QUIET COMPONENTS Core Network)
if(Qt6_FOUND)
    set(QT_VERSION_MAJOR 6)
    set(QT_CORE Qt6::Core)
    set(QT_NETWORK Qt6::Network)
else()
    find_package(Qt5 5.15 REQUIRED COMPONENTS Core Network)
    set(QT_VERSION_MAJOR 5)
    set(QT_CORE Qt5::Core)
    set(QT_NETWORK Qt5::Network)
endif()

message(STATUS "crawlerzoo-bot: building against Qt${QT_VERSION_MAJOR}")

# ------------------------------------------------------------- target ------
add_executable(crawlerzoo-bot
    src/main.cpp
)

target_link_libraries(crawlerzoo-bot
    PRIVATE
        ${QT_CORE}
        ${QT_NETWORK}
)

target_include_directories(crawlerzoo-bot
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(crawlerzoo-bot PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

install(TARGETS crawlerzoo-bot RUNTIME DESTINATION bin)