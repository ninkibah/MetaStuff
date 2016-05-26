#pragma once

#include <string>

struct MovieInfo {
    std::string name;
    float rating;
};

#include <Meta.h>

template <>
inline auto& Meta::getMembers<MovieInfo>()
{
    static auto members = std::make_tuple(
        member("name", &MovieInfo::name),
        member("rating", &MovieInfo::rating));
    return members;
}