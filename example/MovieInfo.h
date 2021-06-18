#pragma once

#include <string>

struct MovieInfo {
    std::string name;
    float rating;
};

#include <MetaStuff/Meta.h>
#include <MetaStuff/Macros.h>


METASTUFF_DEFINE_MEMBERS(MovieInfo, name, rating)
