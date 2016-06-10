/* -----------------------------------------------------------------------------------------------

MetaHolder holds all Member objects constructed via meta::registerMembers<T> call. 
Getting those members back is tricky and this is done by MetaGetter (see MetaGetter.h for details)

-------------------------------------------------------------------------------------------------*/

#pragma once

#include <tuple>

namespace meta
{
namespace detail
{

template <typename T, typename... Args>
struct MetaHolder {
    static std::tuple<Args...> members;
};

template <typename T, typename... Args>
std::tuple<Args...> MetaHolder<T, Args...>::members = registerMembers<T>();

} // end of namespace detail
} // end of namespace meta