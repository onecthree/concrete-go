#pragma once

#include <phpcpp.h>
#include <database/core.hpp>
#include <cores/autoload/autoload.hpp>
#include <error/message.hpp>
#include <constructor/constructor.hpp>
#include <destructor/destructor.hpp>

#include <iostream>
#include <sstream>

class Engine : public Php::Base {
    public: Engine() {
        Construct::framework();
    } 

    public: virtual ~Engine() {}

    public: void static Framework(Php::Parameters &param) {
        Construct::framework_init(param);
        Construct::route_init();
    }

    public: void static Run() {
        Engine __construct;
        
        Destruct::route_init();
        Destruct::session_reset();
    }

};