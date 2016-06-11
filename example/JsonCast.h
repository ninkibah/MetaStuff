#pragma once

#include <map>
#include <string>
#include <vector>
#include <unordered_map>

#include <json/json-forwards.h>

#include <Meta.h>
#include "StringCast.h"

namespace Json
{

/////////////////// SERIALIZATION

template <typename Class,
    typename = std::enable_if_t<std::is_constructible<Value, Class>::value>>
Value serialize(const Class& obj);

template <typename Class,
    typename = std::enable_if_t<!std::is_constructible<Value, Class>::value>,
    typename = void>
Value serialize(const Class& obj);

template <typename Class,
    typename = std::enable_if_t <meta::isRegistered<Class>()>>
Value serialize_impl(const Class& obj);

template <typename Class,
    typename = std::enable_if_t <!meta::isRegistered<Class>()>,
    typename = void>
Value serialize_impl(const Class& obj);

template <typename Class>
Value serialize_basic(const Class& obj);
// specialization for std::vector
template <typename T>
Value serialize_basic(const std::vector<T>& obj);

// specialization for std::unodered_map
template <typename K, typename V>
Value serialize_basic(const std::unordered_map<K, V>& obj);


/////////////////// DESERIALIZATION

template<typename Class>
Class deserialize(const Value& obj);

template <typename Class,
    typename = std::enable_if_t<meta::isRegistered<Class>()>>
void deserialize(Class& obj, const Value& object);

template <typename Class,
    typename = std::enable_if_t<!meta::isRegistered<Class>()>,
    typename = void>
void deserialize(Class& obj, const Value& object);

template <typename T>
T deserialize_basic(const Value& obj);

// specializations
template <> int deserialize_basic(const Value& obj);
template <> float deserialize_basic(const Value& obj);
template <> std::string deserialize_basic(const Value& obj);

// specialization for std::vector
template <typename T>
void deserialize(std::vector<T>& obj, const Value& object);

// specialization for std::unodered_map
template <typename K, typename V>
void deserialize(std::unordered_map<K, V>& obj, const Value& object);

}

#include "JsonCast.inl"