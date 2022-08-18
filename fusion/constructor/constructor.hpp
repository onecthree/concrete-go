#pragma once

#include <phpcpp.h>
#include <database/core.hpp>
#include <error/message.hpp>
#include <regex/route.hpp>
#include <components/gate/route/provider/smart.hpp>

#include <iostream>

namespace Construct {
    void framework() {
        std::string FS_FRAMEWORK_MODE = Database::get::string({"FUSION_STORE", "FS_FRAMEWORK_MODE"});   
        if(!Database::isset::string(FS_FRAMEWORK_MODE)) {
            Error::message::empty_framework_mode();
        }
    }

    void framework_init(Php::Parameters &param) {
        if(Php::count(param) < 1) {
            Error::message::empty_framework_mode();
        }
        
        Php::Value FUSION_DB;
        FUSION_DB["FS_FRAMEWORK_MODE"] = param[0];

        Database::set::array({"FUSION_STORE"}, FUSION_DB);

        Database::set::empty_array({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_List"});
        Database::set::empty_array({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_Req_Uri_Split"});
    }
    
    void route_init() {
        std::string request_uri = Php::eval("return $_SERVER['REQUEST_URI'];").stringValue();       

        std::string escape_request_uri = Regex::uri::escape_request_uri(request_uri);
        Database::set::string({"FUSION_STORE", "FS_ROUTE", "FS_REQUEST_URI"}, escape_request_uri); 

        Database::set::string({"FUSION_STORE", "FS_ROUTE", "REQUEST_METHOD"}, Php::eval("return $_SERVER['REQUEST_METHOD'];").stringValue());

        Database::set::string({"FUSION_STORE", "FS_ROUTE", "GET_METHOD", "is_null"}, "true");
        Database::set::string({"FUSION_STORE", "FS_ROUTE", "POST_METHOD", "is_null"}, "true");
        Database::set::string({"FUSION_STORE", "FS_ROUTE", "HEAD_METHOD", "is_null"}, "true");
        Database::set::string({"FUSION_STORE", "FS_ROUTE", "PUT_METHOD", "is_null"}, "true");
        Database::set::string({"FUSION_STORE", "FS_ROUTE", "PATCH_METHOD", "is_null"}, "true");
        Database::set::string({"FUSION_STORE", "FS_ROUTE", "DELETE_METHOD", "is_null"}, "true");
        Database::set::string({"FUSION_STORE", "FS_ROUTE", "OPTIONS_METHOD", "is_null"}, "true");


        Database::set::boolean({"FUSION_STORE", "FS_ROUTE", "FS_Route_V_Double"}, true);

        Database::set::empty_array({"FUSION_STORE", "FS_ROUTE", "FS_Uri_Route_Char_Count"});    

        Php::Value request_uri_split = SmartRouter::uri_route_split(escape_request_uri, false);
        Database::set::push_array_array({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_Req_Uri_Split"}, request_uri_split);
    }
}