#pragma once

#include "core/ExchangeRate.hpp"
#include "utils/ConfigManager.hpp"
#include <string>

class ExchangeApi
{
public:

    ExchangeApi(ExchangeRate& exchangeRate, const ConfigManager& configManager);

    void fetchRates();

private:
    
    ExchangeRate& exchangeRate_;
    const ApiConfig& apiConfig_;
};
