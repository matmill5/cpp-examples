#include "profile.hpp";
extern profilefoo_cpp;

void foo(int x) {foo_cpp.count(__Line__, "foo"); 

    ++x; foo_cpp.count(__LINE__); 

}

