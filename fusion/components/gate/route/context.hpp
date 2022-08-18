#pragma once

#include <phpcpp.h>

#include <iostream>

class RouteContext : public Php::Base {
    public: void code_501() {
        Php::out << "Error: 501" << std::flush;
    }
};