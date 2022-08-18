#pragma once

#include <phpcpp.h>

#include <constructor/constructor.hpp>
#include <components/gate/route/provider/service.hpp>
#include <components/gate/route/provider/smart.hpp>
#include <database/core.hpp>
#include <regex/route.hpp>
#include <iostream>

class RouteOptions : public Php::Base {

    // constructor
    public: RouteOptions(Php::Parameters &param) {
        if(Php::count(param) < 2) 
            Error::message::empty_route_get_param();

        if(Php::count(param) > 2)
            Error::message::many_route_get_param();

        std::string request_method = Database::get::string({"FUSION_STORE", "FS_ROUTE", "REQUEST_METHOD"});

        if(request_method == "OPTIONS") {
            std::string uri_route   = param[0];
            Php::Value handler_opt  = param[1];

            std::string escape_uri_route = Regex::uri::escape_request_uri(uri_route + "/");

            RouteService::web::push(escape_uri_route);
            SmartRouter::catch_uri_parse(escape_uri_route);

            if(!Database::get::boolean({"FUSION_STORE", "FS_ROUTE", "FS_Route_V_Double"})) {
                std::string request_uri = Database::get::string({"FUSION_STORE", "FS_ROUTE", "FS_REQUEST_URI"});

                if(SmartRouter::handle_input_uri_guard(escape_uri_route) || uri_route == request_uri) {
                    // Change PUT_METHOD parameter to "true" for tell to Router Service, if routing request method given
                    Database::set::string({"FUSION_STORE", "FS_ROUTE", "OPTIONS_METHOD", "is_null"}, "false");

                    // Assign request context to Router Services
                    RouteService::web::assign(escape_uri_route, handler_opt, "OPTIONS");
                }
            }
        }
    }
    
};