#pragma once

#include <MemberPtr.h> // included just so that user can #include "Meta.h" and get this header which is always needed

struct Meta {
    template <typename T>
    inline static auto& getMembers();
};

// default for unregistered classes

template <typename T>
inline auto& Meta::getMembers()
{
    static std::tuple<> emptyTuple;
    return emptyTuple;
}