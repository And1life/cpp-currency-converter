#include "core/ExchangeRate.hpp"
#include <stdexcept>

void ExchangeRate::addCurrency(const Currency &currency)
{
    currencies_[currency.getCode()] = currency;
}