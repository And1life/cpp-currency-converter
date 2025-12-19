#include "core/ExchangeRate.hpp"
#include <stdexcept>

ExchangeRate::ExchangeRate(const ConfigManager& configManager)
{
    for (const auto& currencyConfig : configManager.getCurrencies())
    {
        addCurrency(Currency(currencyConfig.code, currencyConfig.name, currencyConfig.rate));
    }
}

void ExchangeRate::addCurrency(const Currency &currency)
{
    currencies_[currency.getCode()] = currency;

}
double ExchangeRate::convert(const std::string &from, const std::string &to, double amount) const
{
    if (currencies_.find(from) == currencies_.end() || currencies_.find(to) == currencies_.end())
    {
        throw std::runtime_error("Currency not found.");
    }

    double fromRate = currencies_.at(from).getRate();
    double toRate = currencies_.at(to).getRate();

    return amount * (toRate / fromRate);
}

void ExchangeRate::updateRate(const std::string &code, double rate)
{
    if (currencies_.find(code) != currencies_.end())
    {
        currencies_[code].setRate(rate);
    }
}