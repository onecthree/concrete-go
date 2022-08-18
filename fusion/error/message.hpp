#pragma once

#include <phpcpp.h>

#include <iostream>


std::string cout(std::string messages) {
    return "<b>Fatal error:</b> FusionEngine: " +messages+ " {main:0} throw in <b id='fc'></b> on line <b id='lc'></b><br/><script>function z(x){return document.getElementById(x);}window.onload=function(){let b=z('el').innerHTML;let x=b.match(/(?<=\\<b\\>)\\/(.*?)(?=\\<\\/b\\>)|(?<=line <b>)(.*?)(?=\\<\\/b\\>)/g);z('fc').innerHTML=x[0];z('lc').innerHTML=x[1]; document.getElementById('el').style.display = 'none';}</script><div id='el'>";
}

namespace Error {
    class message {
        private: void static error(std::string value) {
            std::string error_message = cout(value);
            Php::out << error_message << std::flush;
            Php::error << "" << std::flush;
        }
        
        public: void static empty_framework_mode() {
            std::string error_message = cout("'Fusion/Cores/Engine::Framework()' not declared");
            Php::out << error_message << std::flush;
            Php::error << "" << std::flush;
        }
        
        public: void static empty_autoload_config_param() {
            std::string error_message = cout("'Fusion/Cores/Autoload::Config()' need more arguments");
            Php::out << error_message << std::flush;
            Php::error << "" << std::flush;
        }

        public: void static many_autoload_config_param() {
            std::string error_message = cout("'Fusion/Cores/Autoload::Config()' too much arguments");
            Php::out << error_message << std::flush;
            Php::error << "" << std::flush;
        }

        public: void static empty_route_get_param() {
            std::string error_message = cout("'Fusion/Controllers/Route::Get()' need more arguments");
            Php::out << error_message << std::flush;
            Php::error << "" << std::flush;
        }
        public: void static many_route_get_param() {
            std::string error_message = cout("'Fusion/Controllers/Route::Get()' too much arguments");
            Php::out << error_message << std::flush;
            Php::error << "" << std::flush;
        }



        public: void static untype_route_redirect_param(std::string uri_type) {
            std::string error_message = cout("'Fusion/Controllers/Route::Redirect()' parameter 2 type is a string. " +uri_type+ " given.");
            Php::out << error_message << std::flush;
            Php::error << "" << std::flush;
        }



        public: void static handler_opt_empty_args() {
            std::string error_message = cout("'Fusion/Controllers/Route::Get()' second parameter need more context");
            Php::out << error_message << std::flush;
            Php::error << "" << std::flush;
        }

        public: void static handler_opt_many_args() {
            std::string error_message = cout("'Fusion/Controllers/Route::Get()' second parameter too much context");
            Php::out << error_message << std::flush;
            Php::error << "" << std::flush;
        }

        public: void static uncapturable_uri_input() {
            std::string error_message = cout("'Fusion/Http/Request->input()' the url doesnt support input method");
            Php::out << error_message << std::flush;
            Php::error << "" << std::flush;
        }


        public: int static captureable_not_found() {
            std::string error_message = cout("'Fusion/Http/Request->input()' cant found the uri input");
            Php::out << error_message << std::flush;
            Php::error << "" << std::flush;
            return 0;
        }

        public: int static method_route_not_post() {
            std::string error_message = cout("method route not post");
            Php::out << error_message << std::flush;
            Php::error << "" << std::flush;
            return 0;
        }

        public: int static method_route_not_get() {
            std::string error_message = cout("method route not get");
            Php::out << error_message << std::flush;
            Php::error << "" << std::flush;
            return 0;
        }
        
        public: void static v_double_uri() {
            error("'v_double_uri' detected");
        }

        public: void static match_uri_identics() {
            error("'match_uri_identics' detected");
        }


        public: void static constra_too_much_arguments() {
            error("too much arguments for Constra");
        }
    };
}