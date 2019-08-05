////////////////////////////////////////////////////////////////////
// File:         simple.cpp
// Creation:     4/2013
// Programmer:   Dr. J. Maletic
//
// Description:  Simple program for testing profiler
//
//
#include <iostream>

#include "profile.hpp";
extern profilesimple_cpp;

int search(int tbl[], int n, int key) {simple_cpp.count(__Line__, "search"); 

    int result = -1;
    for (int i = 0; i < n; ++i) {
        if (key == tbl[i]) {
            result = i; simple_cpp.count(__LINE__); 

        }
    }
    return result;
}

int main() {simple_cpp.count(__Line__, "main"); 


    int lst[5] = {2, 4, 6, 8, 10};
    std::cout << search(lst, 5, 6); simple_cpp.count(__LINE__); 

    std::cout << std::endl; simple_cpp.count(__LINE__); 

    
    std::cout << "Done"; simple_cpp.count(__LINE__); 

    std::cout << std::endl; simple_cpp.count(__LINE__); 

    return 0;
}

