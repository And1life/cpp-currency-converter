#pragma once

#include "core/ExchangeRate.hpp"
#include <string>

class ExchangeApi
{
public:

    ExchangeApi(ExchangeRate& exchangeRate);

    void fetchRates();

private:
    
    ExchangeRate& exchangeRate_;
};
