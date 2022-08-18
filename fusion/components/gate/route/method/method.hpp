#pragma once

#include <phpcpp.h>

#include <constructor/constructor.hpp>
#include <components/gate/route/provider/service.hpp>
#include <components/gate/route/provider/smart.hpp>
#include <database/core.hpp>
#include <regex/route.hpp>
#include <iostream>

#include <algorithm>
#include <string>
#include <vector>
#include <functional>


class RouteMethod : public Php::Base {

    // constructor
    public: RouteMethod(Php::Parameters &param) {
        if(Php::count(param) < 3) 
            Error::message::empty_route_get_param();

        if(Php::count(param) > 3)
            Error::message::many_route_get_param();

        std::string request_method = Database::get::string({"FUSION_STORE", "FS_ROUTE", "REQUEST_METHOD"});

        bool is_method_valid = false;
        for(auto &each_method : (Php::Value)param[0]) {
            
            //
            std::string method_temp = (const char *) each_method.second;
            std::transform(method_temp.begin(), method_temp.end(), method_temp.begin(), ::toupper);

            // 
            if(request_method == method_temp) {
                // Override request method in database, for trigger the actually requested method
                override_request_method(request_method);
                
                // Set is_method_valid to true for change the conditional
                is_method_valid = true;
                
                // Break the loop process
                break;
            }
        }

        if(is_method_valid) {
            std::string uri_route   = param[1];
            Php::Value handler_opt  = param[2];

            std::string escape_uri_route = Regex::uri::escape_request_uri(uri_route + "/");

            RouteService::web::push(escape_uri_route);
            SmartRouter::catch_uri_parse(escape_uri_route);

            if(!Database::get::boolean({"FUSION_STORE", "FS_ROUTE", "FS_Route_V_Double"})) {
                std::string request_uri = Database::get::string({"FUSION_STORE", "FS_ROUTE", "FS_REQUEST_URI"});

                if(SmartRouter::handle_input_uri_guard(escape_uri_route) || uri_route == request_uri) {
                    // Assign request context to Router Services
                    RouteService::web::assign(escape_uri_route, handler_opt, "METHOD");
                }
            }
        }
    }

    public: void override_request_method(std::string REQUEST_METHOD) {
        Database::set::string({"FUSION_STORE", "FS_ROUTE", REQUEST_METHOD+ "_METHOD", "is_null"}, "false");
    }

};