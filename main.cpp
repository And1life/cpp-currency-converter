#include <iostream>
#include "core/Currency.hpp"
#include "core/ExchangeRate.hpp"
#include "api/ExchangeApi.hpp"

int main(int argc, char const *argv[])
{
    ExchangeRate exchangeRate;

    exchangeRate.addCurrency(Currency("USD", "US Dollar", 1.0));
    exchangeRate.addCurrency(Currency("EUR", "Euro", 0.85));

    ExchangeApi api(exchangeRate);

    
    api.fetchRates();

    try
    {
        double result = exchangeRate.convert("USD", "EUR", 100.0);
        std::cout << "100 USD = " << result << " EUR" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }

    
    return 0;
}
