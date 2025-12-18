cmake_minimum_required(VERSION 3.15)
project(CurrencyConverter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})



add_executable(currency_converter
    main.cpp 
    src/core/Currency.cpp 
    src/core/ExchangeRate.cpp 
    src/api/ExchangeApi.cpp
)

target_link_libraries(currency_converter ${OPENSSL_LIBRARIES})
target_include_directories(currency_converter PUBLIC 
    include
    third_party
)




