#include <iostream>
#include "core/Currency.hpp"

int main(int argc, char const *argv[])
{
    Currency currency("USD", "Usd dollar", 1.0);
    std::cout << "Code: " << currency.getCode() << std::endl;
    std::cout << "Name: " << currency.getName() << std::endl;
    std::cout << "Rate: " << currency.getRate() << std::endl;

    return 0;
}
