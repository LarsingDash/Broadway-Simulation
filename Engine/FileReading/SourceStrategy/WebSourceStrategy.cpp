//
// Created by larsv on 03/10/2024.
//

#include "WebSourceStrategy.hpp"
#include <sstream>
#include <iostream>

//Static members
CURL* WebSourceStrategy::curl = nullptr;
bool WebSourceStrategy::isCurlInit = false;

std::unique_ptr<Source> WebSourceStrategy::fetchSource(const std::string& pathOrURL) {
	//Init curl
	if (!initCurl()) {
		std::cerr << "Could not init curl" << std::endl;
		return nullptr;
	}

	//Prepare for request
	std::stringstream output;
	CURLcode res;

	//Settings
	curl_easy_setopt(curl, CURLOPT_URL, pathOrURL.c_str());    //URL
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &output);        //Output

	//Perform request
	res = curl_easy_perform(curl);

	//Check result
	if (res != CURLE_OK) {
		std::cerr << "Result failed with errorCode: " << res << std::endl;
		return nullptr;
	}

	//Prepare Source
	std::unique_ptr<Source> source = std::make_unique<Source>();

	//Get file extension
	size_t pos = pathOrURL.find_last_of('.');
	if (pos != std::string::npos) {
		source->extension = pathOrURL.substr(pos + 1);
	}

	//Break output into lines and stream to Source->data
	std::string line;
	std::istringstream outputStream(output.str());
	while (std::getline(outputStream, line))
		source->data.push_back(line);

	//Return
	return source;
}

bool WebSourceStrategy::initCurl() {
	//Check if curl is already init
	if (isCurlInit) return true;
	isCurlInit = true;

	//Initiate curl
	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	//Check if init was successfull
	if (!curl) return false;

	//Settings
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlCallback);	//Callback
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);				//Allowed to follow redirects (on)
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);				//SSL verify peers (off)
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);				//SSL verify hosts (off)
	
	return true;
}

size_t WebSourceStrategy::curlCallback(void* contents, size_t stride, size_t count, std::stringstream* output) {
	//Total size = stride width * count of items
	size_t totalSize = stride * count;
	
	//Write everything from contents to output stream
	output->write(static_cast<const char*>(contents), static_cast<std::streamsize>(totalSize));
	return totalSize;
}

void WebSourceStrategy::cleanup() {
	//If curl is init
	if (!isCurlInit) return;

	//Cleanup
	curl_easy_cleanup(curl);
	curl_global_cleanup();
}