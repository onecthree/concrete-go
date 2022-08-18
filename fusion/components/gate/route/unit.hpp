#pragma once

#include <phpcpp.h>
#include <iostream>

namespace unit {
    class foo : public Php::Base {
        public: foo() {
            Php::out << "ini foo" << "<br />" << std::flush;
        }


        public: void static foo_u() {
            Php::out << "ini foo" << "<br />" << std::flush;
        }
    };

    class bar : public Php::Base {
        public: bar() {
            Php::out << "ini bar" << "<br />" << std::flush;
        }

        public: void static bar_u() {
            Php::out << "ini bar" << "<br />" << std::flush;
        }
    };
}