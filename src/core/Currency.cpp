#include "Currency.hpp"

Currency::Currency(const std::string &code, const std::string &name, double rate) 
    : code_(code), name_(name), rate_(rate) {}