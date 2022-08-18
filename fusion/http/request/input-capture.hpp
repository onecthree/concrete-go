#pragma once

#include <phpcpp.h>

#include <error/message.hpp>
#include <regex/wrapper/pcre2.hpp>
#include <components/gate/route/provider/smart.hpp>

#include <vector>

class InputCapture : public Php::Base {
    public: void static is_capturable(std::string uri_subject, std::string uri_route) {
        bool is_return = false;

        // no conditional regex
        std::string full_uri = "\\:" +uri_subject+ "";
        regexp::match(full_uri.c_str(), uri_route.c_str(), [&](const char *matched) {
            is_return = true;
        });

        // with conditional regex
        std::string full_uri_regex = "\\:" +uri_subject+ "\\:\\:\\(.*?\\)";
        regexp::match(full_uri_regex.c_str(), uri_route.c_str(), [&](const char *matched) {
            is_return = true;
        });

        if(!is_return)  
            Error::message::captureable_not_found();
    }

    public: Php::Value static parse_input_capturable(std::string uri_subject, std::string uri_route) {
        std::string request_uri = Database::get::string({"FUSION_STORE", "FS_ROUTE", "FS_REQUEST_URI"}); 
        std::vector<std::string> split_request_uri = SmartRouter::uri_route_split(request_uri, false);
        std::vector<std::string> split_uri_route = SmartRouter::uri_route_split(uri_route, false);
        
        Php::Value match_grouping;

        int iterate = 0;

        for(auto &uri_r : split_uri_route) {
            regexp::match("(?<=^\\:)[\\w+_-]*$", uri_r.c_str(), [&](const char * matched) {
                match_grouping[matched] = split_request_uri[iterate];
            });

            regexp::match("(?<=^\\:)[\\w+_-]*(?=\\:\\:\\(.*?\\)$)", uri_r.c_str(), [&](const char * uname) {
                regexp::match("(?<=\\:\\:\\().*?(?=\\))", uri_r.c_str(), [&](const char * matched2) {
                    regexp::match(matched2, split_request_uri[iterate].c_str(), [&](const char * matched3) {
                        match_grouping[uname] = matched3;
                    });
                });
            });

            iterate++;
        }

        return match_grouping;
    }
};