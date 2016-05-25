#include "JsonCast.h"
#include <json/json.h>

namespace Json
{

void cast(const int& value, Json::Value& root)
{
    root = value;
}

void cast(const float& value, Json::Value& root)
{
    root = value;
}

void cast(const std::string& value, Json::Value& root)
{
    root = value;
}

void fromValue(int& value, const Value& root)
{
    value = root.asInt();
}

void fromValue(float& value, const Value& root)
{
    value = root.asFloat();
}

void fromValue(std::string& value, const Value& root)
{
    value = root.asString();
}

}