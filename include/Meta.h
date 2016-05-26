#pragma once

#include <MemberPtr.h>

struct Meta {
    template <typename T>
    inline static decltype(auto) getMembers();
};

// default for unregistered classes

template <typename T>
inline decltype(auto) Meta::getMembers()
{
    return std::tuple<>();
}