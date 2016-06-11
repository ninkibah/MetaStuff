/* -----------------------------------------------------------------------------------------------

MetaHolder holds all Member objects constructed via meta::registerMembers<T> call.
If the class is not registered, members is std::tuple<>

-------------------------------------------------------------------------------------------------*/

#pragma once

#include <tuple>

namespace meta
{
namespace detail
{

template <typename T, typename TupleType>
struct MetaHolder {
    static TupleType members;
};

template <typename T, typename TupleType>
TupleType MetaHolder<T, TupleType>::members = registerMembers<T>();


} // end of namespace detail
} // end of namespace meta