#define CPPHTTPLIB_OPENSSL_SUPPORT

#include "api/ExchangeApi.hpp"
#include "httplib.h"
#include "json.hpp"
#include <iostream>

ExchangeApi::ExchangeApi(ExchangeRate &exchangeRate)
    : exchangeRate_(exchangeRate) {}

void ExchangeApi::fetchRates()
{
    httplib::SSLClient client("api.currencyfreaks.com");
    client.set_connection_timeout(10, 0);
    client.set_read_timeout(10, 0);

    std::string path = "/v2.0/rates/latest?apikey=1ffde2285229404781abc504c47fd661";
    auto res = client.Get(path.c_str());

    if (res && res->status == 200)
    {
        try
        {
            auto json = nlohmann::json::parse(res->body);

            for (auto& [code, rateValue] : json["rates"].items())
            {
                double rate = rateValue.is_number() ?
                rateValue.get<double>() :
                std::stod(rateValue.get<std::string>());

                exchangeRate_.updateRate(code, rate);
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    } else
    {
        std::cerr << "Failed to fetch rates from API. Status: "
                  << (res ? res->status : -1) << std::endl;
    }
}