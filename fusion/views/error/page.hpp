#pragma once

#include <phpcpp.h>

#include <iostream>

namespace error_page {
    class Get {
        public: void static code_404() {
            Php::out << "404: Not Found (GET)" << std::flush;
        }
    };

    class Post {
        public: void static code_404() {
            Php::out << "404: Not Found (POST)" << std::flush;
        }
    };

    class Put {
        public: void static code_404() {
            Php::out << "404: Not Found (PUT)" << std::flush;
        }
    };

    class Patch {
        public: void static code_404() {
            Php::out << "404: Not Found (PATCH)" << std::flush;
        }
    };

    class Delete {
        public: void static code_404() {
            Php::out << "404: Not Found (DELETE)" << std::flush;
        }
    };
}