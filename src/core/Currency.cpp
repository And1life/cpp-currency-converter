#include "Currency.hpp"

Currency::Currency(const std::string &code, const std::string &name, double rate) 
    : code_(code), name_(name), rate_(rate) {}

std::string Currency::getCode() const
{
    return code_;
}

std::string Currency::getName() const
{
    return name_;
}

double Currency::getRate() const
{
    return rate_;
}

void Currency::setRate(double rate)
{
    rate_ = rate;
}
