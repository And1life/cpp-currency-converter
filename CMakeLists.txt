cmake_minimum_required(VERSION 3.15)
project(CurrencyConverter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Sources
set(SOURCES
    main.cpp 
    src/core/Currency.cpp 
    src/core/ExchangeRate.cpp 
    src/api/ExchangeApi.cpp
    src/utils/ConfigManager.cpp
    src/gui/mainwindow.cpp
)

# Headers
set(HEADERS
    include/core/Currency.hpp
    include/core/ExchangeRate.hpp
    include/api/ExchangeApi.hpp
    include/utils/ConfigManager.hpp
    include/gui/mainwindow.h
)

# Resources
set(RESOURCES
    config.json
    src/gui/mainwindow.ui
    resources/resources.qrc
)


add_executable(currency_converter
    ${SOURCES}
    ${HEADERS}
    ${RESOURCES}
)

target_include_directories(currency_converter PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
    third_party
)


target_link_libraries(currency_converter PRIVATE
    ${OPENSSL_LIBRARIES}
    Qt6::Core
    Qt6::Widgets
)

add_custom_command(TARGET currency_converter POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/config.json
        $<TARGET_FILE_DIR:currency_converter>/config.json
)


