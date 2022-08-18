#pragma once

#include <phpcpp.h>

#include <regex/wrapper/pcre2.hpp>

#include <regex>


namespace Regex {
    class uri : public Php::Base {
        public: std::string static escape_request_uri(std::string uri_route) {
            std::string filtered_result = uri_route + "/";

            regexp::replace("(\\?.*)$", filtered_result.c_str(), "/", [&](const char *replaced) {
                filtered_result = (std::string)replaced;
            });

            regexp::replace("\\/\\/*\\/", filtered_result.c_str(), "/", [&](const char *replaced) {
                filtered_result = (std::string)replaced;
            });
            
            regexp::replace("\\\\", filtered_result.c_str(), "$fs_bs$", [&](const char *replaced) {
                filtered_result = (std::string)replaced;
            });
            
            // Php::out << filtered_result << "<br />" << std::flush;
            // std::string escape_backslash_uri = std::regex_replace(uri_route, std::regex("\\/\\/*\\/"), "/");
            // std::string uri_route_filtered = std::regex_replace(escape_backslash_uri, std::regex("\\\\"), "$fs_bs$");

            return filtered_result;
        }
    };
}