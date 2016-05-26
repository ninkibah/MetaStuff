#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "MovieInfo.h"

#include <iostream>

struct Person {
    void setAge(const int& a)
    {
        if (a >= 0 && a < 128) { // sorry, if you're older than 128
            age = a;
        } else {
            std::cout << "Can't set age. " << a << " is out of allowed range\n";
        }
    }

    const int& getAge() const { return age; }

    int age;
    float salary;
    std::string name;
    std::unordered_map<std::string, std::vector<MovieInfo>> favouriteMovies;
};

// You need to specialize template function Meta::getMember<T> like this
// add "friend struct Meta;" to any class to be able to use private members
// in getMembers<T> function. 

#include <Meta.h>
template <>
inline decltype(auto) Meta::getMembers<Person>()
{
    static auto memberPtrs = std::make_tuple(
        member("age", &Person::getAge, &Person::setAge),
        member("salary", &Person::salary),
        member("name", &Person::name),
        member("favouriteMovies", &Person::favouriteMovies));
    return (memberPtrs); // return by reference!
}