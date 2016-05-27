// Various useful template stuff
// thanks to Vittorio Romeo and other people who came up with this stuff

#pragma once

// for_each_arg - call f for each argument from pack
template <typename F, typename... Args>
void for_each_arg(F&& f, Args&&... args);

// for_each_arg - call f for each element from tuple
template <typename F, typename TupleT>
void for_tuple(F&& f, TupleT&& tuple);

// overload for empty tuple which does nothing
template <typename F>
void for_tuple(F&& f, const std::tuple<>& tuple);

// calls F if types T and U are the same
// this is useful for templated lambdas, because they won't be
// instantiated with unneeded types
template <typename T, typename U,
    typename F, typename... Args,
    typename = std::enable_if_t<std::is_same<T, U>::value>>
void call_if_same_types(F&& f, Args&&... args);

// types differ, do nothing
template <typename T, typename U,
    typename F, typename... Args,
    typename = std::enable_if_t<!std::is_same<T, U>::value>,
    typename = void> // dummy type for difference between two functions
void call_if_same_types(F&& f, Args&&... args);

#include "template_helpers.inl"