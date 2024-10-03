//
// Created by larsv on 03/10/2024.
//

#include "WebSourceStrategy.hpp"

std::unique_ptr<Source> WebSourceStrategy::fetchSource(const std::string& path) {
	return std::make_unique<Source>(Source{{"WebTest"}, "web"});
}
