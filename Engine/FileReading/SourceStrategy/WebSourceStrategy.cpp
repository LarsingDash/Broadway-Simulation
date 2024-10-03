//
// Created by larsv on 03/10/2024.
//

#include "WebSourceStrategy.hpp"
#include <sstream>

CURL* WebSourceStrategy::curl = nullptr;
bool WebSourceStrategy::isCurlInit = false;

std::unique_ptr<Source> WebSourceStrategy::fetchSource(const std::string& path) {
	if (initCurl()) {
		
	}
	
	return std::make_unique<Source>(Source{{"WebTest"}, "web"});
}

bool WebSourceStrategy::initCurl() {
	if (isCurlInit) return true;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	
	if (!curl) return false;

	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlCallback);
	return true;
}

size_t WebSourceStrategy::curlCallback(void* contents, size_t size, size_t nmemb, std::stringstream* output) {
	size_t totalSize = size * nmemb;
	output->write(static_cast<const char*>(contents), totalSize);
	return totalSize;
}
