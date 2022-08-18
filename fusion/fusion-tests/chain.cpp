

#include <iostream>

class foo {
    public: foo* bar() {
        std::cout << "ini bar" << std::endl;
        
        return this;
    }

    public: foo* foobar() {
        std::cout << "ini foobar" << std::endl;

        return this;
    }
};

int main() {
    foo *Onec = new foo;
    Onec->bar()->foobar();
    return 0;
}