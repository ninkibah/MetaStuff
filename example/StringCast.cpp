#include "stringcast.h"

std::string castToString(const bool& value)
{
    return value ? "true" : "false";
}

std::string castToString(const int& value)
{
    return std::to_string(value);
}

std::string castToString(const float& value)
{
    return std::to_string(value);
}

std::string castToString(const std::string& value)
{
    return value;
}

// from string

void fromString(bool& obj, const std::string& valueStr)
{
    if(valueStr == "true") {
        obj = true;
    } else if (valueStr == "false") {
        obj = false;
    }
}

void fromString(int& obj, const std::string& valueStr)
{
    obj = std::stoi(valueStr);
}

void fromString(float& obj, const std::string& valueStr)
{
    obj = std::stof(valueStr);
}

void fromString(std::string& obj, const std::string& valueStr)
{
    obj = valueStr;
}
