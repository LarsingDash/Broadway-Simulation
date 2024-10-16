//
// Created by larsv on 03/10/2024.
//

#ifndef BROADWAY_SIMULATION_WEBSOURCESTRATEGY_HPP
#define BROADWAY_SIMULATION_WEBSOURCESTRATEGY_HPP

#include "ISourceStrategy.hpp"
#include <curl/curl.h>

class WebSourceStrategy : public ISourceStrategy {
	public:
		bool fetchSource(const std::string& pathOrURL, std::vector<std::string>& data) override;
		static void cleanup();
	private:
		static CURL* curl;
		static bool isCurlInit;
		static bool initCurl();
		static size_t curlCallback(void* contents, size_t stride, size_t count, std::stringstream* output);
		static void _trim(std::string& line);
};

#endif //BROADWAY_SIMULATION_WEBSOURCESTRATEGY_HPP
