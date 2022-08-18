#include <iostream>
#include <fstream>

int main() {
        std::string render_resource = "ahello all";

        std::ofstream constra_cache("./holla.txt");
        constra_cache << render_resource << std::endl;
        constra_cache.close();

    return 0;
}