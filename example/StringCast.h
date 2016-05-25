// In JSON map keys can only be strings, so here's a class which makes conversion to/from string easy
#pragma once

#include <string>

template <typename T>
std::string castToString(const T& value);

// template specializations

std::string castToString(const bool& value);
std::string castToString(const int& value);
std::string castToString(const float& value);
std::string castToString(const std::string& value);

template <typename T>
void fromString(T& obj, const std::string& value);

void fromString(bool& obj, const std::string& valueStr);
void fromString(int& obj, const std::string& valueStr);
void fromString(float& obj, const std::string& valueStr);
void fromString(std::string& obj, const std::string& valueStr);


// return empty string if no conversion possible
template <typename T>
std::string castToString(const T& /* value */)
{
    return std::string();
}

template <typename T>
void fromString(T& /* obj */, const std::string& /* value */)
{ }