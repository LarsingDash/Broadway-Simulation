//
// Created by larsv on 03/10/2024.
//

#ifndef BROADWAY_SIMULATION_WEBSOURCESTRATEGY_HPP
#define BROADWAY_SIMULATION_WEBSOURCESTRATEGY_HPP

#include "ISourceStrategy.hpp"
#include <curl/curl.h>

class WebSourceStrategy : public ISourceStrategy {
	public:
		std::unique_ptr<Source> fetchSource(const std::string& pathOrURL) override;
		static void cleanup();
	private:
		static CURL* curl;
		static bool isCurlInit;
		static bool initCurl();
		static size_t curlCallback(void* contents, size_t stride, size_t count, std::stringstream* output);
};

#endif //BROADWAY_SIMULATION_WEBSOURCESTRATEGY_HPP
