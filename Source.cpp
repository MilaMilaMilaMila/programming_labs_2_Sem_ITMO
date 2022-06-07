#include <iostream>
#include <nlohmann/json.hpp>
#define CURL_STATICLIB
#include <curl/curl.h>
#include <string>
#include <vector>
#include <io.h>
#include <fcntl.h>
#include <fstream>
#include "currency.h"
#include <windows.h>
#include <conio.h>


using json = nlohmann::json;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

std::string getJson()
{
	curl_global_init(CURL_GLOBAL_ALL);
	std::string data;
	CURL* curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, "https://www.cbr-xml-daily.ru/daily_json.js");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
		CURLcode res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}

	return data;
}

void parseJson(std::vector<Currency>& currencyArray)
{
	std::string data = getJson();
	json allData = json::parse(data);

	int currencyAmount = currencyArray.size();
	for (int i = 0; i < currencyAmount; i++)
	{
		currencyArray[i].value = allData["Valute"][currencyArray[i].charCode]["Value"].get<double>();
		currencyArray[i].updateValues();
	}

}

void buildClass(std::vector<Currency>& currencyArray)
{
	auto data = getJson();
	json allData = json::parse(data);
	std::vector<std::string> currencyNames;
	for (json::iterator it = allData["Valute"].begin(); it != allData["Valute"].end(); ++it) {
		currencyNames.push_back(it.key());
	}
	
	int currencyAmount = currencyNames.size();
	currencyArray.resize(currencyAmount);
	for (int i = 0; i < currencyAmount; i++)
	{
		currencyArray[i].charCode = currencyNames[i];
		currencyArray[i].value = allData["Valute"][currencyNames[i]]["Value"].get<double>();
		currencyArray[i].updateValues();
	}
}

int main()
{
	std::vector<Currency> currencyArray;
	buildClass(currencyArray);

	while (!_kbhit())
	{
		parseJson(currencyArray);
		std::cout << "New request" << std::endl;
		for (auto currency : currencyArray)
		{
			std::cout << currency;
		}

		Sleep(3000);
	}

	for (auto currency : currencyArray)
	{
		std::cout << currency.charCode << " : middle value " << currency.middleValue() << " median value" << currency.medianValue() << std::endl;
	}

	return 0;
}