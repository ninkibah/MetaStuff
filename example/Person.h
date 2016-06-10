#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "MovieInfo.h"

#include <iostream>

struct Person {
    // add this if you want to register private members:
    // template <>
    // auto meta::registerMembers<Person>();

    void setAge(int a)
    {
        std::cout << "Age is set by calling setter!\n";
        if (a >= 0 && a < 128) { // sorry, if you're older than 128
            age = a;
        } else {
            std::cout << "Can't set age. " << a << " is out of allowed range\n";
        }
    }

    int getAge() const { return age; }

    int age;
    float salary;
    std::string name;
    std::unordered_map<std::string, std::vector<MovieInfo>> favouriteMovies;
};

#include <Meta.h>

namespace meta
{

template <>
inline auto registerMembers<Person>()
{
    return members(
        member("age", &Person::age)
            .addGetterSetter(&Person::getAge, &Person::setAge),
        member("salary", &Person::salary),
        member("name", &Person::name),
        member("favouriteMovies", &Person::favouriteMovies)
    );
}

}