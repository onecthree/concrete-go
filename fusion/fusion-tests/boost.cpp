
#include <iostream>
#include <boost/bind.hpp>

#define BUILD0(x) x[0]
#define BUILD1(x) BUILD0(x), x[1]
#define BUILD2(x) BUILD1(x), x[2]
#define BUILD3(x) BUILD2(x), x[3]
#define BUILD4(x) BUILD3(x), x[4]
#define BUILD5(x) BUILD4(x), x[5]
#define BUILD(x, i) BUILD##i(x)


void foo(int i) {std::cout << i << std::endl;}
void foo(int i, int j) {std::cout << j << std::endl;}
void foo(int i, int j, int k) {std::cout << k << std::endl;}
void foo(int i, int j, int k, int l, int o, int z) {
    std::cout << z << std::endl;
}

int main() {
    int x[] = {1, 2, 3, 4, 5, 6};
    boost::bind(foo, BUILD(x, 5))();
}
