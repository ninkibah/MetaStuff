// Various useful template stuff
// thanks to Vittorio Romeo and other people who came up with this stuff

#pragma once

// for_each_arg - call f for each argument from pack
template <typename F, typename... Args>
void for_each_arg(F&& f, Args&&... args);

// for_each_arg - call f for each element from tuple
template <typename F, typename TupleT>
void for_tuple(F&& f, TupleT&& tuple);

template <typename F>
void for_tuple(F&& f, std::tuple<>&& tuple);

#include "template_helpers.inl"