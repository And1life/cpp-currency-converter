#pragma once

#include <string>
#include <vector>
#include "json.hpp"

struct ApiConfig
{
    std::string url;
    std::string endpoint;
    std::string apiKey;
};

struct CurrencyConfig
{
    std::string code;
    std::string name;
    double rate;
};

class ConfigManager
{
public:

    ConfigManager(const std::string& configPath);

    const ApiConfig& getApiConfig() const;

    const std::vector<CurrencyConfig>& getCurrencies() const;

private:

    void loadConfig(const std::string& configPath);

    ApiConfig apiConfig_;

    std::vector<CurrencyConfig> currencies_;
};
