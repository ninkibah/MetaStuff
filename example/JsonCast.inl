#include <json/json.h>
#include "StringCast.h"
#include "template_helpers.h"

#include <Meta.h>


template <typename Class, typename>
void serialize(const Class& obj, Json::Value& root)
{
    meta::doForAllMembers<Class>(
        [&obj, &root](const auto& member)
        {
            auto& objName = root[member.getName()];
            Json::cast(member.get(obj), objName);
        }
    );
}

template <typename Class, typename, typename>
void serialize(const Class& /* obj */, Json::Value& /* root */)
{

}

template <typename Class, typename>
void deserialize(Class& obj, const Json::Value& root)
{
    meta::doForAllMembers<Class>(
        [&obj, &root](const auto& member)
        {
            using MemberT =
                typename std::decay_t<decltype(member)>::member_type; // get type of member

            MemberT value;
            Json::fromValue(value, root[member.getName()]);
            member.set(obj, value);
        }
    );
}

template <typename Class, typename, typename>
void deserialize(Class& /* obj */, const Json::Value& /* root */)
{

}

namespace Json
{

template <typename T>
void cast(const T& value, Json::Value& root)
{
    serialize(value, root);
}

template <typename T>
void cast(const std::vector<T>& value, Json::Value& root)
{
    auto vectorSize = static_cast<Json::ArrayIndex>(value.size());
    root.resize(vectorSize); // will become Json::arrayValue
    for (Json::ArrayIndex i = 0; i < vectorSize; ++i) {
        cast(value[i], root[i]);
    }
}

template <typename T>
void cast_map(const T& value, Json::Value& root)
{
    root = Value(Json::objectValue);
    for (auto& pair : value) {
        auto key = castToString(pair.first);
        cast(pair.second, root[key]); 
    }
}

template <typename K, typename V>
void cast(const std::map<K, V>& value, Json::Value& root)
{
    cast_map(value, root);
}

template <typename K, typename V>
void cast(const std::unordered_map<K, V>& value, Json::Value& root)
{
    cast_map(value, root);
}

template <typename T>
void fromValue(T& value, const Value& root)
{
    deserialize(value, root);
}

template <typename T>
void fromValue(std::vector<T>& value, const Value& root)
{
    value.resize(root.size());
    for (Json::ArrayIndex i = 0; i < root.size(); ++i) {
        fromValue(value[i], root[i]);
    }
}

template <typename T>
void fromValue_map(T& value, const Value& root)
{
    for (auto& key : root.getMemberNames()) {
        // cast from std::string to map's key type (JSON keys are always strings)
        typename T::key_type mapKey;
        fromString(mapKey, key);
        fromValue(value[mapKey], root[key]);
    }
}

template <typename K, typename V>
void fromValue(std::map<K, V>& value, const Value& root)
{
    fromValue_map(value, root);
}

template <typename K, typename V>
void fromValue(std::unordered_map<K, V>& value, const Value& root)
{
    fromValue_map(value, root);
}

}