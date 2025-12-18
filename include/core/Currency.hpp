#pragma once
#include <string>

class Currency
{

public:

    Currency(const std::string& code, const std::string& name, double rate);

    std::string getCode() const;
    std::string getName() const;
    double getRate() const;
    void setRate(double rate);

private:

    std::string code_;
    std::string name_;
    double rate_;
};
