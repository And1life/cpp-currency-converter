#include "ConfigManager.hpp"
#include <fstream>
#include <iostream>

ConfigManager::ConfigManager(const std::string &configPath)
{
    loadConfig(configPath);
}

const ApiConfig &ConfigManager::getApiConfig() const
{
    return apiConfig_;
}

const std::vector<CurrencyConfig> &ConfigManager::getCurrencies() const
{
    return currencies_;
}
