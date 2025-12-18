#include "ConfigManager.hpp"
#include <fstream>
#include <iostream>

ConfigManager::ConfigManager(const std::string &configPath)
{
    loadConfig(configPath);
}
