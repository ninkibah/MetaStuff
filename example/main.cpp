#include <iostream>

#include <json/json.h>

#include "JsonCast.h"
#include "Person.h"

class Unregistered
{ };

#include <Meta.h>

int main()
{
    Person person;
    person.age = 25;
    person.salary = 3.50f;
    person.name = "Ron Burgandy"; // I'm a person!
    person.favouriteMovies["Nostalgia Critic"] = { MovieInfo{ "The Room", 8.5f } };
    person.favouriteMovies["John Tron"] = { MovieInfo{"Goosebumps", 10.0f },
                                            MovieInfo{ "Talking Cat", 9.0f } };

    // printing members of different classes
    std::cout << "Members of Person:" << std::endl;
    for_tuple([](const auto& member)
    {
        std::cout << member.getName() << std::endl;
    }, Meta::getMembers<Person>());
    std::cout << std::endl;

    std::cout << "Members of MovieInfo:" << std::endl;
    for_tuple([](const auto& member)
    {
        std::cout << member.getName() << std::endl;
    }, Meta::getMembers<MovieInfo>());
    std::cout << std::endl;

    // And here's how you can serialize/deserialize
    // (if you write a function for your type. I wrote it for Json::Value! ;D)
    Json::Value root;
    serialize(person, root);

    std::cout << "Serializing person:" << std::endl;
    std::cout << root << std::endl;

    Unregistered y;
    Json::Value root2;
    serialize(y, root2);
    std::cout << "Trying to serialize unregistered class, result:" << std::endl;
    std::cout << root2 << std::endl;
    std::cout << "============" << std::endl;

    Person person2;
    deserialize(person2, root); // set values from Json::Value
}