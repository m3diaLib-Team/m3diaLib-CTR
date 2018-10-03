#include <3ds.h>
#include <stdio.h> 
#include "m3d/core/console.hpp"

namespace m3d {
    void Console::print(const char* t_data) {
        printf(t_data);
    }

}