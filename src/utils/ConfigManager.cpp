#include "utils/ConfigManager.hpp"
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


void ConfigManager::loadConfig(const std::string &configPath)
{
    std::fstream configFile(configPath);

    if (!configFile.is_open())
    {
        throw std::runtime_error("Failed to open file: " + configPath);
    }
    
    nlohmann::json configJson;

    try
    {
        configFile >> configJson;
    }
    catch(const std::exception& e)
    {
        throw std::runtime_error("Failed to parse config file: " + std::string(e.what()));
    }
    
    if (configJson.contains("api"))
    {
        if (!configJson["api"].contains("url") || configJson["api"]["url"].is_null())
        {
            throw std::runtime_error("API URL is missing or null");
        }
        if (!configJson["api"].contains("endpoint") || configJson["api"]["endpoint"].is_null())
        {
            throw std::runtime_error("API endpoint is missing or null");
        }
        if (!configJson["api"].contains("apiKey") || configJson["api"]["apiKey"].is_null())
        {
            throw std::runtime_error("API apikey is missing or null");
        }

        apiConfig_.url = configJson["api"]["url"];
        apiConfig_.endpoint = configJson["api"]["endpoint"];
        apiConfig_.apiKey = configJson["api"]["apiKey"];
    } else {
        throw std::runtime_error("Config file does not contain 'api' section");
    }

    if (configJson.contains("currencies"))
    {
        for (const auto& currencyJson : configJson["currencies"])
        {
            CurrencyConfig currency;
            currency.code = currencyJson["code"];
            currency.name = currencyJson["name"];
            currency.rate = currencyJson["rate"];
            currencies_.push_back(currency);
        }
    } else {
        throw std::runtime_error("Config file does not contain 'currencies' section");
    }
}
