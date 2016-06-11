#include "JsonCast.h"
#include <json/json.h>

namespace Json
{

template <>
int deserialize_basic(const Value& obj)
{
    return obj.asInt();
}

template <>
float deserialize_basic(const Value& obj)
{
    return obj.asFloat();
}

template <>
std::string deserialize_basic(const Value& obj)
{
    return obj.asString();
}

}