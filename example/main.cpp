#include <iostream>

#include <json/json.h>

#include "JsonCast.h"
#include "Person.h"

class Unregistered
{ };

#include <Meta.h>

void printSeparator()
{
    std::cout << "========================\n";
}

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
    std::cout << "Members of class Person:\n";
    for_tuple([](const auto& member)
    {
        std::cout << "* " << member.getName() << '\n';
    }, Meta::getMembers<Person>());

    std::cout << "Members of class MovieInfo:\n";
    for_tuple([](const auto& member)
    {
        std::cout << "* " << member.getName() << '\n';
    }, Meta::getMembers<MovieInfo>());

    printSeparator();

    // checking if classes are registered
    if (Meta::isRegistered<Person>()) {
        std::cout << "Person class is registered\n";
    }

    if (!Meta::isRegistered<Unregistered>()) {
        std::cout << "Unregistered class is unregistered\n";
    }

    // checking if class has a member
    if (Meta::hasMember<Person>("age")) {
        std::cout << "Person has member named 'age'\n";
    }

    // getting setting member values
    int age = Meta::getMemberValue<int>(person, "age");
    std::cout << "Got person's age: " << age << '\n';

    Meta::setMemberValue<int>(person, "age", 30);
    age = Meta::getMemberValue<int>(person, "age");
    std::cout << "Changed person's age to " << age << '\n';

    printSeparator();

    // And here's how you can serialize/deserialize
    // (if you write a function for your type. I wrote it for Json::Value! ;D)
    Json::Value root;
    serialize(person, root);

    std::cout << "Serializing person:" << '\n';
    std::cout << root << '\n';

    Unregistered y;
    Json::Value root2;
    serialize(y, root2);
    std::cout << "Trying to serialize unregistered class:\n";
    std::cout << root2 << '\n';

    printSeparator();

    Person person2;
    deserialize(person2, root); // set values from Json::Value

#ifdef _WIN32 // okay, this is not cool code, sorry :D
    system("pause");
#endif
}