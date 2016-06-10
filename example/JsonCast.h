#pragma once

#include <map>
#include <string>
#include <vector>
#include <unordered_map>

#include <json/json-forwards.h>

#include <Meta.h>

template <typename Class,
    typename = std::enable_if_t<meta::isRegistered<Class>()>>
void serialize(const Class& obj, Json::Value& root);

template <typename Class,
    typename = std::enable_if_t<!meta::isRegistered<Class>()>,
    typename = void>
void serialize(const Class& obj, Json::Value& root);

template <typename Class,
    typename = std::enable_if_t<meta::isRegistered<Class>()>>
void deserialize(Class& obj, const Json::Value& root);

template <typename Class,
    typename = std::enable_if_t<!meta::isRegistered<Class>()>,
    typename = void>
void deserialize(Class& obj, const Json::Value& root);

namespace Json
{
    // Cast 
    template <typename T>
    void cast(const T& value, Json::Value& root);

    void cast(const int& value, Json::Value& root);
    void cast(const float& value, Json::Value& root);
    void cast(const std::string& value, Json::Value& root);

    template <typename T>
    void cast(const std::vector<T>& value, Json::Value& root);

    template <typename T>
    void cast_map(const T& value, Json::Value& root);

    template <typename K, typename V>
    void cast(const std::map<K, V>& value, Json::Value& root);

    template <typename K, typename V>
    void cast(const std::unordered_map<K, V>& value, Json::Value& root);

    // From value 

    template <typename T>
    void fromValue(T& value, const Value& root);

    void fromValue(int& value, const Value& root);
    void fromValue(float& value, const Value& root);
    void fromValue(std::string& value, const Value& root);

    template <typename T>
    void fromValue(std::vector<T>& value, const Value& root);

    template <typename T>
    void fromValue_map(T& value, const Value& root);

    template <typename K, typename V>
    void fromValue(std::map<K, V>& value, const Value& root);

    template <typename K, typename V>
    void fromValue(std::unordered_map<K, V>& value, const Value& root);
}


#include "JsonCast.inl"