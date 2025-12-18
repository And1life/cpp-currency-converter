#pragma once

#include <map>
#include <string>
#include <core/Currency.hpp>

class ExchangeRate
{
public:
    
    void addCurrency(const Currency& currency);
    
    double convert(const std::string& from, const std::string& to, double amount) const;

    void updateRate(const std::string& code, double rate);

private:
    
    std::map<std::string, Currency> currencies_;
};
