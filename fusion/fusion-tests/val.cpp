
#include <iostream>

template <typename Ta> Ta Max (Ta a, Ta b) { 
   return a < b ? b : a; 
}

template <typename ...Param> void function(Param&&... numb) {
    ((std::cout << numb << std::endl), ...);
}

template<typename T>
struct Convert {
    auto operator()(T*) -> T {
        return T{};
    }
};

template <typename ...Ta> void Max (Ta&&... args) { 
    int gg[3] = { 1, 2, 3 };
    // return function(Convert<Ta>{}(gg[3])...);
    function(gg);
}

int main() {
    Max(1, 2 ,3);
    return 0;
}