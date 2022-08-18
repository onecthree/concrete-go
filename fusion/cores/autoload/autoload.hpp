#pragma once

#include <phpcpp.h>

#include <error/message.hpp>
#include <cores/autoload/loader.hpp>
#include <constructor/constructor.hpp>

class Autoload : public Php::Base {
    public: Php::Value static Config(Php::Parameters &param) {
        Construct::framework();

        if(Php::count(param) < 1)
            Error::message::empty_autoload_config_param();
        if(Php::count(param) > 1)
            Error::message::many_autoload_config_param();

        
        std::string autoload_config_mode = param[0];
         if(autoload_config_mode == "FS_DEFAULT") {
            loader::_default();          
            return 0;
        }

        if(autoload_config_mode == "FS_COMPACT") {
            Php::out << "autoload_compact" << std::flush;
            return 0;
        }

        return 0;
    }  

    public: void static Register() {
        // Register the config as startup used for require_src
        loader::boot();
    }
    
};