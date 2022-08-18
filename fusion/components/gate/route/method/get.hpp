#pragma once

#include <phpcpp.h>

#include <constructor/constructor.hpp>
#include <components/gate/route/provider/service.hpp>
#include <components/gate/route/provider/smart.hpp>
#include <database/core.hpp>
#include <regex/route.hpp>
#include <iostream>

class RouteGet : public Php::Base {

    // constructor
    public: RouteGet(Php::Parameters &param) {
        if(Php::count(param) < 2) 
            Error::message::empty_route_get_param();

        if(Php::count(param) > 2)
            Error::message::many_route_get_param();

        std::string request_method = Database::get::string({"FUSION_STORE", "FS_ROUTE", "REQUEST_METHOD"});

        if(request_method == "GET") {
            Php::Value uri_route   = param[0];
            Php::Value handler_opt  = param[1];

            if(Php::is_array(uri_route).boolValue()) {
                for(auto &uri_each : uri_route) {
                    assign_to_route_service((std::string)uri_each.second, handler_opt);
                }
            } else {
                assign_to_route_service(uri_route, handler_opt);
            }
        }
    }   

    public: void assign_to_route_service(std::string uri_router, Php::Value handler_opt) {
        std::string escape_uri_route = Regex::uri::escape_request_uri(uri_router + "/");

        RouteService::web::push(escape_uri_route);

        SmartRouter::catch_uri_parse(escape_uri_route);                    
        
        if(!Database::get::boolean({"FUSION_STORE", "FS_ROUTE", "FS_Route_V_Double"})) {
            std::string request_uri = Database::get::string({"FUSION_STORE", "FS_ROUTE", "FS_REQUEST_URI"});

            //The gate for check if current $_SERVER["REQUEST_URI"] request same as user route address
            if(SmartRouter::handle_input_uri_guard(escape_uri_route) || uri_router == request_uri) {
                // Change GET_METHOD parameter to "true" for tell to Router Service, if routing request method given
                Database::set::string({"FUSION_STORE", "FS_ROUTE", "GET_METHOD", "is_null"}, "false");

                // Assign request context to Router Services
                RouteService::web::assign(escape_uri_route, handler_opt, "GET");
            }
        }
    }
};