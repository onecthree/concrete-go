#pragma once

#include <phpcpp.h>

#include <cores/container/container.hpp>
#include <database/core.hpp>
#include <error/message.hpp>
#include <http/request/request.hpp>
#include <regex/route.hpp>
#include <http/request/input-capture.hpp>
#include <components/gate/route/provider/smart.hpp>
#include <cores/container/container.hpp>
#include <views/error/page.hpp>


#include <iostream>

namespace RouteService {
    class web : public Php::Base {
        
        /**
         * @brief       Used for push each routing uri to SESSION "FS_Web_Route_List".
         * @note        SmartRouter::v_double which is will handle for double/twice routing from user script.
         * 
         * @param       uri_route (string) User router address
         * @return      void
         * 
         * @warning     SmartRouter::v_double() => (will throw (PHP) error if conditional meet it)
         */
        public: void static push(std::string uri_route) {
            // Default guard for checking double uri_route if more then one
            SmartRouter::v_double(uri_route);
            // Push uri_route string to SESSION storage
            Database::set::push_array_string({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_List"}, uri_route);
        }

        /**
         * @brief Main method for assign routing to class controller, function callback and the return action
         * @note list of method assign:
         *       1. DI/Dependency Injection to controller class, with return action argument (see sub comment top of method)
         *       2. function callback with injected context/request from Http stuff (see sub comment top of method)
         * 
         * @param uri_route         (std::string) User router address
         * @param handler_opt       (Php::Value) A param for callback or action context
         * @param request_method    (std::string) Request method for parameter action (GET, POST, PUT, etc.)
         * 
         * @return void()       A void return only for blocking return each state conditional (blocking return)
         * 
         */
        public: Php::Value static assign(std::string uri_route, Php::Value handler_opt, std::string request_method) {

            // Php::out << " ini ada router nya bos #KK6 -- " << std::flush;
            /**
             * @note Reserved method for Redirect
             * 
             */
            if(request_method == "REDIRECT") {
                Php::eval("header('Location: " +(std::string)handler_opt+ "');");
                return 0;
            }
            
            Database::set::string({"FUSION_STORE", "FS_ROUTE", "FS_Route_Hitted"}, uri_route);

            /**
             * @note Reserved method for Get, Post, Put, Patch, Delete
             * 
             */
            if(
                request_method == "GET"   || 
                request_method == "POST"  ||
                request_method == "PUT"   ||
                request_method == "PATCH" ||
                request_method == "DELETE" ||
                request_method == "ANY" ||
                request_method == "METHOD"
            ) {

                // 1. Router handler with Dependencies Injection
                if(Php::is_array(handler_opt).boolValue()) {      
                        
                    std::string user_controller_name = handler_opt[0];
                    const char* user_method_name     = handler_opt[1];

                    if(Php::count(handler_opt) < 2)
                        Error::message::handler_opt_empty_args();

                    if(Php::count(handler_opt) > 2)
                        Error::message::handler_opt_many_args();

                    // 1. When __construct exists in user controller class, binding DI to constructor instead user_method_name
                    if(Php::call("method_exists", user_controller_name, "__construct").boolValue()) {
                        // Import default dependencies lib for Dependency Injection
                        std::vector<Php::Value> args = Container::Loader::Method(user_controller_name, "__construct");

                        Php::Value reflect_class = Php::Object("ReflectionClass", user_controller_name);
                        Php::Value class_init = reflect_class.call("newInstanceArgs", args);
                        class_init.call(user_method_name);
                    }

                    // 2. When __construct not exists in user controller class, binding DI to user_method_name
                    if(! (bool)Php::call("method_exists", user_controller_name, "__construct").boolValue()) {

                        std::string user_controller_name = handler_opt[0];
                        const char* user_method_name     = handler_opt[1];

                        // Import default dependencies lib for Dependency Injection
                        std::vector<Php::Value> args = Container::Loader::Method(user_controller_name, user_method_name);

                        Php::Value class_method;
                        class_method[0] = Php::Object(user_controller_name.c_str());
                        class_method[1] = user_method_name;
                        Php::call("call_user_func_array", class_method, args);
                    }

                    return 0;
                }               

                // 2. Router handler with callback action, injected (Object)Request, etc.. as param
                if(Php::call("is_callable", handler_opt).boolValue()) {
                    // Import default dependencies lib for Dependency Injection
                    std::vector<Php::Value> args = Container::Loader::Function(handler_opt);

                    Php::call("call_user_func_array", handler_opt, args);
                    return 0;
                }


            }

            return 0;
        }

        /**
         * @brief flush all session in RouteService such session storage, error handler, and etc.
         * 
         */
        public: void static flush() {
            // flush session storage


            // handle error page/header for incoming http request
            std::string request_method = Database::get::string({"FUSION_STORE", "FS_ROUTE", "REQUEST_METHOD"});


            std::string get_method  = Database::get::string({"FUSION_STORE", "FS_ROUTE", "GET_METHOD", "is_null"});
            std::string post_method = Database::get::string({"FUSION_STORE", "FS_ROUTE", "POST_METHOD", "is_null"});
            std::string put_method = Database::get::string({"FUSION_STORE", "FS_ROUTE", "PUT_METHOD", "is_null"});
            std::string patch_method = Database::get::string({"FUSION_STORE", "FS_ROUTE", "PATCH_METHOD", "is_null"});
            std::string delete_method = Database::get::string({"FUSION_STORE", "FS_ROUTE", "DELETE_METHOD", "is_null"});

            if(get_method == "true" && request_method == "GET")         error_page::Get::code_404();    
            if(post_method == "true" && request_method == "POST")       error_page::Post::code_404();   
            if(post_method == "true" && request_method == "HEAD")       error_page::Post::code_404();   
            if(put_method == "true" && request_method == "PUT")         error_page::Put::code_404();   
            if(patch_method == "true" && request_method == "PATCH")     error_page::Patch::code_404();   
            if(delete_method == "true" && request_method == "DELETE")   error_page::Delete::code_404();    
            if(delete_method == "true" && request_method == "OPTIONS")   error_page::Delete::code_404();    
        }

        /**
         * @brief Reset the SESSION "FS_Web_Route_List" to the empty array
         * 
         * @return void()
         */
        public: void static reset_route_list() {
            Database::set::empty_array({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_List"});
        }

    };
}