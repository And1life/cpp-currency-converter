#include <iostream>
#include "core/ExchangeRate.hpp"
#include "api/ExchangeApi.hpp"
#include "utils/ConfigManager.hpp"

int main(int argc, char const *argv[])
{
    try
    {
        ConfigManager configManager("config.json");

        ExchangeRate exchangeRate(configManager);

        ExchangeApi api(exchangeRate, configManager);
        api.fetchRates();

        double result = exchangeRate.convert("USD", "EUR", 100.0);
        std::cout << "100 USD = " << result << " EUR" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    
    return 0;
}
