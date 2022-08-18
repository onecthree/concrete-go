#pragma once

#include <phpcpp.h>

class Controller : public Php::Base {
    public: Php::Value static Class() {
        return Php::call("get_called_class");
    }
};