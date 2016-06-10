/* -----------------------------------------------------------------------------------------------

MetaGetter is used to access members from MetaHolder by just <T>, not by <T, Args...>
This works because meta::register returns std::tuple<Args...> which we can use by adding
a tricky specialization: MetaGetter <T, std::tuple<Args...>> which "catches" Args... inside
the tuple and then uses it to access MetaHolder<T, Args...>s

-------------------------------------------------------------------------------------------------*/

#pragma once

#include "MetaHolder.h"

namespace meta
{
namespace detail
{

template <typename T, typename... Args>
struct MetaGetter {
    static const auto& getMembers();
};

template <typename T, typename... Args>
const auto& MetaGetter<T, Args...>::getMembers()
{
    return MetaHolder<T>::members; // empty tuple
}

template <typename T, typename... Args>
struct MetaGetter <T, std::tuple<Args...>>
{
    static const auto& getMembers();
};

template <typename T, typename... Args>
const auto& MetaGetter <T, std::tuple<Args...>>::getMembers()
{
    return MetaHolder<T, Args...>::members;
}

} // end of namespace detail
} // end of namespace meta