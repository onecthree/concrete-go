
#include <iostream>
#include <vector>

int main() {
    std::string uri_route = "/test/";

    uri_route = uri_route.substr(1, uri_route.length() - 2);


    std::cout << uri_route << std::endl;

    return 0;
}