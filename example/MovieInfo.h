#pragma once

#include <string>

struct MovieInfo {
    std::string name;
    float rating;

// meta
    inline static decltype(auto) getMembers();
};


#include <MemberPtr.h>

inline decltype(auto) MovieInfo::getMembers()
{
    using namespace std::string_literals;
    static auto memberPtrs = std::make_tuple(
    member("name"s,   &MovieInfo::name ),
    member("rating"s, &MovieInfo::rating));
    return (memberPtrs);
}