cmake_minimum_required(VERSION 3.15)
project(CurrencyConverter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt 6 REQUIRED COMPONENTS Widgets)

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

# Sources
set(SOURSES
    main.cpp 
    src/core/Currency.cpp 
    src/core/ExchangeRate.cpp 
    src/api/ExchangeApi.cpp
    src/utils/ConfigManager.cpp
)

# Headers
set(HEADER
    core/Currensy.hpp
    core/ExchangeRate.hpp
    api/ExchangeApi.hpp
    ConfigManager.hpp
)

add_executable(currency_converter ${SOURCES} ${HEADERS})

target_link_libraries(currency_converter Qt6::Widgets ${OPENSSL_LIBRARIES})
target_include_directories(currency_converter PUBLIC 
    include
    third_party
)




