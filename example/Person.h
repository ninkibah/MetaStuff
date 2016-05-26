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
    
// meta stuff
    inline static decltype(auto) getMembers();
};

#include <MemberPtr.h>

inline decltype(auto) Person::getMembers()
{
    using namespace std::string_literals;
    static auto memberPtrs = std::make_tuple(
        member("age"s,             &Person::getAge, &Person::setAge),
        member("salary"s,          &Person::salary),
        member("name"s,            &Person::name),
        member("favouriteMovies"s, &Person::favouriteMovies));
    return (memberPtrs); // return by reference!
}